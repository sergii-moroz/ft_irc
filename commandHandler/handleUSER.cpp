/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleUSER.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:25:00 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/17 10:25:00 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandHandler.hpp"

void	CommandHandler::handleUSER(int sd, const Command &cmd)
{
	std::vector< std::vector<std::string> >	params = cmd.getParameters();
	if (!params.empty()) {
		_server->getUser(sd).setUsername(params[0][0]);
		_server->getUser(sd).setRealname(cmd.getTail());
		std::cout << "INFO: " << _server->getUser(sd) << std::endl; // <-- Server Side Logging
		// User is registered --> send Welcome message
		std::string	msg = ":localhost 001 root :Welcome to the IRC Network, <nickname>!<user>@<host>\r\n";
		_server->sendData(sd, msg);
	}
}
