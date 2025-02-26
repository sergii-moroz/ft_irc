/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:07:13 by olanokhi          #+#    #+#             */
/*   Updated: 2025/02/26 14:40:35 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

// Default constructor
Token::Token()
{
	// std::cout << "Token: Default constructor called" << std::endl;
}

// Custom constructor
Token::Token(TokenType type, std::string value) : _type(type), _value(value)
{
	// std::cout << "Token: Custom constructor called" << std::endl;
}

// Copy constructor ?
Token::Token(const Token& copy)
{
	// std::cout << "Token: Copy constructor called" << std::endl;
	*this = copy;
}

// Destructor
Token::~Token()
{
	// std::cout << "Token: Destructor called" << std::endl;
}

// Overloaded assignment operator
Token & Token::operator=(Token const & rhs)
{
	if (this != &rhs) {
		// std::cout << "Token: Assignment operator=() called" << std::endl;
		this->_type = rhs.getType();
		this->_value.assign(rhs.getValue());
	}
	return (*this);
}

std::string Token::getValue() const
{
	return this->_value;
}

TokenType Token::getType() const
{
	return this->_type;
}

std::string Token::getTypeString() const
{
	static const std::string v[] = {
		"CR", "LF", "SPACE", "COLON", "DIGIT", "ALPHA", "UNDEFINED", "EOF"
	};
	static const size_t v_size = 8;  // Number of elements in the array

	if (static_cast<size_t>(_type) >= v_size)
	{
		std::cerr << "ERROR: Invalid token type!" << std::endl;
		return "UNKNOWN";
	}
	return v[_type];
}

std::ostream & operator<<(std::ostream & out, Token const & t)
{
	out << "Token: { type: " << t.getTypeString() << ", value: \"" << t.getValue() << "\" }";
	return (out);
}
