/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:07:13 by olanokhi          #+#    #+#             */
/*   Updated: 2025/02/04 23:32:08 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

// Default constructor
Token::Token()
{
	std::cout << "Token: Default constructor called" << std::endl;
}

// Custom constructor
Token::Token(tokenType type, std::string value) : _type(type), _value(value)
{
	std::cout << "Token: Custom constructor called" << std::endl;
}

// Copy constructor ?
Token::Token(const Token& copy)
{
	std::cout << "Token: Copy constructor called" << std::endl;
	*this = copy;
}

// Destructor
Token::~Token()
{
	std::cout << "Token: Destructor called" << std::endl;
}

// Overloaded assignment operator
Token & Token::operator=(Token const & rhs)
{
	if (this != &rhs) {
		std::cout << "Token: Assignment operator=() called" << std::endl;
		this->_type = rhs.getType();
		this->_value.assign(rhs.getValue());
	}
	return (*this);
}

std::string Token::getValue() const
{
	return this->_value;
}

tokenType Token::getType() const
{
	return this->_type;
}

std::string Token::getTypeString() const
{
	const char *typeStrings[] = {
		"CR",
		"LF",
		"SPACE",
		"COLON",
		"DIGIT",
		"ALPHA",
		"UNDEFINED",
		"END"
	};
	if (this->_type >= sizeof(typeStrings) / sizeof(typeStrings[0]))
	{
		std::cout << "ERROR: Invalid token type!" << std::endl;
		return "UNKNOWN";
	}
	return typeStrings[this->_type];
}

std::ostream & operator<<(std::ostream & out, Token const & t)
{
	out << "Token: { type: " << t.getTypeString() << ", value: \"" << t.getValue() << "\" }";
	return (out);
}