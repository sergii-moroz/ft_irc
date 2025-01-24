/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:05:10 by smoroz            #+#    #+#             */
/*   Updated: 2025/01/20 21:05:10 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// ==========================================
// Constructors
// ==========================================

Server::Server()
{
	std::cout << "Server: Default constructor called" << std::endl;
}

Server::Server(Server const & copy)
{
	std::cout << "Server: Copy constructor called" << std::endl;
	*this = copy;
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
	}
	return (*this);
}
