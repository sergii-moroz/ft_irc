/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePASS.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:52:56 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/16 15:52:56 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandHandler.hpp"

void	CommandHandler::handlePASS(int sd, Command const & cmd)
{
	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cout << "ERROR: user [" << sd << "] ERR_NEEDMOREPARAMS (461)" << std::endl;
		std::string	msg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, msg);
		_server->clearClient(sd);
	}
	else if (cmd.hasParamAtPos(_server->getPass(), 0, 0))
	{
		_server->getUser(sd).setPassOK(true);
		std::cout << "INFO: user [" << sd << "] password accepted" << std::endl;
	}
	else
	{
		std::cout << "ERROR: user [" << sd << "] ERR_PASSWDMISMATCH (464)" << std::endl;
		std::string	msg = errPasswdMismatch(_server->getName());
		_server->sendData(sd, msg);
		_server->clearClient(sd);
	}
}
