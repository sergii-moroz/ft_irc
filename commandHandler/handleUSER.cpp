/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleUSER.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:25:00 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/27 14:04:47 by olanokhi         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void	CommandHandler::handleUSER(int sd, const Command &cmd)
{
	User &		user = _server->getUser(sd);
	std::string	nickname = user.getNickname();

	if (user.getStatus(REGISTERED))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_ALREADYREGISTERED (462)" << std::endl;
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
		// user.setStatus(REGISTERED, true);

		std::cout << "INFO: " << nickname << "!" << username << "@" << _server->getName() << " [" << sd << "] registered with realname: "  << realname << std::endl;
		std::cout << "INFO: " << user << std::endl;
		std::string	msg = ":localhost 001 root :Welcome to the IRC Network, <nickname>!<user>@<host>\r\n";
		_server->sendData(sd, msg);
	}
}
