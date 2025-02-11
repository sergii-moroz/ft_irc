/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:11:32 by smoreron          #+#    #+#             */
/*   Updated: 2025/01/27 20:59:40 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "User.hpp"

User::User() : _fd(-1), _registered(false), _passOK(false) {}

User::User(int fd) : _fd(fd), _registered(false), _passOK(false) {}

User::User(const User &other) {
	*this = other;
}

User::~User() {}

// ==========================================
// Assignment operator=()
// ==========================================

User &	User::operator=(User const & other)
{
	if (this != &other)
	{
		_fd = other._fd;
		_registered = other._registered;
		_passOK = other._passOK;
		_nickname = other._nickname;
		_username = other._username;
		_realname = other._realname;
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
