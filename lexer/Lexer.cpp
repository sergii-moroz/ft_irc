/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:36:14 by olanokhi          #+#    #+#             */
/*   Updated: 2025/02/09 11:37:50 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer()
{
	std::cout << "Lexer: Default constructor called" << std::endl;
}

Lexer::~Lexer()
{
	std::cout << "Lexer: Destructor called" << std::endl;
}

Lexer::Lexer(std::string text) : _text(text), _it(_text.begin())
{
	std::cout << "Lexer: Custom constructor called" << std::endl;
	getNextToken();
}

Lexer::Lexer(Lexer const & copy)
{
	std::cout << "Lexer: Copy constructor called" << std::endl;
	*this = copy;
}

Lexer & Lexer::operator=(Lexer const & rhs)
{
	if (this != &rhs)
	{
		std::cout << "Lexer: Assignment operator=() called" << std::endl;
		setText(rhs.getText());
	}
	return (*this);
}

std::string Lexer::getText() const
{
	return (this->_text);
}

void	Lexer::setText(std::string text)
{
	_text.assign(text);
	this->_it = _text.begin();
}

Token	Lexer::getTokenAt(std::string::iterator it)
{
	std::cout << "Lexer: getTokenAt() called" << std::endl;

	// it's end of the string _text
	if (it >= _text.end())
		return (Token(END, ""));
	if (std::isdigit(*it))
		return (Token(DIGIT, std::string(1, *it)));
	return (Token(UNDEFINED, std::string(1, *it)));
}

const Token &Lexer::getCurrentToken() const
{
	return _currentToken;
}

void Lexer::getNextToken()
{
	std::cout << "Lexer: getNextToken() called" << std::endl;
	if (_it != _text.end())
	{
		_currentToken = getTokenAt(_it);
		++_it;
	}
	else
		_currentToken = Token(END, "");
}

TokenType	Lexer::peekTokenType()
{
	std::string::iterator it = _it;
	Token token = getTokenAt(it);
	return (token.getType());
}