/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:36:14 by olanokhi          #+#    #+#             */
/*   Updated: 2025/02/04 23:40:08 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.hpp"

Lexer::Lexer()
{
	std::cout << "Lexer: Default constructor called" << std::endl;
}

Lexer::~Lexer()
{
	std::cout << "Lexer: Destructor called" << std::endl;
}

Lexer::Lexer(Lexer const & copy)
{
	std::cout << "Lexer: Copy constructor called" << std::endl;
	*this = copy;
}

Lexer & Lexer::operator=(Lexer const & rhs)
{
	std::cout << "Lexer: Assignation operator called" << std::endl;
	if (this != &rhs)
	{
		std::cout << "Lexer: Assignment operator=() called" << std::endl;
	}
	return (*this);
}