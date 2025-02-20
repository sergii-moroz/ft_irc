/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:51:11 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/19 00:52:22 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"

Channel::Channel() : _name(""), _topic("unknown"), _mode(0)
{
	std::cout << "Channel: Default constructor called" << std::endl;
}

Channel::Channel(const std::string &name) : _name(name), _topic("unknown"), _mode(0)
{
	std::cout << "Channel: Named constructor called" << std::endl;
}

Channel::Channel(const Channel &other)
{
	*this = other;
}

Channel::~Channel()
{
	std::cout << "Channel: Destructor called" << std::endl;
}

Channel &Channel::operator=(const Channel &other)
{
	if (this != &other)
	{
		std::cout << "Channel: Assignment operator called" << std::endl;
		_name = other._name;
		_topic = other._topic;
		_mode = other._mode;
		_userFds = other._userFds;
	}
	return (*this);
}

const std::string & Channel::getName() const
{
	return (_name);
}

std::string const &	Channel::getTopic() const
{
	return (_topic);
}

void	Channel::setName(std::string const & name)
{
	_name = name;
}

void	Channel::setTopic(std::string const & topic)
{
	_topic = topic;
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

// void Channel::broadcast(Server &server, const std::string &senderNick,
// 						const std::string &message, int excludeFd)
// {
// 	std::string fullMsg = ":" + senderNick
// 						+ " PRIVMSG " + _name
// 						+ " :" + message
// 						+ "\r\n";
// 	for (std::set<int>::iterator it = _userFds.begin(); it != _userFds.end(); ++it)
// 	{
// 		if (*it == excludeFd)
// 			continue;
// 		server.sendData(*it, fullMsg);
// 	}
// }
