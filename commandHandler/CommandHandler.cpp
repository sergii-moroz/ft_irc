/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:21:11 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/13 09:21:11 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandHandler.hpp"

// ==========================================
// Constructors
// ==========================================

CommandHandler::CommandHandler()
{
	std::cout << "CommandHandler: default constructor called" << std::endl;
}

CommandHandler::CommandHandler(CommandHandler const & copy)
{
	std::cout << "CommandHandler: Copy constructor called" << std::endl;
	*this = copy;
}

// ==========================================
// Destructor
// ==========================================

CommandHandler::~CommandHandler()
{
	std::cout << "CommandHandler: destructor called" << std::endl;
}

// ==========================================
// Assignment operator=()
// ==========================================

CommandHandler &	CommandHandler::operator=(CommandHandler const & rhs)
{
	if (this != &rhs)
	{
		std::cout << "CommandHandler: Assignment operator called" << std::endl;
		// copy attributes here
	}
	return (*this);
}
