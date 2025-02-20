/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:01:02 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/18 21:32:47 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <iostream>
# include <unistd.h>
# include <fcntl.h>
# include <csignal>
# include <poll.h>
# include <string>
# include <vector>
# include <map>
#include <cstring>

# include "User.hpp"
# include "Lexer.hpp"
# include "CommandHandler.hpp"
# include "Channel.hpp"

# define PORT	12345
# define PASS	"42Heilbronn"
# define NAME	"irc.42heilbron.de"

class Server
{
	public:
		Server();
		~Server();
		Server(Server const &);
		Server(int port, std::string & pass);
		Server &	operator=(Server const &);

		static void	usage(void);
		static void	signalHandler(int signum);

		int			getPort(void) const;
		std::string	getPass(void) const;
		std::string	getName(void) const;

		void		init(void);
		void		run(void);
		void		sendData(int sd, std::string & data);
		void		clearClient(int sd);
		User &		getUser(int sd);
		User		*getUserByNickname(std::string const &);

		//chanel
		Channel *	getChannelByName(std::string const &channelName);
		void		createChannel(std::string const &);
		// void		addChannel(Channel *channel);
		// Channel *	findOrCreateChannel(std::string const &channelName);

	private:
		void		handlePollIn(size_t i);
		void		handlePollHup(size_t & i);
		void		handlePollErr(size_t & i);
		void		acceptClient(void);
		void		receiveData(int sd);
		void		processData(int sd);
		void		closeAllSockets(void);
		void		addNewUser(int sd);

		int							_listen_sd;
		int							_timeout;
		int							_port;
		std::string					_pass;
		std::map<int, User>			_users;
		std::vector<struct pollfd>	_fds;
		static bool					_forever;
		std::string					_name;

		std::map<std::string, Channel>	_channels;
};

#endif
