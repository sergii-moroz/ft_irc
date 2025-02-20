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

void CommandHandler::handlePRIVMSG(int sd, Command const &cmd)
{
	User &		sender = _server->getUser(sd);
	std::string	senderNick = sender.getNickname();

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cout << "ERROR: " + senderNick + " [" << sd << "] ERR_NEEDMOREPARAMS (461)" << std::endl;
		std::string	msg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, msg);
		return;
	}

	/*if (!target.empty() && target[0] == '#')
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
	}*/
	else
	{
		std::string	recipientNick = cmd.getParamAtPos(0, 0);
		User		*recipient = _server->getUserByNickname(recipientNick);
		if (!recipient)
		{
			std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NOSUCHNICK (401)" << std::endl;
			std::string	msg = errNoSuchNick(_server->getName(), senderNick, recipientNick);
			_server->sendData(sd, msg);
			return ;
		}
		int	recipientSD = recipient->getFd();
		std::string	msg = ":" + senderNick + "!" + sender.getUsername()
			+ "@" + _server->getName()
			+ " PRIVMSG " + recipientNick + " :" + cmd.getTail() + "\r\n";
		_server->sendData(recipientSD, msg);
	}
}
