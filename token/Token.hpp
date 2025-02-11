/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:36:05 by olanokhi          #+#    #+#             */
/*   Updated: 2025/02/09 11:26:01 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <iostream>
# include <string>
# include <array>

enum TokenType
{
	CR,
	LF,
	SPACE,
	COLON,
	DIGIT,
	ALPHA,
	UNDEFINED,
	END
};;

class Token
{
	public:
		Token();
		Token(TokenType, std::string);
		Token(const Token &copy);
		~Token();
		Token & operator=(Token const &);

		TokenType		getType() const;
		std::string		getValue() const;
		std::string		getTypeString() const;
		
	private:
		TokenType	_type;
		std::string	_value;
};

std::ostream & operator<<(std::ostream &, Token const &);

#endif

