/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleJOIN.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:10:01 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/23 13:10:56 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include <iostream>


void CommandHandler::handleJOIN(int sd, Command const & cmd)
{
	
	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		User &user = _server->getUser(sd);
		std::string errorMsg = "461 " + user.getNickname()
							 + " JOIN :Not enough parameters\r\n";
		_server->sendData(sd, errorMsg);
		return;
	}

	
	std::string channelName = cmd.getParamAtPos(0, 0);
	Channel *channel = _server->getChannelByName(channelName);
	if (!channel)
	{
		_server->createChannel(channelName);
		channel = _server->getChannelByName(channelName);
	}

	
	if (!channel->hasUser(sd))
	{
		channel->addUser(sd);
		User &user = _server->getUser(sd);

		
		std::string joinMsg = ":" + user.getNickname() 
							+ " JOIN :" + channelName + "\r\n";
		_server->sendData(sd, joinMsg);

	}
	
}

