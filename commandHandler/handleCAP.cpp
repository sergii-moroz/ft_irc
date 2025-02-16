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
	std::vector< std::vector<std::string> >	params = cmd.getParameters();
	if (params.empty())
	{
		std::string	msg = ":localhost 461\r\n";
		_server->sendData(sd, msg);
		// close connection ???
	}
	else if (params[0][0] == "LS")
	{
		std::string	msg = ":localhost CAP * LS :\r\n";
		_server->sendData(sd, msg);
	}
}
