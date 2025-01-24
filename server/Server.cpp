/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:05:10 by smoroz            #+#    #+#             */
/*   Updated: 2025/01/24 20:06:24 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// ==========================================
// Constructors
// ==========================================

Server::Server() : _port(PORT), _pass(PASS), _listen_sd(-1), _timeout(15 * 1000)
{
	std::cout << "Server: Default constructor called" << std::endl;
}

Server::Server(Server const & copy)
{
	std::cout << "Server: Copy constructor called" << std::endl;
	*this = copy;
}

Server::Server(int port, std::string & pass) : _port(port), _pass(pass), _listen_sd(-1), _timeout(15 * 1000)
{
	std::cout << "Server: Custom constructor called" << std::endl;
}

// ==========================================
// Destructor
// ==========================================

Server::~Server()
{
	std::cout << "Server: Destructor called" << std::endl;
	closeAllSockets();
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

	while (Server::_forever)
	{
		try
		{
			rc = poll(_fds.data(), _fds.size(), _timeout);
			if (rc < 0 && Server::_forever)
				throw(std::runtime_error("ERROR: poll failed"));
			if (rc == 0)
				throw(std::runtime_error("INFO: [timestamp] Waiting..."));
			for (int i=0; i < _fds.size(); ++i)
			{
				if (_fds[i].revents == 0)
					continue;
				else if (_fds[i].revents != POLLIN)
					throw std::runtime_error("ERROR: Unexpected revents!");
				else
				{
					if (_fds[i].fd == _listen_sd)
						acceptClient();
					else
						receiveData(_fds[i].fd);
				}
			}
		}
		catch(std::exception const & e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

void	Server::acceptClient(void)
{
	struct pollfd		connection;
	struct sockaddr_in6	conn_addr;
	char				str[INET6_ADDRSTRLEN];
	socklen_t			addrlen = sizeof(conn_addr);

	std::cout << "INFO: Listening socket is readable" << std::endl;
	connection.fd = accept(_listen_sd, (struct sockaddr *)&conn_addr, &addrlen);
	if (connection.fd < 0)
		throw std::runtime_error("ERROR: accept new connection failed!");
	else
	{
		connection.events = POLLIN;
		connection.revents = 0;

		_fds.push_back(connection);
		std::cout << "Client with socket descriptor [" << connection.fd << "] connected" << std::endl;
		if (inet_ntop(AF_INET6, &conn_addr.sin6_addr, str, sizeof(str)))
			std::cout << "INFO: Client: " << str << ":" << ntohs(conn_addr.sin6_port) << std::endl;
	}
}

void	Server::receiveData(int sd)
{
	int		rc;
	char	buffer[1024];

	memset(buffer, 0, sizeof(buffer));
	std::cout << "INFO: Existing descriptor " << sd << " is readable" << std::endl;
	rc = recv(sd, buffer, sizeof(buffer) - 1, 0);
	if (rc < 0)
		throw std::runtime_error("ERROR: recv() faild");
	else if (rc == 0)
	{
		std::cout << "INFO: Connection was closed by client. Socket " << sd << std::endl;
		clearClient(sd);
	}
	else
	{
		std::cout << "INFO: Client [" << sd << "] " << rc << " bytes received" << std::endl;

		// Currently just print message
		std::cout << buffer << std::endl;
		// TODO:
		// ---> Parse and process message here <---
	}
}

void	Server::clearClient(int sd)
{
	for (int i=0; i<_fds.size(); ++i)
	{
		if (_fds[i].fd == sd)
		{
			_fds.erase(_fds.begin() + i);
			break;
		}
	}
	close(sd);
}

void	Server::closeAllSockets(void)
{
	for (int i=0; i<_fds.size(); ++i)
	{
		std::cout << "INFO: Socket id: ["<< _fds[i].fd << "] disconnected" << std::endl;
		close(_fds[i].fd);
	}
}

// ==========================================
// Static vars / functions
// ==========================================

bool Server::_forever = true;

void	Server::signalHandler(int signum)
{
	(void)signum;
	std::cout << "WARNING: SIGINT signal received!" << std::endl;
	Server::_forever = false;
}

void	Server::usage(void)
{
	std::cout << "example: ./ircserv <port> <password>" << std::endl;
}
