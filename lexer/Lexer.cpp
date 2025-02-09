/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:36:14 by olanokhi          #+#    #+#             */
/*   Updated: 2025/02/09 16:51:39 by olanokhi         ###   ########.fr       */
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
	if (it >= _text.end())
		return (Token(END, ""));
	if (*it == '\r')
		return (Token(CR, "\r"));
	if (*it == '\n')
		return (Token(LF, "\n"));
	if (*it == ':')
		return (Token(COLON, ":"));
	if (*it == ' ')
		return (Token(SPACE, " "));
	if (std::isdigit(*it))
		return (Token(DIGIT, std::string(1, *it)));
	if (std::isalpha(*it))
		return (Token(ALPHA, std::string(1, *it)));
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

void	Lexer::eat(TokenType type)
{
	if (_currentToken.getType() == type)
		getNextToken();
	else
		throw std::runtime_error("ERROR: Wrong tokenType");
}

void	Lexer::crlf(void)
{
	std::cout << "Lexer: crlf() called" << std::endl;
	eat(CR);
	eat(LF);
}

void	Lexer::spaces(void)
{
	std::cout << "Lexer: spaces() called" << std::endl;
	eat(SPACE);
	while (_currentToken.getType() == SPACE)
		eat(SPACE);
}

std::string Lexer::letters(void)
{
	std::string s;
	while (_currentToken.getType() == ALPHA)
	{
		s += _currentToken.getValue();
		eat(ALPHA);
	}
	return (s);
}

std::string Lexer::threeDigits(void)
{
	std::string s;
	for (int i = 0; i < 3; i++)
	{
		// if (_currentToken.getType() == DIGIT)
		// {
			s += _currentToken.getValue();
			eat(DIGIT);
		// }
		// else
		// 	throw std::runtime_error("ERROR: Expected 3 digits");
	}
	return (s);
}

std::string Lexer::command(void)
{
	std::string s;
	if (_currentToken.getType() == ALPHA)
		return (letters());
	else if (_currentToken.getType() == DIGIT)
		return (threeDigits());
	else
		throw std::runtime_error("ERROR: Lexer: Wrong syntax at command rule!");
}