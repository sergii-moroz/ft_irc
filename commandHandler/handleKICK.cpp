/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleKICK.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:23:38 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/27 14:25:29 by olanokhi         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"
#include "Server.hpp"
#include "Channel.hpp"


void CommandHandler::handleKICK(int sd, Command const & cmd)
{
	User &sender	   = _server->getUser(sd);
	std::string senderNick = sender.getNickname();




	if (cmd.isParamEmpty()
		|| !cmd.hasParamAtPos(0, 0)
		|| !cmd.hasParamAtPos(1, 0))
	{

		std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NEEDMOREPARAMS (461)" << std::endl;
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
		std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NOSUCHCHANNEL (403)" << std::endl;
		std::string errMsg = ":" + _server->getName() + " 403 "
						   + senderNick + " " + channelName
						   + " :No such channel\r\n";
		_server->sendData(sd, errMsg);
		return;
	}


	if (!channel->isUser(&sender))
	{
		std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NOTONCHANNEL (442)" << std::endl;
		std::string errMsg = ":" + _server->getName() + " 442 "
						   + senderNick + " " + channelName
						   + " :You're not on that channel\r\n";
		_server->sendData(sd, errMsg);
		return;
	}

	User *targetUser = _server->getUserByNickname(targetNick);
	if (!targetUser)
	{
		std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NOSUCHNICK (401)" << std::endl;
		std::string errMsg = errNoSuchNick(_server->getName(), senderNick, targetNick);
		_server->sendData(sd, errMsg);
		return;
	}

	if (!channel->isUser(targetUser))
	{
		std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_USERNOTINCHANNEL (441)" << std::endl;
		std::string errMsg = ":" + _server->getName() + " 441 "
						   + senderNick + " " + targetNick + " " + channelName
						   + " :They aren't on that channel\r\n";
		_server->sendData(sd, errMsg);
		return;
	}

	channel->removeUser(targetUser);

	std::string kickMsg = ":" + senderNick + " KICK "
						+ channelName + " " + targetNick
						+ " :" + reason + "\r\n";

	channel->broadcastAll(_server, kickMsg);

	int targetFd = targetUser->getFd();
	_server->sendData(targetFd, kickMsg);
}
