/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePING.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:25:05 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/18 12:53:59 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"


void	CommandHandler::handlePING(int sd, Command const & cmd)
{
	User &		user = _server->getUser(sd);
	std::string nickname = user.getNickname();

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cerr << "ERROR: " <<  nickname << " [" << sd << "] ERR_NEEDMOREPARAMS (461) - " << cmd.getName() << std::endl;
		std::string msg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, msg);
	}
	else
	{
		std::string token = cmd.getParamAtPos(0, 0);
		std::cout << "INFO: " << nickname << " [" << sd << "] sent PING with token: " << token << std::endl;

		std::string response = ":" + _server->getName()
			+ " PONG " + _server->getName() + " :" + token + "\r\n";

		_server->sendData(sd, response);
	}
}
