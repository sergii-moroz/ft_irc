/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:51:11 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/25 20:56:57 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"
#include "Server.hpp"
#include <iostream>
#include <cstdlib> // для std::atoi, если потребуется

Channel::Channel() :
	_name(""),
	_topic("unknown"),
	_mode(0),
	_userLimit(0)  // 0 означает без ограничения
{
	std::cout << "Channel: Default constructor called" << std::endl;
}

Channel::Channel(const std::string &name) :
	_name(name),
	_topic("unknown"),
	_mode(0),
	_userLimit(0)
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
		_name      = other._name;
		_topic     = other._topic;
		_mode      = other._mode;
		_userFds   = other._userFds;
		_operators = other._operators;

		_password  = other._password;
		_userLimit = other._userLimit;
		_banList   = other._banList;
	}
	return (*this);
}

const std::string & Channel::getName() const
{
	return (_name);
}

std::string const & Channel::getTopic() const
{
	return (_topic);
}

void Channel::setName(std::string const & name)
{
	_name = name;
}

void Channel::setTopic(std::string const & topic)
{
	_topic = topic;
}

// --------------------------------------------------
// Работа с пользователями
// --------------------------------------------------

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

std::set<int> Channel::getUsers() const
{
	return _userFds;
}

// --------------------------------------------------
// Операторы канала
// --------------------------------------------------

void Channel::addOperator(int userFd)
{
	_operators.insert(userFd);
}

void Channel::removeOperator(int userFd)
{
	_operators.erase(userFd);
}

bool Channel::isOperator(int userFd) const
{
	return (_operators.find(userFd) != _operators.end());
}

// --------------------------------------------------
// Параметры канала (пароль, лимит, бан-лист)
// --------------------------------------------------

void Channel::setPassword(const std::string &pass)
{
	_password = pass;
}
const std::string & Channel::getPassword() const
{
	return _password;
}

void Channel::setUserLimit(size_t limit)
{
	_userLimit = limit;
}
size_t Channel::getUserLimit() const
{
	return _userLimit;
}

void Channel::addBan(const std::string &nick)
{
	_banList.insert(nick);
}
void Channel::removeBan(const std::string &nick)
{
	_banList.erase(nick);
}
bool Channel::isBanned(const std::string &nick) const
{
	return (_banList.find(nick) != _banList.end());
}

// --------------------------------------------------
// Широковещательные методы
// --------------------------------------------------

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

void Channel::broadcastRaw(Server &server, const std::string &msg)
{
	for (std::set<int>::iterator it = _userFds.begin(); it != _userFds.end(); ++it)
	{
		server.sendData(*it, msg);
	}
}
