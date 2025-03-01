/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:51:11 by smoreron          #+#    #+#             */
/*   Updated: 2025/03/01 21:10:24 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"

Channel::Channel() : _name(""), _topic(" "), _key(""), _userLimit(0),  _mode(0)
{
	// std::cout << "Channel: Default constructor called" << std::endl;
}

Channel::Channel(const std::string &name) : _name(name), _topic(" "), _key(""), _userLimit(0), _mode(0)
{
	// std::cout << "Channel: Named constructor called" << std::endl;
}

Channel::Channel(const Channel &other)
{
	*this = other;
}

Channel::~Channel()
{
	// std::cout << "Channel: Destructor called" << std::endl;
}

Channel &Channel::operator=(const Channel &other)
{
	if (this != &other)
	{
		_name		= other._name;
		_topic		= other._topic;
		_key		= other._key;
		_users		= other._users;
		_operators	= other._operators;
		_userLimit	= other._userLimit;
		_invited	= other._invited;
		_mode		= other._mode;
	}
	return (*this);
}

// Getters
const std::string & Channel::getName() const
{
	return (_name);
}

std::string const & Channel::getTopic() const
{
	return (_topic);
}

std::string const & Channel::getKey() const
{
	return (_key);
}

bool Channel::getMode(char key) const
{
	return ((_mode >> key) & 1);
}

size_t Channel::getUserLimit() const
{
	return (_userLimit);
}

std::set<User *> Channel::getUsers() const
{
	return (_users);
}

std::set<User *> Channel::getOperators() const
{
	return (_operators);
}

std::set<User *> Channel::getInvitedUsers() const
{
	return (_invited);
}

// Setters
void Channel::setName(std::string const &name)
{
	_name = name;
}

void Channel::setTopic(std::string const &topic)
{
	_topic = topic;
}

void Channel::setKey(std::string const &key)
{
	_key = key;
}

void Channel::setUserLimit(size_t limit)
{
	_userLimit = limit;
}

void Channel::setMode(char key, bool value)
{
	if (((_mode >> key) & 1) != value)
		_mode ^= (1 << key);
}

// Resource operations
void Channel::addUser(User *user)
{
	_users.insert(user);
	user->joinChannel(this);
}

void Channel::removeUser(User *user)
{
	_users.erase(user);
	user->leaveChannel(this);
}

void Channel::addOperator(User *user)
{
	_operators.insert(user);
}

void Channel::removeOperator(User *user)
{
	_operators.erase(user);
}

void Channel::addInvitedUser(User *user)
{
	_invited.insert(user);
}

void Channel::removeInvitedUser(User *user)
{
	_invited.erase(user);
}

bool Channel::isUser(User *user) const
{
	return (_users.find(user) != _users.end());
}

bool Channel::isOperator(User *user) const
{
	return (_operators.find(user) != _operators.end());
}

bool Channel::isInvitedUser(User *user) const
{
	return (_invited.find(user) != _invited.end());
}

std::string Channel::getMembersList() const
{
	std::string membersList;
	for (std::set<User *>::const_iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (isOperator(*it))
			membersList += "@";
		membersList += (*it)->getNickname();
		membersList += " ";
	}
	return (membersList);
}

std::string	Channel::getModeList() const
{
	static std::string	modies = "itkl";
	std::string	modiesList = "+";
	for(size_t i=0; i<=LIMIT_MODE; ++i)
	{
		if (getMode(i))
			modiesList += modies[i];
	}
	return (modiesList);
}

std::string	Channel::getModeArgs() const
{
	std::ostringstream os;
	std::string args;

	if (getMode(KEY_MODE))
		args += "???";

	if (getMode(LIMIT_MODE))
	{
		os << getUserLimit();
		if (!args.empty())
			args += " ";
		args += os.str();
	}

	return (args);
}

// Channel operations
void Channel::broadcastAll(Server *server, std::string const &message) const
{
	for (std::set<User *>::const_iterator it = _users.begin(); it != _users.end(); it++)
	{
		server->sendData((*it)->getFd(), message);
	}
}

void Channel::broadcast(Server *server, std::string const &message, int excludeFd) const
{
	for (std::set<User *>::const_iterator it = _users.begin(); it != _users.end(); it++)
	{
		int	sd = (*it)->getFd();
		if (sd != excludeFd)
			server->sendData(sd, message);
	}
}
