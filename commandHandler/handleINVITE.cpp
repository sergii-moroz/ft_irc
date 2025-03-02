/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleINVITE.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:43:58 by smoreron          #+#    #+#             */
/*   Updated: 2025/03/02 19:40:27 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


#include "CommandHandler.hpp"

void CommandHandler::handleINVITE(int sd, Command const & cmd)
{
	User &user = _server->getUser(sd);
	std::string nick = user.getNickname();

	// Guard REGISTERED
	if (!user.getStatus(REGISTERED))
	{
		std::cerr << "ERROR: " << nick << " [" << sd << "] Command \"" << cmd.getName() << "\" available only for registered users." << std::endl;
		std::string	msg = errNotRegistered(_server->getName(), nick);
		_server->sendData(sd, msg);
		return ;
	}

	if (cmd.isParamEmpty()
		|| !cmd.hasParamAtPos(0, 0)
		|| !cmd.hasParamAtPos(1, 0))
	{
		std::cerr << "ERROR: " <<  nick << " [" << sd << "] ERR_NEEDMOREPARAMS (461) - " << cmd.getName() << std::endl;
		std::string	errMsg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, errMsg);
		return;
	}

	std::string targetNick  = cmd.getParamAtPos(0, 0);
	std::string channelName = cmd.getParamAtPos(1, 0);

	Channel *channel = _server->getChannelByName(channelName);
	if (!channel)
	{
		std::cerr << "ERROR: " << nick << " [" << sd << "] ERR_NOSUCHCHANNEL (403) - " << cmd.getName() << std::endl;
		std::string	errMsg = errNoSuchChannel(_server->getName(), nick, channelName);
		_server->sendData(sd, errMsg);
		return;
	}

	if (!channel->isUser(&user))
	{
		std::cerr << "ERROR: " << nick << " [" << sd << "] ERR_NOTONCHANNEL (442) - " << cmd.getName() << std::endl;
		std::string	errMsg = errNotOnChannel(_server->getName(), nick, channelName);
		_server->sendData(sd, errMsg);
		return;
	}

	if (channel->getMode(INVITE_MODE) && !channel->isOperator(&user))
	{
		std::cerr << "ERROR: " << nick << " [" << sd << "] ERR_CHANOPRIVSNEEDED (482) - " << cmd.getName() << std::endl;
		std::string errMsg = errChanOpPrivsNeeded(_server->getName(), nick, channelName);
		_server->sendData(sd, errMsg);
		return;
	}

	User	*invitedUser = _server->getUserByNickname(targetNick);

	if (!invitedUser)
	{
		std::cout << "ERROR: " << nick << " [" << sd << "] ERR_NOSUCHNICK (401)" << std::endl;
		std::string	msg = errNoSuchNick(_server->getName(), nick, targetNick);
		_server->sendData(sd, msg);
		return;
	}
	else
	{
		if (channel->isUser(invitedUser))
		{
			std::cerr << "ERROR: " << nick << " [" << sd << "] ERR_USERONCHANNEL (443) - " << cmd.getName() << std::endl;
			std::string	errMsg = errUserOnChannel(_server->getName(), nick, targetNick, channelName);
			_server->sendData(sd, errMsg);
			return;
		}
	}

	channel->addInvitedUser(invitedUser);

	std::string rplMsg = rplInviting(_server->getName(), nick, targetNick, channelName);
	_server->sendData(sd, rplMsg);

	std::string inviteMsg = ":" + nick + "!" + user.getUsername() + "@" + _server->getName()
		+ " INVITE " + targetNick + " " + channelName + "\r\n";
	_server->sendData(invitedUser->getFd(), inviteMsg);

}
