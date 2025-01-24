/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:01:02 by smoroz            #+#    #+#             */
/*   Updated: 2025/01/24 20:04:52 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define PORT	12345
# define PASS	"42Heilbronn"

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

		void		init(void);
		void		run(void);

	private:

		void		acceptClient(void);
		void		receiveData(int sd);
		void		clearClient(int sd);
		void		closeAllSockets(void);

		int							_listen_sd;
		int							_timeout;
		int							_port;
		std::string					_pass;
		std::vector<struct pollfd>	_fds;
		static bool					_forever;
};

#endif
