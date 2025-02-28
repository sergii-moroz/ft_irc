/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePASS.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:52:56 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/27 14:02:26 by olanokhi         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void	CommandHandler::handlePASS(int sd, Command const & cmd)
{
	User &		user = _server->getUser(sd);
	std::string	nickname = user.getNickname();

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NEEDMOREPARAMS (461)" << cmd.getName() << std::endl;
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
		std::cerr << "ERROR: " + nickname + " [" << sd << "] ERR_PASSWDMISMATCH (464)" << std::endl;
		std::string	msg = errPasswdMismatch(_server->getName());
		_server->sendData(sd, msg);
		_server->clearClient(sd);
	}
}
