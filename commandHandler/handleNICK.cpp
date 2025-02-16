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
	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::string	nickname = _server->getUser(sd).getNickname();
		if (nickname.empty())
			nickname = "*";
		std::cout << "ERROR: user [" << sd << "] ERR_NONICKNAMEGIVEN (431)" << std::endl;
		std::string	msg = errNoNicknameGiven(_server->getName(), nickname);
		_server->sendData(sd, msg);
	}
	else
	{
		User &	user = _server->getUser(sd);
		std::string	oldNickname = user.getNickname();
		std::string	newNickname = cmd.getParamAtPos(0, 0);
		// check here if new nickname is valid
		User	*found = _server->getUserByNickname(newNickname);

		if (!found)
		{
			user.setNickname(newNickname);
			std::cout << "INFO: " << oldNickname << " [" << sd << "] has change nickname to " << newNickname << std::endl;
		}
		else
		{
			std::cout << "ERROR: " << oldNickname << " [" << sd << "] ERR_NICKNAMEINUSE (433)" << std::endl;
			std::string	msg = errNicknameInUse(_server->getName(), oldNickname, newNickname);
			_server->sendData(sd, msg);
		}
		// std::cout << "INFO: " << _server->getUser(sd) << std::endl; // <-- Server Side Logging
	}
}
