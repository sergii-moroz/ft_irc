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
	User &	user = _server->getUser(sd);
	std::string nickname = user.getNickname();

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NEEDMOREPARAMS (461) - " << cmd.getName() << std::endl;
		std::string msg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, msg);
	}
	else
	{
		std::string token = cmd.getParamAtPos(0, 0);
		std::cout << "INFO: " << nickname << " [" << sd << "] PONG received with token: " << token << std::endl;
	}
}
