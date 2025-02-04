/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:07:13 by olanokhi          #+#    #+#             */
/*   Updated: 2025/02/04 22:54:27 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

// Default constructor
Token::Token() {
	std::cout << "Token: Default constructor called" << std::endl;
}

// Copy constructor
Token::Token(const Token& copy) {
	std::cout << "Token: Copy constructor called" << std::endl;
	*this = copy;
}

// Destructor
Token::~Token() {
	std::cout << "Token: Destructor called" << std::endl;
}

// Overloaded assignment operator
Token& Token::operator=(const Token& other) {
	if (this != &other) {
		std::cout << "Token: Assignment operator=() called" << std::endl;
	}
	return *this;
}

