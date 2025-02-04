/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:36:05 by olanokhi          #+#    #+#             */
/*   Updated: 2025/02/04 22:51:02 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <iostream>

class Token
{
	public:
		Token();
		Token(const Token& other);
		~Token();
		Token& operator=(const Token& other);
};

#endif

