/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleCAP.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:34:55 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/28 17:22:29 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void	CommandHandler::handleCAP(int sd, Command const & cmd)
{
	User &		user = _server->getUser(sd);
	std::string	nickname = user.getNickname();

	// Registration guard
	if (user.getStatus(REGISTERED))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_ALREADYREGISTERED (462)" << std::endl;
		std::string	msg = errAlreadyRegistered(_server->getName(), nickname);
		_server->sendData(sd, msg);
		return ;
	}

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NEEDMOREPARAMS (461) " << cmd.getName() << std::endl;
		std::string	msg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, msg);
		_server->clearClient(sd);
	}
	else if(cmd.hasParamAtPos("LS", 0, 0))
	{
		std::string	msg = ":" + _server->getName() + " CAP * LS :\r\n";
		_server->sendData(sd, msg);
		user.setStatus(CAP_LS, true);
	}
	else if (cmd.hasParamAtPos("END", 0, 0))
	{
		if (!user.getStatus(CAP_LS))
		{
			std::cerr << "ERROR: " << nickname << " [" << sd << "] \"CAP END\" should be sent after \"CAP LS\" command" << std::endl;
			return ;
		}

		user.setStatus(CAP_END, true);

		// Registration is completed
		if (!user.getStatus(REGISTERED) && user.getStatus() == END_REG)
		{
			user.setStatus(REGISTERED, true);
			std::string	msg = rplWelcome(_server->getName(), nickname);
			_server->sendData(sd, msg);
		}
	}
}
