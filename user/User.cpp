/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:11:32 by smoreron          #+#    #+#             */
/*   Updated: 2025/03/01 21:48:03 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "User.hpp"

// Constructors
User::User() : _fd(-1), _status(0), _nickname("*"), _username(""), _realname("") {}

User::User(int fd) : _fd(fd), _status(0), _nickname("*"), _username(""), _realname("") {}

User::User(User const & other)
{
	*this = other;
}

User::~User() {}

User &	User::operator=(User const & other)
{
	if (this != &other)
	{
		_fd = other.getFd();
		_status = other._status;
		_nickname = other.getNickname();
		_username = other.getUsername();
		_realname = other.getRealname();
		_buffer = other._buffer;
		_joinedChannels = other._joinedChannels;
	}
	return (*this);
}

// Getters

int	User::getFd(void) const
{
	return (_fd);
}

char	User::getStatus() const
{
	return (_status);
}

bool	User::getStatus(char status) const
{
	return ((_status >> status) & 1);
}

std::string const &	User::getNickname(void) const
{
	return (_nickname);
}

std::string const &	User::getUsername(void) const
{
	return (_username);
}

std::string const &	User::getRealname(void) const
{
	return (_realname);
}

std::set<Channel *> const &	User::getJoinedChannels(void) const
{
	return (_joinedChannels);
}

// Setters
void	User::setStatus(char key, bool value)
{
	if (((_status >> key) & 1) != value)
		_status ^= (1 << key);
}

void	User::setNickname(std::string const & nick)
{
	_nickname = nick;
}

void	User::setUsername(std::string const & user)
{
	_username = Utils::validateUsername(user, USERLEN);
}

void	User::setRealname(std::string const & real)
{
	_realname = real;
}

// Methods
void	User::addToBuffer(std::string const & msg)
{
	_buffer += msg;
}

void	User::joinChannel(Channel * channel)
{
	_joinedChannels.insert(channel);
}

void	User::leaveChannel(Channel * channel)
{
	_joinedChannels.erase(channel);
}

std::string	User::getNextCommand(void)
{
	size_t	pos = _buffer.find("\r\n");

	if (pos == std::string::npos)
		return ("");

	std::string	s = _buffer.substr(0, pos + 2);
	_buffer.erase(0, pos + 2);

	return (s);
}
// ==========================================
// Overload operator<<
// ==========================================

std::ostream &	operator<<(std::ostream & out, User const & ref)
{
	out << "User: { " << std::endl
		<< std::string(2, ' ') << "nickname: " << ref.getNickname() << std::endl
		<< std::string(2, ' ') << "username: " << ref.getUsername() << std::endl
		<< std::string(2, ' ') << "realname: " << ref.getRealname() << std::endl
		<< std::string(2, ' ') << "sock desc: " << ref.getFd() << std::endl
		<< std::string(2, ' ') << "is CAP LS setted: " << ref.getStatus(CAP_LS) << std::endl
		<< std::string(2, ' ') << "is CAP END setted: " << ref.getStatus(CAP_END) << std::endl
		<< std::string(2, ' ') << "is authenticated: " << ref.getStatus(PASSWORD) << std::endl
		<< std::string(2, ' ') << "is Nick Setted: " << ref.getStatus(NICK) << std::endl
		<< std::string(2, ' ') << "is User Setted: " << ref.getStatus(USER) << std::endl
		<< std::string(2, ' ') << "is registered: " << ref.getStatus(REGISTERED) << std::endl
		<< std::string(2, ' ') << "joined channel: " << ref.getJoinedChannels().size() << std::endl
		<< std::string(2, ' ') << "{ " << std::endl << std::string(4, ' ');
		for (std::set<Channel *>::const_iterator it = ref.getJoinedChannels().begin(); it != ref.getJoinedChannels().end(); it++)
		{
			out << (*it)->getName() << " ";
		}
		out << std::endl << std::string(2, ' ') << "}" << std::endl << "}";
	return (out);
}
