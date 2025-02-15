/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:58:45 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/15 16:10:14 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <sstream>
# include <string>

class Utils
{
	public:
		~Utils();
		static int			validatePort(char const *arg);
		static std::string	validatePass(char const *arg);

	private:
		Utils();
		Utils(Utils const &);
		Utils &	operator=(Utils const &);

		static std::string	trim(std::string const & s);
		static bool			isInteger(std::string const & s);
		static int			strToInteger(std::string const & s);
};

#endif
