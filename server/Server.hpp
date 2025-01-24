/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:01:02 by smoroz            #+#    #+#             */
/*   Updated: 2025/01/21 09:24:27 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>

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

		int			getPort(void) const;
		std::string	getPass(void) const;

	private:
		int			_port;
		std::string	_pass;
};

#endif
