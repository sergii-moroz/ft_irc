/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePASS.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:52:56 by smoroz            #+#    #+#             */
/*   Updated: 2025/03/04 19:52:00 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void	CommandHandler::handlePASS(int sd, Command const & cmd)
{
	User &		user = _server->getUser(sd);
	std::string	nickname = user.getNickname();

	// Guard REGISTERED
	if (user.getStatus(REGISTERED))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_ALREADYREGISTERED (462) - " << cmd.getName() << std::endl;
		std::string	msg = errAlreadyRegistered(_server->getName(), nickname);
		_server->sendData(sd, msg);
		return ;
	}

	// Guard NICK / USER
	if (user.getStatus(NICK) || user.getStatus(USER))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] MUST send a PASS command before sending the NICK / USER combination." << std::endl;
		return;
	}

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NEEDMOREPARAMS (461) - " << cmd.getName() << std::endl;
		std::string	msg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, msg);
		_server->clearClient(sd);
	}
	else if (cmd.hasParamAtPos(_server->getPass(), 0, 0))
	{
		std::cout << "INFO: " + nickname + " [" << sd << "] password accepted" << std::endl;
		user.setStatus(PASSWORD, true);
	}
	else
	{
		std::cerr << "ERROR: " + nickname + " [" << sd << "] ERR_PASSWDMISMATCH (464) - " << cmd.getName() << std::endl;
		std::string	msg = errPasswdMismatch(_server->getName());
		_server->sendData(sd, msg);
		_server->clearClient(sd);
	}
}
