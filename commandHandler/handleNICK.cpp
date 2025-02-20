/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleNICK.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:05:14 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/16 19:51:07 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandHandler.hpp"

void	CommandHandler::handleNICK(int sd, Command const & cmd)
{
	User &		user = _server->getUser(sd);
	std::string	nickname = user.getNickname();

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NONICKNAMEGIVEN (431)" << std::endl;
		std::string	msg = errNoNicknameGiven(_server->getName(), nickname);
		_server->sendData(sd, msg);
	}
	else
	{
		std::string	newNickname = cmd.getParamAtPos(0, 0);
		// check here if new nickname is valid
		User	*found = _server->getUserByNickname(newNickname);

		if (!found)
		{
			std::cout << "INFO: " << nickname << " [" << sd << "] has change nickname to " << newNickname << std::endl;
			user.setNickname(newNickname);
			std::string	msg = ":" + nickname + " NICK :" + newNickname + "\r\n";
			_server->sendData(sd, msg);
		}
		else
		{
			std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NICKNAMEINUSE (433)" << std::endl;
			std::string	msg = errNicknameInUse(_server->getName(), nickname, newNickname);
			_server->sendData(sd, msg);
		}
	}
}
