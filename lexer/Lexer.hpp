/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:36:04 by olanokhi          #+#    #+#             */
/*   Updated: 2025/02/10 15:28:31 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

# include <iostream>
# include <string>
# include <vector>

# include "Token.hpp"
# include "Command.hpp"

class Lexer

{
	public:
		Lexer();
		~Lexer();
		Lexer(Lexer const &);
		Lexer(std::string);
		Lexer & operator=(Lexer const &);
		
		std::string              getText() const;
		void                     setText(std::string);
		void                     getNextToken();
		const Token             &getCurrentToken() const;
		TokenType                peekTokenType();
		void                     eat(TokenType type);
		void                     crlf(void);
		void                     spaces(void);
		std::string              letters(void);
		std::string              threeDigits(void);
		std::string              command(void);
		bool                     isspcrlfcl(void);
		std::string              nospcrlfcl(void);
		std::string              trailing(void);
		void                     message(void);
		std::vector<std::string> parameters(Command &cmd);
		std::vector<std::string> middle(void);

	private:
		Token                    getTokenAt(std::string::iterator);
		
		std::string             _text;
		std::string::iterator   _it;
		Token                   _currentToken;
};

#endif