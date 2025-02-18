/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePRIVMSG.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:23:13 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/19 00:17:55 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "Command.hpp"
#include <iostream>



void CommandHandler::handlePRIVMSG(int sd, Command const &cmd)
{
	
	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		
		std::string errMsg = errNeedMoreParams(_server->getName(), "PRIVMSG");
		_server->sendData(sd, errMsg);
		return;
	}

	
	User &sender = _server->getUser(sd);
	std::string senderNick = sender.getNickname();
	if (senderNick.empty())
		senderNick = "*";

	
	std::string target = cmd.getParamAtPos(0, 0);

	
	
	
	
	std::string message = cmd.getTail(); 
	
	if (message.empty() && cmd.hasParamAtPos(0, 1))
		message = cmd.getParamAtPos(0, 1);

	
	if (!target.empty() && target[0] == '#')
	{
		Channel *channel = _server->getChannelByName(target);
		if (!channel)
		{
			
			std::string errMsg = ":" + _server->getName() + " 401 " + senderNick + " " 
							   + target + " :No such channel\r\n";
			_server->sendData(sd, errMsg);
			return;
		}
		
		channel->broadcast(*_server, senderNick, message, sd);
	}
	else
	{
		
		User *recipient = _server->getUserByNickname(target);
		if (!recipient)
		{
			
			std::string errMsg = ":" + _server->getName() + " 401 " + senderNick + " " 
							   + target + " :No such nick\r\n";
			_server->sendData(sd, errMsg);
			return;
		}
		
		std::string msg = ":" + senderNick + " PRIVMSG " + target + " :" + message + "\r\n";
		_server->sendData(recipient->getFd(), msg);
	}
}
	