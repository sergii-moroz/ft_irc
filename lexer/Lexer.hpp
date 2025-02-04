/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:36:04 by olanokhi          #+#    #+#             */
/*   Updated: 2025/02/04 23:38:04 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

# include <iostream>

class Lexer
{
public:
	Lexer();
	~Lexer();
	Lexer(Lexer const &);
	Lexer & operator=(Lexer const &);
};

#endif