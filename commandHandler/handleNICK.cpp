/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleNICK.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:05:14 by smoroz            #+#    #+#             */
/*   Updated: 2025/03/04 15:31:47 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void	CommandHandler::handleNICK(int sd, Command const & cmd)
{
	User &		user = _server->getUser(sd);
	std::string	nickname = user.getNickname();

	// Guard password
	if (!user.getStatus(PASSWORD))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] MUST send a PASS command before sending the NICK / USER combination." << std::endl;
		std::string	msg = errNotRegistered(_server->getName(), nickname);
		_server->sendData(sd, msg);
		return;
	}

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NONICKNAMEGIVEN (431)" << std::endl;
		std::string	msg = errNoNicknameGiven(_server->getName(), nickname);
		_server->sendData(sd, msg);
	}
	else
	{
		std::string	newNickname = cmd.getParamAtPos(0, 0);

		// check new nickname is valid
		if (!Utils::isValidNickname(newNickname, USERLEN))
		{
			std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_ERRONEUSNICKNAME (432)" << std::endl;
			std::string	msg = errErroneusNickName(_server->getName(), nickname, newNickname);
			_server->sendData(sd, msg);
			return ;
		}

		User	*found = _server->getUserByNickname(newNickname);

		if (!found)
		{
			std::cout << "INFO: " << nickname << " [" << sd << "] has change nickname to " << newNickname << std::endl;
			user.setNickname(newNickname);
			user.setStatus(NICK, true);

			// send message to all unique users in all channel
			std::string	msg = ":" + nickname + "!" + user.getUsername() + "@" + _server->getName()
				+ " NICK :" + newNickname + "\r\n";
			std::set<User *>	uniqueUsers = user.getUniqueUsersFromJoinedChannels();

			for (std::set<User *>::const_iterator it = uniqueUsers.begin(); it != uniqueUsers.end(); ++it)
				_server->sendData((*it)->getFd(), msg);

			if (uniqueUsers.empty())
				_server->sendData(sd, msg);

			// Registration is completed
			if (!user.getStatus(REGISTERED) && user.getStatus() == END_REG)
			{
				user.setStatus(REGISTERED, true);
				std::string	msg = rplWelcome(_server->getName(), nickname);
				_server->sendData(sd, msg);
			}
		}
		else
		{
			std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NICKNAMEINUSE (433)" << std::endl;
			std::string	msg = errNicknameInUse(_server->getName(), nickname, newNickname);
			_server->sendData(sd, msg);
		}
	}
}
