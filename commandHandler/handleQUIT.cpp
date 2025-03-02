/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleQUIT.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:08:32 by smoroz            #+#    #+#             */
/*   Updated: 2025/03/02 11:34:40 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void	CommandHandler::handleQUIT(int sd, Command const & cmd)
{
	User &		user = _server->getUser(sd);
	std::string	nickname = user.getNickname();

	std::set<Channel *>	joinedChannels = user.getJoinedChannels();
	for (std::set<Channel *>::const_iterator it=joinedChannels.begin(); it != joinedChannels.end(); ++it)
	{
		// std::cout << (*it)->getName() << std::endl;
		std::string	msg = ":" + nickname + "!" + user.getUsername()
			+ "@" + _server->getName()
			+  " QUIT " + ":Quit :" + cmd.getTail() + "\r\n";
		// (*it)->broadcast(_server, msg, sd);
		(*it)->broadcastAll(_server, msg);
		(*it)->removeUser(&user);
	}
	_server->clearClient(sd);
}
