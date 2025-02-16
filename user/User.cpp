/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:11:32 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/11 18:49:42 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "User.hpp"

User::User() : _fd(-1), _registered(false), _passOK(false),
	_nickname("*"), _username(""), _realname("") {}

User::User(int fd) : _fd(fd), _registered(false), _passOK(false),
	_nickname("*"), _username(""), _realname("") {}

User::User(User const & other)
{
	*this = other;
}

// ==========================================
// Destructor
// ==========================================

User::~User() {}

// ==========================================
// Assignment operator=()
// ==========================================

User &	User::operator=(User const & other)
{
	if (this != &other)
	{
		_fd = other.getFd();
		_registered = other.isRegistered();
		_passOK = other.isPassOK();
		_nickname = other.getNickname();
		_username = other.getUsername();
		_realname = other.getRealname();
	}
	return (*this);
}

// ==========================================
// Getters / Setters
// ==========================================

int	User::getFd(void) const
{
	return (_fd);
}

bool	User::isRegistered(void) const
{
	return (_registered);
}

bool	User::isPassOK(void) const
{
	return (_passOK);
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

std::string	User::getNextCommand(void)
{
	size_t	pos = _buffer.find("\r\n");

	if (pos == std::string::npos)
		return ("");

	std::string	s = _buffer.substr(0, pos + 2);
	_buffer.erase(0, pos + 2);

	return (s);
}

void	User::setRegistered(bool val)
{
	_registered = val;
}

void	User::setPassOK(bool val)
{
	_passOK = val;
}

void	User::setNickname(std::string const & nick)
{
	_nickname = nick;
}

void	User::setUsername(std::string const & user)
{
	_username = user;
}

void	User::setRealname(std::string const & real)
{
	_realname = real;
}

void	User::addToBuffer(std::string const & msg)
{
	_buffer += msg;
}

// ==========================================
// Overload operator<<
// ==========================================

std::ostream &	operator<<(std::ostream & out, User const & ref)
{
	out << "User: { " << std::endl
		<< std::string(3, ' ') << "nickname: " << ref.getNickname() << std::endl
		<< std::string(3, ' ') << "username: " << ref.getUsername() << std::endl
		<< std::string(3, ' ') << "realname: " << ref.getRealname() << std::endl
		<< std::string(3, ' ') << "sock desc: " << ref.getFd() << std::endl
		<< std::string(3, ' ') << "registered: " << ref.isRegistered() << std::endl
		<< std::string(3, ' ') << "authenticated: " << ref.isPassOK() << std::endl
		<< "}";
	return (out);
}
