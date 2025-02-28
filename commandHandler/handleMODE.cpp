/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleMODE.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:02:40 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/28 11:49:12 by olanokhi         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void CommandHandler::handleMODE(int sd, Command const & cmd)
// {
// 	(void)sd;
// 	(void)cmd;
// }
{
	User &user = _server->getUser(sd);
	std::string nick = user.getNickname();

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0)) {
		std::string msg = ":" + _server->getName() + " 461 " + nick
						  + " MODE :Not enough parameters\r\n";
		_server->sendData(sd, msg);
		return;
	}

	std::string target = cmd.getParamAtPos(0, 0);

	if (!target.empty() && target[0] == '#') {
		Channel *channel = _server->getChannelByName(target);
		if (!channel) {
			std::string msg = ":" + _server->getName() + " 403 " + nick
							  + " " + target + " :No such channel\r\n";
			_server->sendData(sd, msg);
			return;
		}

		if (!channel->isOperator(&user)) {
			std::string msg = ":" + _server->getName() + " 482 " + nick
							  + " " + channel->getName()
							  + " :You're not channel operator\r\n";
			_server->sendData(sd, msg);
			return;
		}

		if (cmd.hasParamAtPos(1, 0)) {
			std::string modes = cmd.getParamAtPos(1, 0);

			bool add = true;
			for (size_t i = 0; i < modes.size(); ++i) {
				char c = modes[i];
				if (c == '+') {
					add = true;
					continue;
				} else if (c == '-') {
					add = false;
					continue;
				}
				switch (c) {
					case 'i': // invite-only
						channel->setMode(INVATE_MODE, add);
						break;
					case 't': // topic lock
						channel->setMode(TOPIC_MODE, add);
						break;
					case 'k': // channel key (password)
						channel->setMode(KEY_MODE, add);
						if (add) {
							if (cmd.hasParamAtPos(2, 0)) {
								channel->setKey(cmd.getParamAtPos(2, 0));
							}
						} else {
							channel->setKey("");
						}
						break;
					case 'l': // user limit
						channel->setMode(LIMIT_MODE, add);
						if (add) {
							if (cmd.hasParamAtPos(2, 0)) {
								channel->setUserLimit(std::atoi(cmd.getParamAtPos(2, 0).c_str()));
							}
						} else {
							channel->setUserLimit(0); // 0 — without limit
						}
						break;
					// case 'b': // ban
					// 	if (add) {

					// 		if (cmd.hasParamAtPos(2, 0)) {
					// 			channel->_banList.insert(cmd.getParamAtPos(2, 0));
					// 		}
					// 	} else {
					// 		if (cmd.hasParamAtPos(2, 0)) {
					// 			channel->_banList.erase(cmd.getParamAtPos(2, 0));
					// 		}
					// 	}
					// 	break;
					default:
						break;
				}
			}

			std::string broadcastMsg = ":" + nick + "!" + user.getUsername()
				+ "@" + _server->getName()
				+ " MODE " + target + " " + modes + "\r\n";
			channel->broadcastAll(_server, broadcastMsg);
		}
		else {
			std::string currentModes = "+";
			if (channel->getMode(INVATE_MODE))
				currentModes += "i";
			if (channel->getMode(TOPIC_MODE))
				currentModes += "t";
			if (channel->getMode(KEY_MODE))
				currentModes += "k";
			if (channel->getMode(LIMIT_MODE))
				currentModes += "l";
			// if (channel->getMode(BAN_MODE))
			// 	currentModes += "b";
			std::string msg = ":" + _server->getName() + " 324 " + nick
							  + " " + channel->getName() + " " + currentModes
							  + " " + channel->getKey() + "\r\n"; // + " " + std::itoa(channel->getUserLimit())
			_server->sendData(sd, msg);
		}
	}
	else {
		std::string msg = ":" + _server->getName() + " 501 " + nick
						  + " :Unknown MODE target\r\n";
		_server->sendData(sd, msg);
	}
}
