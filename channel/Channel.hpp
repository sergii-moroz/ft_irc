/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:50:06 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/23 15:07:48 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <set>

# include "User.hpp"


class Server;
class Channel
{
	public:
		Channel();
		~Channel();
		Channel(Channel const &);
		Channel(std::string const &);
		Channel &	operator=(Channel const &);

		const std::string & getName() const;
		std::string const &	getTopic() const;
		void	setName(std::string const &);
		void	setTopic(std::string const &);

		void addUser(int userFd);
		void removeUser(int userFd);
		bool hasUser(int userFd) const;
		std::set<int> getUsers() const;

		void broadcast(Server &server, const std::string &senderNick, const std::string &message, int excludeFd);

		void broadcastRaw(Server &server, const std::string &msg);


	private:
		std::string		_name;
		std::string		_topic;
		char			_mode;
		std::set<int>	_userFds;

};

#endif
