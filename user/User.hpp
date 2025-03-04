/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:04:09 by smoreron          #+#    #+#             */
/*   Updated: 2025/03/04 09:37:25 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef USER_HPP
# define USER_HPP

# include <set>
# include <string>
# include <iostream>

# include "Utils.hpp"
# include "Channel.hpp"

# define CAP_LS			0
# define CAP_END		1
# define PASSWORD		2
# define NICK			3
# define USER			4
# define REGISTERED		5
# define USERLEN		18
# define END_REG		31 // 2^4 + 2^3 + 2^2 + 2 + 1

class Channel;

class User
{
	public:
		// Constructors and destructor
		User();
		User(User const &);
		User(int fd);
		~User();
		User &		operator=(User const &);

		// Getters
		int					getFd(void) const;
		char				getStatus() const;
		bool				getStatus(char) const;
		std::string const &	getNickname(void) const;
		std::string const &	getUsername(void) const;
		std::string const &	getRealname(void) const;
		std::set<Channel *> const &	getJoinedChannels() const;
		std::set<User *>	getUniqueUsersFromJoinedChannels() const;

		// Setters
		void				setStatus(char, bool);
		void				setNickname(std::string const &);
		void				setUsername(std::string const &);
		void				setRealname(std::string const &);

		// Methods
		void				addToBuffer(std::string const &);
		void				joinChannel(Channel *);
		void				leaveChannel(Channel *);
		std::string			getNextCommand(void);

		// Deprecated
		// bool				isRegistered(void) const;
		// bool				isPassOK(void) const;
		// void				setRegistered(bool val);
		// void				setPassOK(bool val);

	private:
		int					_fd;
		char				_status;
		std::string			_nickname;
		std::string			_username;
		std::string			_realname;
		std::string			_buffer;
		std::set<Channel *>	_joinedChannels;
		// bool				_registered;
		// bool				_passOK;
};

std::ostream &	operator<<(std::ostream &, User const &);

#endif
