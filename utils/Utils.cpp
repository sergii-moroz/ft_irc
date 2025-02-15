/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:00:16 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/15 15:00:16 by smoroz           ###   ########.fr       */
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
