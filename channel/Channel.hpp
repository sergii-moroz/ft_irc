/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:50:06 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/25 21:33:42 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <set>
# include <map>

# include "User.hpp"

// +i: Channel is invite-only; only invited users can join
#define MODE_INVITE_ONLY  0x01  
// +t: Topic lock; only channel operators can change the topic
#define MODE_TOPIC_LOCK   0x02  

class Server;
class Channel
{
	public:
		Channel();
		Channel(std::string const &name);
		Channel(Channel const &);
		Channel &	operator=(Channel const &);
		~Channel();

		const std::string & getName() const;
		std::string const &	getTopic() const;
		void	setName(std::string const &);
		void	setTopic(std::string const &);

		void addUser(int userFd);
		void removeUser(int userFd);
		bool hasUser(int userFd) const;
		std::set<int> getUsers() const;

		void addOperator(int userFd);
		void removeOperator(int userFd);
		bool isOperator(int userFd) const;

		void setPassword(const std::string &pass);
		const std::string & getPassword() const;
		void setUserLimit(size_t limit);
		size_t getUserLimit() const;
		void addBan(const std::string &nick);
		void removeBan(const std::string &nick);
		bool isBanned(const std::string &nick) const;

		void broadcast(Server &server, const std::string &senderNick,
		               const std::string &message, int excludeFd);
		void broadcastRaw(Server &server, const std::string &msg);

		std::string	_name;
		std::string	_topic;
		char		_mode;  


		std::set<int> _userFds;
		std::set<int> _operators;

		std::string        _password;
		size_t             _userLimit;
		std::set<std::string> _banList;

	private:
		

	
};

#endif
