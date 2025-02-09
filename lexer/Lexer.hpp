/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:36:04 by olanokhi          #+#    #+#             */
/*   Updated: 2025/02/09 11:37:27 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

# include <iostream>
# include <string>

# include "Token.hpp"

class Lexer

{
	public:
		Lexer();
		~Lexer();
		Lexer(Lexer const &);
		Lexer(std::string);
		Lexer & operator=(Lexer const &);
		
		std::string   getText() const;
		void          setText(std::string);
		void          getNextToken();
		const Token &getCurrentToken() const;
		TokenType     peekTokenType();
		
		
	private:
		Token         getTokenAt(std::string::iterator);
		
		std::string             _text;
		std::string::iterator   _it;
		Token                   _currentToken;

};

#endif