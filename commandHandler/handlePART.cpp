/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePART.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:36:10 by smoroz            #+#    #+#             */
/*   Updated: 2025/03/04 12:41:31 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void	CommandHandler::handlePART(int sd, Command const & cmd)
{
	User &		user = _server->getUser(sd);
	std::string	nickname = user.getNickname();

	// Guard REGISTERED
	if (!user.getStatus(REGISTERED))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] Command \"" << cmd.getName() << "\" available only for registered users." << std::endl;
		std::string	msg = errNotRegistered(_server->getName(), nickname);
		_server->sendData(sd, msg);
		return;
	}

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NEEDMOREPARAMS (461)" << cmd.getName() << std::endl;
		std::string	msg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, msg);
		return ;
	}

	std::string	args = cmd.getParamAtPos(0, 0);
	std::string	reason = cmd.getTail();

	if (reason.empty())
		reason = "Goodbye everyone!";

	std::vector<std::string>	channels = splitByComma(args, 0);

	for (size_t i = 0; i < channels.size(); ++i)
		leaveChannel(channels[i], reason, user);
}

void	CommandHandler::leaveChannel(std::string const & channelName, std::string const & reason, User & user) const
{
	std::string	nickname = user.getNickname();
	int			sd = user.getFd();
	Channel		*channel = _server->getChannelByName(channelName);

	if (!channel)
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NOSUCHCHANNEL (403) - PART " << channelName << std::endl;
		std::string msg = errNoSuchChannel(_server->getName(), nickname, channelName);
		_server->sendData(sd, msg);
		return;
	}

	if (!channel->isUser(&user))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NOTONCHANNEL (442) - PART " << channelName << std::endl;
		std::string msg = errNotOnChannel(_server->getName(), nickname, channelName);
		_server->sendData(sd, msg);
		return;
	}

	std::cout << "INFO: " << nickname << " [" << sd << "] leave " << channelName << std::endl;

	std::string	msg = ":" + nickname + "!" + user.getUsername() + "@" + _server->getName()
		+ " PART " + channelName + " :" + reason + "\r\n";
	channel->broadcastAll(_server, msg);
	channel->removeUser(&user);

	// delete channel if it is empty
	if (channel->getUsersCount() == 0)
	{
		std::cout << "INFO: last user leave the channel \"" << channelName << "\"."<< std::endl;
		std::cout << "INFO: The channel \"" << channelName << "\" was deleted."<< std::endl;
		_server->deleteChannel(channelName);
	}
}
