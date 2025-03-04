/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePRIVMSG.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:23:13 by smoreron          #+#    #+#             */
/*   Updated: 2025/03/04 15:37:03 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void CommandHandler::handlePRIVMSG(int sd, Command const &cmd)
{
	User &		sender = _server->getUser(sd);
	std::string	senderNick = sender.getNickname();

	// Guard REGISTERED
	if (!sender.getStatus(REGISTERED))
	{
		std::cerr << "ERROR: " << senderNick << " [" << sd << "] Command \"" << cmd.getName() << "\" available only for registered users." << std::endl;
		std::string	msg = errNotRegistered(_server->getName(), senderNick);
		_server->sendData(sd, msg);
		return ;
	}

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cerr << "ERROR: " << senderNick << " [" << sd << "] ERR_NEEDMOREPARAMS (461) - PRIVMSG" << std::endl;
		std::string msg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, msg);
		return ;
	}

	std::string	args = cmd.getParamAtPos(0, 0);
	std::string	text = cmd.getTail();

	if (Utils::trim(text).empty())
	{
		std::cerr << "ERROR: " << senderNick << " [" << sd << "] ERR_NOTEXTTOSEND (412) - PRIVMSG" << std::endl;
		std::string	msg = errNoTextToSend(_server->getName(), senderNick);
		_server->sendData(sd, msg);
	}

	std::vector<std::string>	targets = splitByComma(args, 0);

	for (size_t i = 0; i < targets.size(); ++i)
		sendSingleMsg(targets[i], text, sender);
}

void	CommandHandler::sendSingleMsg(std::string const & target, std::string const & text, User & sender) const
{
	std::string	senderNick = sender.getNickname();
	int			sd = sender.getFd();

	if (!target.empty() && target[0] == '#')
	{
		Channel	*channel = _server->getChannelByName(target);
		if (!channel)
		{
			std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NOSUCHCHANNEL (403) - PRIVMSG " << target << std::endl;
			std::string	errMsg = errNoSuchChannel(_server->getName(), senderNick, target);
			_server->sendData(sd, errMsg);
			return ;
		}

		if (!channel->isUser(&sender))
		{
			std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NOTONCHANNEL (442) - PRIVMSG " << target << std::endl;
			std::string	errMsg = errNotOnChannel(_server->getName(), senderNick, target);
			_server->sendData(sd, errMsg);
			return ;
		}

		std::string	msg = ":" + senderNick + "!" + sender.getUsername() + "@" + _server->getName()
			+ " PRIVMSG " + target + " :" + text + "\r\n";
		channel->broadcast(_server, msg, sd);
	}
	else
	{
		User	*recipient = _server->getUserByNickname(target);
		if (!recipient)
		{
			std::cout << "ERROR: " << senderNick << " [" << sd << "] ERR_NOSUCHNICK (401) - PRIVMSG " << target << std::endl;
			std::string	msg = errNoSuchNick(_server->getName(), senderNick, target);
			_server->sendData(sd, msg);
			return;
		}

		int	recipientSD = recipient->getFd();
		std::string	msg = ":" + senderNick + "!" + sender.getUsername() + "@" + _server->getName()
						+ " PRIVMSG " + target + " :" + text + "\r\n";
		_server->sendData(recipientSD, msg);
	}
}
