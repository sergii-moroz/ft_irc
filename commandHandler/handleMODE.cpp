/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleMODE.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:02:40 by smoreron          #+#    #+#             */
/*   Updated: 2025/03/02 13:55:57 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void CommandHandler::handleMODE(int sd, Command const & cmd)
{
	User &		user = _server->getUser(sd);
	std::string	nickname = user.getNickname();

	// Guard REGISTERED
	if (!user.getStatus(REGISTERED))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] Command \"" << cmd.getName() << "\" available only for registered users." << std::endl;
		// optional send error here
		return;
	}

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0)) {
		std::string msg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, msg);
		return;
	}

	std::string target = cmd.getParamAtPos(0, 0);

	if (!target.empty() && target[0] == '#')
	{
		// Handle Channel's mode
		Channel *channel = _server->getChannelByName(target);

		if (!channel)
		{
			std::cout << "ERROR: " << nickname << " [" << sd << "] ERR_NOSUCHCHANNEL (403)" << std::endl;
			std::string	msg = errNoSuchChannel(_server->getName(), nickname, target);
			_server->sendData(sd, msg);
			return;
		}

		if (cmd.hasParamAtPos(1, 0))
		{
			// Setter (Only Operator area)
			if (!channel->isOperator(&user))
			{
				std::string msg = errChanOpPrivsNeeded(_server->getName(), nickname, target);
				_server->sendData(sd, msg);
				return;
			}

			std::string modes = cmd.getParamAtPos(1, 0);

			bool add = true;
			size_t	iarg = 2;
			for (size_t i = 0; i < modes.size(); ++i) {
				char c = modes[i];
				if (c == '+') {
					add = true;
					continue;
				} else if (c == '-') {
					add = false;
					continue;
				}
				switch (c)
				{
					case 'i': // invite-only
						channel->setMode(INVITE_MODE, add);
						break;
					case 't': // topic lock
						channel->setMode(TOPIC_MODE, add);
						break;
					case 'k': // channel key (password)
						if (add)
						{
							if (cmd.hasParamAtPos(iarg, 0))
							{
								std::string	password = Utils::validatePass(cmd.getParamAtPos(iarg, 0).c_str());
								if (!password.empty())
								{
									channel->setMode(KEY_MODE, true);
									channel->setKey(password);
								}
							}
							++iarg;
						}
						else
						{
							channel->setMode(KEY_MODE, false);
							channel->setKey("");
						}
						break;
					case 'l': // user limit
						if (add)
						{
							if (cmd.hasParamAtPos(iarg, 0))
							{
								channel->setMode(LIMIT_MODE, true);
								channel->setUserLimit(std::atoi(cmd.getParamAtPos(iarg, 0).c_str()));
							}
							++iarg;
						}
						else
						{
							channel->setMode(LIMIT_MODE, false);
							channel->setUserLimit(0); // 0 — without limit
						}
						break;
					default:
						break;
				}
			}

			std::string broadcastMsg = ":" + nickname + "!" + user.getUsername()
				+ "@" + _server->getName()
				+ " MODE " + target + " " + modes + "\r\n";
			channel->broadcastAll(_server, broadcastMsg);
		}
		else
		{
			// Getter
			std::string msg = rplChannelModeIs(_server->getName(), nickname, channel);
			_server->sendData(sd, msg);
		}

		// DEBUG
		std::cout << *channel << std::endl;
	}
	else
	{
		// Handle User's mode
		std::string msg = errUModeUnknownFlag(_server->getName(), nickname);
		_server->sendData(sd, msg);
	}
}
