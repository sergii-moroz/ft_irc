/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleJOIN.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:10:01 by smoreron          #+#    #+#             */
/*   Updated: 2025/03/04 11:28:49 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void CommandHandler::handleJOIN(int sd, Command const & cmd)
{
	User &		user = _server->getUser(sd);
	std::string	nickname = user.getNickname();

	// Guard REGISTERED
	if (!user.getStatus(REGISTERED))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] Command \"" << cmd.getName() << "\" available only for registered users." << std::endl;
		std::string	msg = errNotRegistered(_server->getName(), nickname);
		_server->sendData(sd, msg);
		return ;
	}

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cerr << "ERROR: " <<  nickname << " [" << sd << "] ERR_NEEDMOREPARAMS (461) - " << cmd.getName() << std::endl;
		std::string	errorMsg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, errorMsg);
		return;
	}

	std::string	args = cmd.getParamAtPos(0, 0);
	std::string	kwargs = "";

	if (cmd.hasParamAtPos(1, 0))
		kwargs = cmd.getParamAtPos(1, 0);

	std::vector<std::string>	channels = splitByComma(args, 0);
	std::vector<std::string>	keys = splitByComma(kwargs, channels.size());

	for (size_t i = 0; i < channels.size(); ++i)
		joinChannel(channels[i], keys[i], user);
}

void	CommandHandler::joinChannel(std::string const & channelName, std::string const & key, User & user) const
{
	std::string	nickname = user.getNickname();
	int	sd = user.getFd();

	Channel *channel = _server->getChannelByName(channelName);

	if (!channel)
	{
		_server->createChannel(channelName);

		channel = _server->getChannelByName(channelName);
		std::cout << "INFO: " << channelName << " was created by " << nickname << " [" << sd << "]" << std::endl;

		channel->addOperator(&user);
		std::cout << "INFO: " << nickname << " [" << sd << "] gets operators role on the " << channelName << std::endl;
	}

	if (channel->getMode(INVITE_MODE) && !channel->isInvitedUser(&user))
	{
		std::string	msg = errInviteOnlyChan(_server->getName(), nickname, channelName);
		_server->sendData(sd, msg);
		return ;
	}

	if (channel->getMode(KEY_MODE) && key != channel->getKey())
	{
		std::cerr << "ERROR: " <<  nickname << " [" << sd << "] ERR_BADCHANNELKEY (475) - the channel \"" << channelName
			<< "\" requires a key and the key was either incorrect or not supplied." << std::endl;
		std::string	msg = errBadChannelKey(_server->getName(), nickname, channelName);
		_server->sendData(sd, msg);
		return ;
	}

	if (channel->getMode(LIMIT_MODE) && channel->getUsersCount() >= channel->getUserLimit())
	{
		std::string	msg = errChannelIsFull(_server->getName(), nickname, channelName);
		_server->sendData(sd, msg);
		return;
	}

	if (!channel->isUser(&user))
	{
		std::cout << "INFO: " << nickname << " [" << sd << "] join " << channelName << std::endl;
		channel->addUser(&user);

		if (channel->isInvitedUser(&user))
			channel->removeInvitedUser(&user);

		// Send to all user
		std::string	msg = ":" + nickname + "!" + user.getUsername() + "@" + _server->getName()
			+ " JOIN " + channelName + "\r\n";
		channel->broadcastAll(_server, msg);

		// Send Topic to the Joining User
		std::string	topic = channel->getTopic();
		if (topic.length() == 1 && topic[0] == ' ')
			msg = rplNoTopic(_server->getName(), nickname, channelName);
		else
			msg = rplTopic(_server->getName(), nickname, channelName, topic);
		_server->sendData(sd, msg);

		// Send the List of Users in the Channel
		// The server must send a list of all current members in #channel to only the joining user:
		msg = rplNamReply(_server->getName(), nickname, channelName, channel->getMembersList());
		_server->sendData(sd, msg);

		msg = rplEndOfNames(_server->getName(), nickname, channelName);
		_server->sendData(sd, msg);
	}
}
