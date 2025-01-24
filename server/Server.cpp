/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:05:10 by smoroz            #+#    #+#             */
/*   Updated: 2025/01/24 19:06:42 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// ==========================================
// Constructors
// ==========================================

Server::Server() : _port(PORT), _pass(PASS), _listen_sd(-1)
{
	std::cout << "Server: Default constructor called" << std::endl;
}

Server::Server(Server const & copy)
{
	std::cout << "Server: Copy constructor called" << std::endl;
	*this = copy;
}

Server::Server(int port, std::string & pass) : _port(port), _pass(pass), _listen_sd(-1)
{
	std::cout << "Server: Custom constructor called" << std::endl;
}

// ==========================================
// Destructor
// ==========================================

Server::~Server()
{
	std::cout << "Server: Destructor called" << std::endl;
}

// ==========================================
// Assignment operator=()
// ==========================================

Server &	Server::operator=(Server const & rhs)
{
	if (this != &rhs)
	{
		std::cout << "Server: Assignment operator called" << std::endl;
		_port = rhs.getPort();
		_pass = rhs.getPass();
	}
	return (*this);
}

// ==========================================
// Getter
// ==========================================

int	Server::getPort(void) const
{
	return (_port);
}

std::string	Server::getPass(void) const
{
	return (_pass);
}

// ==========================================
// Methods
// ==========================================

void	Server::init(void)
{
	int				on = 1;
	struct pollfd	pl;
	sockaddr_in6	serverAddr;
	char			str[INET6_ADDRSTRLEN];

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin6_family = AF_INET6;
	serverAddr.sin6_port = htons(_port);
	serverAddr.sin6_addr = in6addr_any;

	std::cout << "INFO: creating a socket..." << std::endl;
	_listen_sd = socket(AF_INET6, SOCK_STREAM, 0);
	if (_listen_sd < 0)
		throw std::runtime_error("ERROR: Socket creating failed!");
	if (setsockopt(_listen_sd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
		throw std::runtime_error("ERROR: setsockopt(SO_REUSEADDR) failed!");
	if (fcntl(_listen_sd, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error("ERROR: fcntl(O_NONBLOCK) failed!");
	if (bind(_listen_sd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
		throw std::runtime_error("ERROR: bind socket to port failed!");
	if (listen(_listen_sd, SOMAXCONN) < 0)
		throw std::runtime_error("ERROR: listen failed!");

	if (inet_ntop(AF_INET6, &serverAddr.sin6_addr, str, sizeof(str)))
		std::cout << "INFO: Server " << str << ":" << _port << std::endl;

	pl.fd = _listen_sd;
	pl.events = POLLIN;
	pl.revents = 0;

	_fds.push_back(pl);
}

void	Server::run()
{
	int	rc;
	while (true)
	{
		std::cout << "INFO: [timestamp] Waiting..." << std::endl;
		rc = poll(&_fds[0], _fds.size(), 5 * 1000);
		if (rc < 0)
			throw(std::runtime_error("ERROR: poll failed"));
		if (rc == 0)
			continue; // timeout
		for (std::vector<struct pollfd>::iterator it=_fds.begin(); it != _fds.end(); ++it)
		{
			if (it->revents == 0)
				continue;
			else if (it->revents != POLLIN)
				throw std::runtime_error("ERROR: Unexpected revents!");
			else
			{
				// if (it->fd == _listen_sd)
				// 	acceptClient();
				// else
				// 	receiveData(it->fd);
			}
		}
	}
}

// ==========================================
// Static
// ==========================================

void	Server::usage(void)
{
	std::cout << "example: ./ircserv <port> <password>" << std::endl;
}
