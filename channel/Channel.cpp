/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:51:11 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/19 00:15:33 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"
#include "Server.hpp"
#include <iostream>

Channel::Channel(const std::string &name)
: _name(name)
{
}

Channel::~Channel()
{
}

const std::string & Channel::getName() const
{
	return _name;
}

void Channel::addUser(int userFd)
{
	_userFds.insert(userFd);
}

void Channel::removeUser(int userFd)
{
	_userFds.erase(userFd);
}

bool Channel::hasUser(int userFd) const
{
	return (_userFds.find(userFd) != _userFds.end());
}

void Channel::broadcast(Server &server, const std::string &senderNick,
						const std::string &message, int excludeFd)
{
	std::string fullMsg = ":" + senderNick 
						+ " PRIVMSG " + _name 
						+ " :" + message 
						+ "\r\n";
	for (std::set<int>::iterator it = _userFds.begin(); it != _userFds.end(); ++it)
	{
		if (*it == excludeFd)
			continue; 
		server.sendData(*it, fullMsg);
	}
}
