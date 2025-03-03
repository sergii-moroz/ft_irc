/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleKICK.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:23:38 by smoreron          #+#    #+#             */
/*   Updated: 2025/03/03 09:05:51 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"


void CommandHandler::handleKICK(int sd, Command const & cmd)
{
	User &		sender = _server->getUser(sd);
	std::string senderNick = sender.getNickname();

	// Guard REGISTERED
	if (!sender.getStatus(REGISTERED))
	{
		std::cerr << "ERROR: " << senderNick << " [" << sd << "] Command \"" << cmd.getName() << "\" available only for registered users." << std::endl;
		std::string	msg = errNotRegistered(_server->getName(), senderNick);
		_server->sendData(sd, msg);
		return;
	}

	if (cmd.isParamEmpty()
		|| !cmd.hasParamAtPos(0, 0)
		|| !cmd.hasParamAtPos(1, 0))
	{
		std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NEEDMOREPARAMS (461) - " << cmd.getName() << std::endl;
		std::string msg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, msg);
		return;
	}

	std::string channelName = cmd.getParamAtPos(0, 0);
	std::string targetNick  = cmd.getParamAtPos(1, 0);
	std::string reason = cmd.getTail();

	if (reason.empty())
		reason = "Kicked";

	Channel *channel = _server->getChannelByName(channelName);
	if (!channel)
	{
		std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NOSUCHCHANNEL (403) - " << cmd.getName() << std::endl;
		std::string errMsg = errNoSuchChannel(_server->getName(), senderNick, channelName);
		_server->sendData(sd, errMsg);
		return;
	}

	if (!channel->isUser(&sender))
	{
		std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NOTONCHANNEL (442) - " << cmd.getName() << std::endl;
		std::string	errMsg = errNotOnChannel(_server->getName(), senderNick, channelName);
		_server->sendData(sd, errMsg);
		return;
	}

	// Guard OPERATOR
	if (!channel->isOperator(&sender))
	{
		std::cerr << "ERROR: " << sender << " [" << sd << "] ERR_CHANOPRIVSNEEDED (482) - " << cmd.getName() << std::endl;
		std::string errMsg = errChanOpPrivsNeeded(_server->getName(), senderNick, channelName);
		_server->sendData(sd, errMsg);
		return;
	}

	User *targetUser = _server->getUserByNickname(targetNick);

	if (!targetUser)
	{
		std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NOSUCHNICK (401) - " << cmd.getName() << std::endl;
		std::string errMsg = errNoSuchNick(_server->getName(), senderNick, targetNick);
		_server->sendData(sd, errMsg);
		return;
	}

	if (!channel->isUser(targetUser))
	{
		std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_USERNOTINCHANNEL (441) - " << cmd.getName() << std::endl;
		std::string	errMsg = errUserOnChannel(_server->getName(), senderNick, targetNick, channelName);
		_server->sendData(sd, errMsg);
		return;
	}

	channel->removeUser(targetUser);

	std::string kickMsg = ":" + senderNick + "!" + sender.getUsername() + "@" + _server->getName()
		+ " KICK " + channelName + " " + targetNick + " :" + reason + "\r\n";

	channel->broadcastAll(_server, kickMsg);

	int targetFd = targetUser->getFd();
	_server->sendData(targetFd, kickMsg);
}
