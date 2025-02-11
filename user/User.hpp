/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:04:09 by smoreron          #+#    #+#             */
/*   Updated: 2025/01/27 20:59:02 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef USER_HPP
# define USER_HPP

# include <string>
# include <iostream>

class User
{
	public:
		User();
		User(User const &);
		User(int fd);
		~User();
		User &		operator=(User const &);

		int			getFd(void) const;
		bool		isRegistered(void) const;
		bool		isPassOK(void) const;
		std::string const &	getNickname(void) const;
		std::string const &	getUsername(void) const;
		std::string const &	getRealname(void) const;

		void		setRegistered(bool val);
		void		setPassOK(bool val);
		void		setNickname(std::string const &);
		void		setUsername(std::string const &);
		void		setRealname(std::string const &);

	private:
		int			_fd;
		bool		_registered;
		bool		_passOK;
		std::string	_nickname;
		std::string	_username;
		std::string	_realname;
};

std::ostream &	operator<<(std::ostream &, User const &);

#endif
