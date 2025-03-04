/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleUSER.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:25:00 by smoroz            #+#    #+#             */
/*   Updated: 2025/03/04 19:46:26 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void	CommandHandler::handleUSER(int sd, const Command &cmd)
{
	User &		user = _server->getUser(sd);
	std::string	nickname = user.getNickname();

	// Guard Password
	if (!user.getStatus(PASSWORD))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] MUST send a PASS command before sending the NICK / USER combination." << std::endl;
		std::string	msg = errNotRegistered(_server->getName(), nickname);
		_server->sendData(sd, msg);
		return;
	}

	// Guard Registered
	if (user.getStatus(REGISTERED))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_ALREADYREGISTERED (462) - " << cmd.getName() << std::endl;
		std::string	msg = errAlreadyRegistered(_server->getName(), nickname);
		_server->sendData(sd, msg);
		return ;
	}

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NEEDMOREPARAMS (461) - " << cmd.getName() << std::endl;
		std::string	msg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, msg);
		_server->clearClient(sd);
	}
	else
	{
		std::string	username = cmd.getParamAtPos(0, 0);
		std::string	realname = cmd.getTail();

		user.setUsername(username);
		user.setRealname(realname);
		user.setStatus(USER, true);

		// Registration is completed
		if (!user.getStatus(REGISTERED) && user.getStatus() == END_REG)
		{
			user.setStatus(REGISTERED, true);
			std::string	msg = rplWelcome(_server->getName(), nickname);
			_server->sendData(sd, msg);
		}

		std::cout << "INFO: " << nickname << "!" << username << "@" << _server->getName() << " [" << sd << "] registered with realname: "  << realname << std::endl;
		std::cout << "INFO: " << user << std::endl; // <-- Debug
	}
}
