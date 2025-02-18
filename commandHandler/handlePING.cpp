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
	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::string nickname = _server->getUser(sd).getNickname();
		if (nickname.empty())
			nickname = "*";

		std::cout << "ERROR: user [" << sd << "] ERR_NEEDMOREPARAMS (461) - PING" << std::endl;
		std::string msg = errNeedMoreParams(_server->getName(), "PING");
		_server->sendData(sd, msg);
	}
	else
	{
		std::string token = cmd.getParamAtPos(0, 0);

		std::cout << "INFO: user [" << sd << "] sent PING with token: " << token << std::endl;

		std::string response = ":" + _server->getName() +
							   " PONG " + _server->getName() +
							   " :" + token + "\r\n";

		_server->sendData(sd, response);
	}
}
