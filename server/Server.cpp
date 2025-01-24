/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:05:10 by smoroz            #+#    #+#             */
/*   Updated: 2025/01/21 09:26:18 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// ==========================================
// Constructors
// ==========================================

Server::Server() : _port(PORT), _pass(PASS)
{
	std::cout << "Server: Default constructor called" << std::endl;
}

Server::Server(Server const & copy)
{
	std::cout << "Server: Copy constructor called" << std::endl;
	*this = copy;
}

Server::Server(int port, std::string & pass) : _port(port), _pass(pass)
{
	std::cout << "Server: Custom constructor called" << std::endl;
}

// ==========================================
// Destructor
// ==========================================

Server::~Server()
{
	std::cout << "Server: Destructor called" << std::endl;
}

// ==========================================
// Assignment operator=()
// ==========================================

Server &	Server::operator=(Server const & rhs)
{
	if (this != &rhs)
	{
		std::cout << "Server: Assignment operator called" << std::endl;
		_port = rhs.getPort();
		_pass = rhs.getPass();
	}
	return (*this);
}

// ==========================================
// Getter
// ==========================================

int	Server::getPort(void) const
{
	return (_port);
}

std::string	Server::getPass(void) const
{
	return (_pass);
}

// ==========================================
// Methods
// ==========================================
