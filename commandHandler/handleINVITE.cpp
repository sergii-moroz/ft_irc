/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleINVITE.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:43:58 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/26 02:13:08 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


#include "CommandHandler.hpp"

void CommandHandler::handleINVITE(int sd, Command const & cmd)
{
	User &user = _server->getUser(sd);
	std::string nick = user.getNickname();

		
		
	if (cmd.isParamEmpty()
		|| !cmd.hasParamAtPos(0, 0)  	
		|| !cmd.hasParamAtPos(1, 0)) 	
	{
			
		std::string errMsg = ":" + _server->getName() + " 461 "
							 + nick + " INVITE :Not enough parameters\r\n";
		_server->sendData(sd, errMsg);
		return;
	}

		
	std::string targetNick  = cmd.getParamAtPos(0, 0);
	std::string channelName = cmd.getParamAtPos(1, 0);

		
	User *invitedUser = _server->getUserByNickname(targetNick);
	if (!invitedUser)
	{
			
		std::string errMsg = ":" + _server->getName() + " 401 "
							 + nick + " " + targetNick
							 + " :No such nick/channel\r\n";
		_server->sendData(sd, errMsg);
		return;
	}

		
	Channel *channel = _server->getChannelByName(channelName);
	if (!channel)
	{
			
		std::string errMsg = ":" + _server->getName() + " 403 "
							 + nick + " " + channelName
							 + " :No such channel\r\n";
		_server->sendData(sd, errMsg);
		return;
	}

		
	if (!channel->isOperator(sd))
	{
			
		std::string errMsg = ":" + _server->getName() + " 482 "
							 + nick + " " + channelName
							 + " :You're not channel operator\r\n";
		_server->sendData(sd, errMsg);
		return;
	}

		
	std::string rplMsg = ":" + _server->getName() + " 341 "
						 + nick + " " + targetNick + " " + channelName + "\r\n";
	_server->sendData(sd, rplMsg);

		
	channel->addInvited(targetNick);

		
	std::string inviteMsg = ":" + nick + "!" + user.getUsername()
						   + "@" + _server->getName()
						   + " INVITE " + targetNick
						   + " :" + channelName + "\r\n";
	_server->sendData(invitedUser->getFd(), inviteMsg);

		
		
}
	