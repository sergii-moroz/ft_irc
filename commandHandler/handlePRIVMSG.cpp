/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePRIVMSG.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:23:13 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/23 19:28:49 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void CommandHandler::handlePRIVMSG(int sd, Command const &cmd)
{
	User &sender = _server->getUser(sd);
	std::string senderNick = sender.getNickname();
	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NEEDMOREPARAMS (461)" << std::endl;
		std::string msg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, msg);
		return;
	}
	

	std::string target  = cmd.getParamAtPos(0, 0);
	std::string message = cmd.getTail();  

	if (!target.empty() && target[0] == '#')
	{
		Channel *channel = _server->getChannelByName(target);
		if (!channel)
		{
			std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NOSUCHNICK/CHANNEL (401)" << std::endl;
			std::string errMsg = ":" + _server->getName() + " 401 " + senderNick + " " + target 
							   + " :No such nick/channel\r\n";
			_server->sendData(sd, errMsg);
			return;
		}

		if (!channel->hasUser(sd))
		{
			std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NOTONCHANNEL (442)" << std::endl;
			std::string errMsg = ":" + _server->getName() + " 442 " + senderNick + " " + target
							   + " :You're not on that channel\r\n";
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
			std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NOSUCHNICK (401)" << std::endl;
			std::string msg = errNoSuchNick(_server->getName(), senderNick, target);
			_server->sendData(sd, msg);
			return;
		}

		int recipientSD = recipient->getFd();
		std::string msg = ":" + senderNick + "!" + sender.getUsername()
						+ "@" + _server->getName()
						+ " PRIVMSG " + target + " :" + message + "\r\n";
		_server->sendData(recipientSD, msg);
	}
}
