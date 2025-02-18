/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePONG.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:43:23 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/18 12:53:48 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


#include "CommandHandler.hpp"


void	CommandHandler::handlePONG(int sd, Command const & cmd)
{


	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::string nickname = _server->getUser(sd).getNickname();
		if (nickname.empty())
			nickname = "*";

		std::cout << "ERROR: user [" << sd << "] ERR_NEEDMOREPARAMS (461) - PONG" << std::endl;
		std::string msg = errNeedMoreParams(_server->getName(), "PONG");
		_server->sendData(sd, msg);
	}
	else
	{
		std::string token = cmd.getParamAtPos(0, 0);
		std::cout << "INFO: user [" << sd << "] PONG received with token: " << token << std::endl;
	}
}
