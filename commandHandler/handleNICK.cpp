/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleNICK.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:05:14 by smoroz            #+#    #+#             */
/*   Updated: 2025/03/01 21:43:19 by smoroz           ###   ########.fr       */
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
		// optional send error here
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
			std::string	msg = ":" + nickname + " NICK :" + newNickname + "\r\n";
			_server->sendData(sd, msg);
			user.setStatus(NICK, true);

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
