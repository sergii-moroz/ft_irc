/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:36:05 by olanokhi          #+#    #+#             */
/*   Updated: 2025/02/09 11:02:12 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <iostream>
# include <string>
# include <array>

enum tokenType
{
	CR,
	LF,
	SPACE,
	COLON,
	DIGIT,
	ALPHA,
	UNDEFINED,
	END
};

class Token
{
	public:
		Token();
		Token(tokenType, std::string);
		Token(const Token &copy);
		~Token();
		Token & operator=(Token const &);

		tokenType		getType() const;
		std::string		getValue() const;
		std::string		getTypeString() const;
		
	private:
		tokenType	_type;
		std::string	_value;
};

std::ostream & operator<<(std::ostream &, Token const &);

#endif

