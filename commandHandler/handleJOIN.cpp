/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleJOIN.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:10:01 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/26 02:20:16 by smoreron         ###   ########.fr       */
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
	User &user = _server->getUser(sd);
	std::string nick = user.getNickname();

	
	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::string errorMsg = "461 " + nick + " JOIN :Not enough parameters\r\n";
		_server->sendData(sd, errorMsg);
		return;
	}

	std::string channelName = cmd.getParamAtPos(0, 0);
	Channel *channel = _server->getChannelByName(channelName);

	bool newChannel = false;
	if (!channel)
	{
		
		_server->createChannel(channelName);
		channel = _server->getChannelByName(channelName);
		newChannel = true;
	}

	
	if (channel->isBanned(nick))
	{
		std::string err = "474 " + nick + " " + channelName
						  + " :You are banned from this channel\r\n";
		_server->sendData(sd, err);
		return;
	}

	
	if (channel->hasMode(MODE_INVITE_ONLY) && !channel->isInvited(nick))
	{
		
		std::string err = "473 " + nick + " " + channelName
						  + " :Cannot join channel (+i)\r\n";
		_server->sendData(sd, err);
		return;
	}

	
	if (!channel->getPassword().empty())
	{
		std::string key;
		if (cmd.hasParamAtPos(1, 0))
			key = cmd.getParamAtPos(1, 0);

		if (key != channel->getPassword())
		{
			std::string err = "475 " + nick + " " + channelName
							  + " :Cannot join channel (+k)\r\n";
			_server->sendData(sd, err);
			return;
		}
	}

	
	if (channel->getUserLimit() > 0
		&& channel->getUsers().size() >= channel->getUserLimit())
	{
		std::string err = "471 " + nick + " " + channelName
						  + " :Cannot join channel (+l)\r\n";
		_server->sendData(sd, err);
		return;
	}

	
	if (!channel->hasUser(sd))
	{
		channel->addUser(sd);

		
		if (newChannel)
			channel->addOperator(sd);

		
		if (channel->isInvited(nick))
			channel->removeInvited(nick);

		
		std::string joinMsg = ":" + nick + " JOIN :" + channelName + "\r\n";
		_server->sendData(sd, joinMsg);

		
		std::string broadcastMsg = ":" + nick + " JOIN " + channelName + "\r\n";
		channel->broadcastRaw(*_server, broadcastMsg);
	}
}
