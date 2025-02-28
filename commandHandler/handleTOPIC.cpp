/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleTOPIC.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:39:34 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/27 14:33:34 by olanokhi         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"


void CommandHandler::handleTOPIC(int sd, Command const & cmd)
{
	User &user = _server->getUser(sd);
	std::string nick = user.getNickname();


	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{

		std::string errMsg = ":" + _server->getName() + " 461 "
							 + nick + " TOPIC :Not enough parameters\r\n";
		_server->sendData(sd, errMsg);
		return;
	}

	std::string channelName = cmd.getParamAtPos(0, 0);
	Channel *channel = _server->getChannelByName(channelName);

	if (!channel)
	{

		std::string errMsg = ":" + _server->getName() + " 403 "
							 + nick + " " + channelName
							 + " :No such channel\r\n";
		_server->sendData(sd, errMsg);
		return;
	}


	if (!channel->isUser(&user))
	{

		std::string errMsg = ":" + _server->getName() + " 442 "
							 + nick + " " + channelName
							 + " :You're not on that channel\r\n";
		_server->sendData(sd, errMsg);
		return;
	}


	if (cmd.getParameters().size() < 2 || !cmd.hasParamAtPos(1, 0))
	{

		std::string currentTopic = channel->getTopic();
		if (currentTopic.empty() || currentTopic == "unknown")
		{

			std::string msg = ":" + _server->getName() + " 331 "
							  + nick + " " + channelName
							  + " :No topic is set\r\n";
			_server->sendData(sd, msg);
		}
		else
		{

			std::string msg = ":" + _server->getName() + " 332 "
							  + nick + " " + channelName
							  + " :" + currentTopic + "\r\n";
			_server->sendData(sd, msg);
		}
	}
	else
	{

		if ((channel->getMode(TOPIC_MODE)) && !channel->isOperator(&user))
		{

			std::string errMsg = ":" + _server->getName() + " 482 "
								 + nick + " " + channelName
								 + " :You're not channel operator\r\n";
			_server->sendData(sd, errMsg);
			return;
		}


		std::string newTopic = cmd.getParamAtPos(1, 0);
		channel->setTopic(newTopic);


		std::string topicMsg = ":" + nick + "!" + user.getUsername()
							   + "@" + _server->getName()
							   + " TOPIC " + channelName
							   + " :" + newTopic + "\r\n";
		channel->broadcastAll(_server, topicMsg);
	}
}
