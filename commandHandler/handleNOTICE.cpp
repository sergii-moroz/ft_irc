/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleNOTICE.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:23:13 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/28 21:33:10 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void CommandHandler::handleNOTICE(int sd, Command const &cmd)
{
	User &		sender = _server->getUser(sd);
	std::string	senderNick = sender.getNickname();

	// Guard REGISTERED
	if (!sender.getStatus(REGISTERED))
	{
		std::cerr << "ERROR: " << senderNick << " [" << sd << "] Command \"" << cmd.getName() << "\" available only for registered users." << std::endl;
		return ;
	}

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cerr << "ERROR: " << senderNick << " [" << sd << "] ERR_NEEDMOREPARAMS (461)" << std::endl;
		return ;
	}

	std::string	target = cmd.getParamAtPos(0, 0);

	if (!target.empty() && target[0] == '#')
	{
		Channel	*channel = _server->getChannelByName(target);
		if (!channel)
		{
			std::cerr << "ERROR: " << senderNick << " [" << sd << "] ERR_NOSUCHCHANNEL (403)" << std::endl;
			return ;
		}

		if (!channel->isUser(&sender))
		{
			std::cerr << "ERROR: " << senderNick << " [" << sd << "] ERR_NOTONCHANNEL (442)" << std::endl;
			return ;
		}

		std::string	msg = ":" + senderNick + "!" + sender.getUsername()
			+ "@" + _server->getName()
			+ " NOTICE " + target + " :" + cmd.getTail() + "\r\n";
		channel->broadcast(_server, msg, sd);
	}
	else
	{
		User	*recipient = _server->getUserByNickname(target);
		if (!recipient)
		{
			std::cerr << "ERROR: " << senderNick << " [" << sd << "] ERR_NOSUCHNICK (401)" << std::endl;
			return;
		}

		int	recipientSD = recipient->getFd();
		std::string	msg = ":" + senderNick + "!" + sender.getUsername()
						+ "@" + _server->getName()
						+ " NOTICE " + target + " :" + cmd.getTail() + "\r\n";
		_server->sendData(recipientSD, msg);
	}
}
