/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePART.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:36:10 by smoroz            #+#    #+#             */
/*   Updated: 2025/03/02 11:15:19 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

void	CommandHandler::handlePART(int sd, Command const & cmd)
{
	User &		user = _server->getUser(sd);
	std::string	nickname = user.getNickname();

	// Guard REGISTERED
	if (!user.getStatus(REGISTERED))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] Command \"" << cmd.getName() << "\" available only for registered users." << std::endl;
		// optional send error here
		return;
	}

	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NEEDMOREPARAMS (461)" << cmd.getName() << std::endl;
		std::string	msg = errNeedMoreParams(_server->getName(), cmd.getName());
		_server->sendData(sd, msg);
		return ;
	}

	std::string	channelName = cmd.getParamAtPos(0, 0);
	Channel		*channel = _server->getChannelByName(channelName);

	if (!channel)
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NOSUCHCHANNEL (403) - " << cmd.getName() << std::endl;
		std::string msg = errNoSuchChannel(_server->getName(), nickname, channelName);
		_server->sendData(sd, msg);
		return;
	}

	if (!channel->isUser(&user))
	{
		std::cerr << "ERROR: " << nickname << " [" << sd << "] ERR_NOTONCHANNEL (442) - " << cmd.getName() << std::endl;
		std::string msg = errNotOnChannel(_server->getName(), nickname, channelName);
		_server->sendData(sd, msg);
		return;
	}

	std::cout << "INFO: " << nickname << " [" << sd << "] leave " << channelName << std::endl;

	std::string	msg = ":" + nickname + "!" + user.getUsername()
	+ "@" + _server->getName()
	+ " PART " + channelName + " :Goodbye everyone!\r\n";
	channel->broadcastAll(_server, msg);
	channel->removeUser(&user);
}
