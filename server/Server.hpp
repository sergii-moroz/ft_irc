/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:01:02 by smoroz            #+#    #+#             */
/*   Updated: 2025/01/24 19:25:27 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <iostream>
# include <fcntl.h>
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

		int			getPort(void) const;
		std::string	getPass(void) const;

		void		init(void);
		void		run(void);
		void		acceptClient(void);

	private:
		int							_listen_sd;
		int							_port;
		std::string					_pass;
		std::vector<struct pollfd>	_fds;
};

#endif
