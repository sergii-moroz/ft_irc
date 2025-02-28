/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleTOPIC.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:39:34 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/28 22:06:51 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void CommandHandler::handleTOPIC(int sd, Command const & cmd)
{
	User &		user = _server->getUser(sd);
	std::string	nickname = user.getNickname();

	// Guard REGISTERED
	if (!user.getStatus(REGISTERED))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] Command \"" << cmd.getName() << "\" available only for registered users." << std::endl;
		// optional send error here
		return;
	}

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cerr << "ERROR: " <<  nickname << " [" << sd << "] ERR_NEEDMOREPARAMS (461) - " << cmd.getName() << std::endl;
		std::string	errMsg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, errMsg);
		return;
	}

	std::string channelName = cmd.getParamAtPos(0, 0);
	Channel *channel = _server->getChannelByName(channelName);

	if (!channel)
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NOSUCHCHANNEL (403) - " << cmd.getName() << std::endl;
		std::string	errMsg = errNoSuchChannel(_server->getName(), nickname, channelName);
		_server->sendData(sd, errMsg);
		return;
	}

	if (!channel->isUser(&user))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NOTONCHANNEL (442) - " << cmd.getName() << std::endl;
		std::string	errMsg = errNotOnChannel(_server->getName(), nickname, channelName);
		_server->sendData(sd, errMsg);
		return;
	}

	std::string	topic = channel->getTopic();
	std::string	newTopic = cmd.getTail();
	std::string	msg;

	if (newTopic.length())
	{
		// setTopic

		if (channel->getMode(TOPIC_MODE) && !channel->isOperator(&user))
		{
			std::string errMsg = errChanOpPrivsNeeded(_server->getName(), nickname, channelName);
			_server->sendData(sd, errMsg);
			return;
		}

		std::cout << "INFO: " << nickname << " [" << sd << "] set \"" << newTopic << "\" as new topic for " << channelName << std::endl;
		channel->setTopic(newTopic);
		msg = ":" + nickname + "!" + user.getUsername()
			+ "@" + _server->getName()
			+  " TOPIC " + channelName + " :" + newTopic + "\r\n";
		channel->broadcastAll(_server, msg);
	}
	else
	{
		// get topic
		std::cout << "INFO: " << nickname << " [" << sd << "] request topic of " << channelName << " topic" << std::endl;
		if (topic.length() == 1 && topic[0] == ' ')
			msg = rplNoTopic(_server->getName(), nickname, channelName);
		else
			msg = rplTopic(_server->getName(), nickname, channelName, topic);
		_server->sendData(sd, msg);
	}
}
