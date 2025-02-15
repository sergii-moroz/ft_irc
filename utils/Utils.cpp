/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:00:16 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/15 16:10:26 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

// ==========================================
// Constructors
// ==========================================

Utils::Utils()
{
	std::cout << "Utils: Default constructor called" << std::endl;
}

Utils::Utils(Utils const & copy)
{
	std::cout << "Utils: Copy constructor called" << std::endl;
	*this = copy;
}

// ==========================================
// Destructor
// ==========================================

Utils::~Utils()
{
	std::cout << "Utils: Destructor called" << std::endl;
}

// ==========================================
// Assignment operator=
// ==========================================

Utils &	Utils::operator=(Utils const & rhs)
{
	if (this != &rhs)
	{
		std::cout << "Utils: Assignment operator called" << std::endl;
		// do nothing
	}
	return (*this);
}

// ==========================================
// Static functions
// ==========================================

std::string	Utils::trim(std::string const & s)
{
	size_t	start = s.find_first_not_of("\f\n\r\t\v ");
	if (start == std::string::npos)
		return (s); // no content
	size_t	end	= s.find_last_not_of("\f\n\r\t\v ");
	size_t	range = end - start + 1;
	return (s.substr(start, range));
}

bool	Utils::isInteger(std::string const & s)
{
	std::istringstream iss(Utils::trim(s));
	int	i;
	iss >> i;
	return (!iss.fail() && iss.eof());
}

int	Utils::strToInteger(std::string const & s)
{
	std::istringstream	iss(Utils::trim(s));
	int	i;
	iss >> i;
	return (i);
}

int	Utils::validatePort(char const *arg)
{
	if (!Utils::isInteger(arg))
	{
		std::cerr << "ERROR: First argument is not an integer!" << std::endl;
		// Server::usage();
		return (-1);
	}

	int port = Utils::strToInteger(arg);
	if (port < 0)
	{
		std::cerr << "ERROR: Port number should be a positive value." << std::endl;
		return (-1);
	}

	if (port < 1024)
	{
		std::cerr << "ERROR: Port numbers from 0 to 1023 are reserved for common TCP/IP applications." << std::endl;
		return (-1);
	}

	return (port);
}

std::string	Utils::validatePass(char const *arg)
{
	std::string	pass(arg);
	std::cout << "\"" << pass << "\"" << std::endl;

	if (pass.empty())
	{
		std::cerr << "ERROR: Password cannot be empty!" << std::endl;
		return (std::string(""));
	}

	if (pass.length() < 6) {
		std::cerr << "ERROR: Password must be at least 6 characters long!" << std::endl;
		return (std::string(""));
	}

	size_t	pos = pass.find_first_of("\f\n\r\t\v ");
	if (pos != std::string::npos)
	{
		std::cerr << "ERROR: Password cannot contain whitespace characters!" << std::endl;
		return (std::string(""));
	}

	return (pass);
}
