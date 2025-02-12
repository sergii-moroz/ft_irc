/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:36:14 by olanokhi          #+#    #+#             */
/*   Updated: 2025/02/10 15:28:03 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer()
{
	// std::cout << "Lexer: Default constructor called" << std::endl;
}

Lexer::~Lexer()
{
	// std::cout << "Lexer: Destructor called" << std::endl;
}

Lexer::Lexer(std::string text) : _text(text), _it(_text.begin())
{
	// std::cout << "Lexer: Custom constructor called" << std::endl;
	getNextToken();
}

Lexer::Lexer(Lexer const & copy)
{
	// std::cout << "Lexer: Copy constructor called" << std::endl;
	*this = copy;
}

Lexer & Lexer::operator=(Lexer const & rhs)
{
	if (this != &rhs)
	{
		// std::cout << "Lexer: Assignment operator=() called" << std::endl;
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
	// std::cout << "Lexer: getTokenAt() called" << std::endl;
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
	// std::cout << "Lexer: getNextToken() called" << std::endl;
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
	// std::cout << "Lexer: crlf() called" << std::endl;
	eat(CR);
	eat(LF);
}

void	Lexer::spaces(void)
{
	// std::cout << "Lexer: spaces() called" << std::endl;
	eat(SPACE);
	while (_currentToken.getType() == SPACE)
		eat(SPACE);
}

std::string Lexer::letters(void)
{
	// std::cout << "Lexer: letters() called" << std::endl;
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
	// std::cout << "Lexer: threeDigits() called" << std::endl;
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
	// std::cout << "Lexer: command() called" << std::endl;
	std::string s;
	if (_currentToken.getType() == ALPHA)
		return (letters());
	else if (_currentToken.getType() == DIGIT)
		return (threeDigits());
	else
		throw std::runtime_error("ERROR: Lexer: Wrong syntax at command rule!");
}

bool Lexer::isspcrlfcl(void)
{
	TokenType	t = _currentToken.getType();

	if (t == SPACE || t == CR || t == LF || t == COLON || t == END)
		return (true);
	return (false);
}

std::string Lexer::nospcrlfcl(void)
{
	std::string s;

	while (!isspcrlfcl())
	{
		s += _currentToken.getValue();
		eat(_currentToken.getType());
	}
	return (s);
}

std::vector<std::string>	Lexer::middle(void)
{
	std::vector<std::string>	v;
	std::string                 s;

	s += nospcrlfcl();
	v.push_back(s);
	s.clear();

	while (_currentToken.getType() == COLON || !isspcrlfcl())
	{
		if (_currentToken.getType() == COLON)
			eat(_currentToken.getType());
		else
		{
			s += nospcrlfcl();
			v.push_back(s);
			s.clear();
		}
	}
	return (v);
}

std::string Lexer::trailing(void)
{
	std::string s;

	// ":" / " " / nospcrlfcl means => not in [CR, LF, EOF]
	while (_currentToken.getType() != CR &&
			_currentToken.getType() != LF &&
			_currentToken.getType() != END)
	{
		if (_currentToken.getType() == COLON)
		{
			s += ":"; // save all??? or skip first and save all other???
			eat(COLON);
		}
		else if(_currentToken.getType() == SPACE)
		{
			s += " "; // replace many spaces with one.
			spaces();
		}
		else
			s += nospcrlfcl();
	}
	return (s);
}

std::vector<std::string>    Lexer::parameters(Command & cmd)
{
	std::vector<std::string>    v;

	while (_currentToken.getType() == SPACE)
	{
		spaces();
		if (!isspcrlfcl())
			cmd.addParam(middle());
		else if (_currentToken.getType() == COLON)
		{
			eat(COLON);
			cmd.setTail(trailing());
			break;
			// no need to break. Trailing should consume line till the end
		}
		else if (_currentToken.getType() == END)
		{
			break;
		}
		else
		{
			throw std::runtime_error("ERROR: Unexpected token in parameters");
		}
	}
	return (v);
}

Command	Lexer::message(void)
{
	Command cmd;

	cmd.setName(command());
	parameters(cmd);
	crlf();

	return (cmd);
}
