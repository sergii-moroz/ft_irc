/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:58:45 by smoroz            #+#    #+#             */
/*   Updated: 2025/03/05 10:10:47 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <cstdlib>
# include <sstream>
# include <string>
# include <ctime>

class Utils
{
	public:
		~Utils();
		static int			validatePort(char const *arg);
		static std::string	validatePass(char const *arg);
		static std::string	validateUsername(std::string const &, size_t);
		static bool			isValidNickname(std::string const &, size_t);
		static bool			isValidChannelname(std::string const &, size_t);
		static int			validateInteger(std::string const & s);
		static std::string	trim(std::string const & s);

	private:
		Utils();
		Utils(Utils const &);
		Utils &	operator=(Utils const &);

		static bool			isInteger(std::string const & s);
		static int			strToInteger(std::string const & s);
		static std::string	generateRandomString(size_t);
};

#endif
