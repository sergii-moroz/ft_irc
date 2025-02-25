/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleMODE.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:02:40 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/25 21:31:03 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"


void CommandHandler::handleMODE(int sd, Command const & cmd)
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

		if (!channel->isOperator(sd)) {
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
						if (add) {
							channel->_mode |= MODE_INVITE_ONLY;
						} else {
							channel->_mode &= ~MODE_INVITE_ONLY;
						}
						break;
					case 't': // topic lock
						if (add) {
							channel->_mode |= MODE_TOPIC_LOCK;
						} else {
							channel->_mode &= ~MODE_TOPIC_LOCK;
						}
						break;
					case 'k': // password
						if (add) {
							if (cmd.hasParamAtPos(2, 0)) {
								channel->_password = cmd.getParamAtPos(2, 0);
							}
						} else {
							channel->_password.clear();
						}
						break;
					case 'l': // user limit
						if (add) {
							if (cmd.hasParamAtPos(2, 0)) {
								channel->_userLimit = std::atoi(cmd.getParamAtPos(2, 0).c_str());
							}
						} else {
							channel->_userLimit = 0; // 0 — without limit
						}
						break;
					case 'b': // ban
						if (add) {

							if (cmd.hasParamAtPos(2, 0)) {
								channel->_banList.insert(cmd.getParamAtPos(2, 0));
							}
						} else {
							if (cmd.hasParamAtPos(2, 0)) {
								channel->_banList.erase(cmd.getParamAtPos(2, 0));
							}
						}
						break;
					default:
						break;
				}
			}

			std::string broadcastMsg = ":" + nick + "!" + user.getUsername()
				+ "@" + _server->getName()
				+ " MODE " + target + " " + modes + "\r\n";
			channel->broadcastRaw(*_server, broadcastMsg);
		}
		else {
			std::string currentModes = "+";
			if (channel->_mode & MODE_INVITE_ONLY) currentModes += "i";
			if (channel->_mode & MODE_TOPIC_LOCK)  currentModes += "t";
			std::string msg = ":" + _server->getName() + " 324 " + nick
							  + " " + channel->getName() + " " + currentModes + "\r\n";
			_server->sendData(sd, msg);
		}
	}
	else {
		std::string msg = ":" + _server->getName() + " 501 " + nick
						  + " :Unknown MODE target\r\n";
		_server->sendData(sd, msg);
	}
}
	
