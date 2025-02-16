/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleCAP.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:34:55 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/16 12:34:55 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandHandler.hpp"

void	CommandHandler::handleCAP(int sd, Command const & cmd)
{
	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0) || !cmd.hasParamAtPos(1, 0))
	{
		std::string	msg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, msg);
		_server->clearClient(sd);
	}
	else if(cmd.hasParamAtPos("LS", 0, 0))
	{
		std::string	msg = ":" + _server->getName() + " CAP * LS :\r\n";
		_server->sendData(sd, msg);
	}
}
