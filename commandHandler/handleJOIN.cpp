/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleJOIN.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:10:01 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/27 14:22:12 by olanokhi         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

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


	if (channel->getMode(INVATE_MODE) && !channel->isInvitedUser(&user))
	{

		std::string err = "473 " + nick + " " + channelName
						  + " :Cannot join channel (+i)\r\n";
		_server->sendData(sd, err);
		return;
	}


	if (!channel->getKey().empty())
	{
		std::string key;
		if (cmd.hasParamAtPos(1, 0))
			key = cmd.getParamAtPos(1, 0);

		if (key != channel->getKey())
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


	if (!channel->isUser(&user))
	{
		channel->addUser(&user);


		if (newChannel)
			channel->addOperator(&user);


		if (channel->isInvitedUser(&user))
			channel->removeInvitedUser(&user);


		std::string joinMsg = ":" + nick + " JOIN :" + channelName + "\r\n";
		_server->sendData(sd, joinMsg);


		std::string broadcastMsg = ":" + nick + " JOIN " + channelName + "\r\n";
		channel->broadcastAll(_server, broadcastMsg);
	}
}
