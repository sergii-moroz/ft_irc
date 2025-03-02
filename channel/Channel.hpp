/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:50:06 by smoreron          #+#    #+#             */
/*   Updated: 2025/03/02 12:47:02 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <set>

# include "Server.hpp"
# include "User.hpp"

# define INVITE_MODE	0
# define TOPIC_MODE		1
# define KEY_MODE		2
# define LIMIT_MODE		3

class Server;
class User;

class Channel
{
	public:
		// Constructors and destructor
		Channel();
		Channel(std::string const &name);
		Channel(Channel const &);
		Channel &	operator=(Channel const &);
		~Channel();

		// Getters
		const std::string &		getName() const;
		const std::string &		getTopic() const;
		const std::string &		getKey() const;
		bool					getMode(char) const;
		size_t					getUserLimit() const;
		size_t					getUsersCount() const;
		std::set<User *>		getUsers() const;
		std::set<User *>		getOperators() const;
		std::set<User *>		getInvitedUsers() const;


		// Setters
		void					setName(std::string const &);
		void					setTopic(std::string const &);
		void					setKey(std::string const &);
		void					setUserLimit(size_t limit);
		void					setMode(char mode, bool value);

		// Resource operations
		void 					addUser(User *user);
		void 					removeUser(User *user);
		void 					addOperator(User *user);
		void 					removeOperator(User *user);
		void 					addInvitedUser(User *user);
		void 					removeInvitedUser(User *user);
		bool 					isUser(User *user) const;
		bool 					isOperator(User *user) const;
		bool 					isInvitedUser(User *user) const;
		std::string				getMembersList() const;
		std::string				getOperatorsList() const;
		std::string				getInvitedList() const;
		std::string				getModeList() const;
		std::string				getModeArgs() const;

		// Channel operations
		void					broadcastAll(Server *server, std::string const &message) const;
		void					broadcast(Server *server, std::string const &message, int excludeFd) const;


	private:
		std::string				_name;
		std::string				_topic;
		std::string				_key;
		size_t					_userLimit;
		char					_mode;
		std::set<User *>		_users;
		std::set<User *>		_operators;
		std::set<User *>		_invited;
};

std::ostream &	operator<<(std::ostream &, Channel const &);

#endif
