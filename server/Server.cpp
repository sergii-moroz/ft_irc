/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:05:10 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/18 22:02:39 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Server.hpp"

// ==========================================
// Constructors
// ==========================================

Server::Server() : _listen_sd(-1), _timeout(15 * 1000), _port(PORT), _pass(PASS), _name(NAME)
{
	std::cout << "Server: Default constructor called" << std::endl;
}

Server::Server(Server const & copy)
{
	std::cout << "Server: Copy constructor called" << std::endl;
	*this = copy;
}

Server::Server(int port, std::string & pass) : _listen_sd(-1), _timeout(15 * 1000), _port(port), _pass(pass), _name(NAME)
{
	std::cout << "Server: Custom constructor called" << std::endl;
	createChannel("general");
	createChannel("smalltalk");
}

// ==========================================
// Destructor
// ==========================================

Server::~Server()
{
	std::cout << "Server: Destructor called" << std::endl;
	closeAllSockets();

	// for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	// {
	// 	delete it->second;
	// }
	// _channels.clear();
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
		_name = rhs.getName();
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

std::string	Server::getName(void) const
{
	return (_name);
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
			// Waiting for events
			rc = poll(_fds.data(), _fds.size(), _timeout);
			if (rc < 0 && Server::_forever)
				throw(std::runtime_error("ERROR: poll failed"));
			if (rc == 0)
				throw(std::runtime_error("INFO: [timestamp] Waiting..."));

			// Process events
			for (size_t i=0; i<_fds.size(); ++i)
			{
				if (_fds[i].revents == 0)
					continue;
				if (_fds[i].revents & POLLIN)
					handlePollIn(i);
				else if (_fds[i].revents & POLLHUP)
					handlePollHup(i);
				else if (_fds[i].revents & POLLERR)
					handlePollErr(i);
				else
					throw std::runtime_error("ERROR: Unexpected revents!");
			}
		}
		catch(std::exception const & e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

// ==========================================
// Event handlers
// ==========================================

void	Server::handlePollIn(size_t i)
{
	std::cout << "DEBUG: POLLIN event on socket " << _fds[i].fd  << std::endl;
	if (_fds[i].fd == _listen_sd)
		acceptClient();				// A new client is connecting
	else
	{
		receiveData(_fds[i].fd);	// An existing client has sent data
		processData(_fds[i].fd);	// Check if we have enough data to parse a command and execute
	}
}

void	Server::handlePollHup(size_t & i)
{
	std::cout << "DEBUG: POLLHUP event on socket " << _fds[i].fd << std::endl;
	std::cerr << "INFO: Client disconnected. Socket " << _fds[i].fd << std::endl;
	close(_fds[i].fd); 				// Close the socket
	_fds.erase(_fds.begin() + i);	// Remove from poll list
	--i;							// Adjust index after erasing
}

void	Server::handlePollErr(size_t & i)
{
	std::cout << "DEBUG: POLLERR event on socket " << _fds[i].fd << std::endl;
	std::cerr << "ERROR: Socket error on descriptor " << _fds[i].fd << std::endl;
	close(_fds[i].fd); 				// Close the socket
	_fds.erase(_fds.begin() + i);	// Remove from poll list
	--i;							// Adjust index after erasing
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
		addNewUser(connection.fd);

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
		_users[sd].addToBuffer(buffer);

		// DEBUG print message
		for (int i=0; i<rc; i++)
		{
			if (buffer[i] == '\r')
				std::cout << "\\r";
			else if(buffer[i] == '\n')
				std::cout << "\\n";
			else
				std::cout << buffer[i];
		}
		std::cout << std::endl;
	}
}

void	Server::processData(int sd)
{
	std::string		data = _users[sd].getNextCommand();
	CommandHandler	cmdHandler(*this);

	while (!data.empty())
	{
		Lexer	lex(data);
		Command	cmd = lex.message();

		std::cout << cmd << std::endl; // <-- DEBUG

		cmdHandler.executeCommand(sd, cmd);
		data = _users[sd].getNextCommand();
	}
}

void	Server::sendData(int sd, std::string & data)
{
	if (send(sd, data.c_str(), data.size(), 0) < 0)
	{
		std::cout << "ERROR: Send failed" << std::endl;
	}
}

void	Server::clearClient(int sd) // Rename to removeFromPool()
{
	for (size_t i=0; i<_fds.size(); ++i)
	{
		if (_fds[i].fd == sd)
		{
			_fds.erase(_fds.begin() + i);
			break;
		}
	}

	std::map<int, User>::iterator	it = _users.find(sd);
	if (it != _users.end())
		_users.erase(it);

	close(sd);
}

void	Server::closeAllSockets(void)
{
	for (size_t i=0; i<_fds.size(); ++i)
	{
		std::cout << "INFO: Socket id: ["<< _fds[i].fd << "] disconnected" << std::endl;
		close(_fds[i].fd);
	}
}

void	Server::addNewUser(int sd)
{
	_users[sd] = User(sd);
}

User &	Server::getUser(int sd)
{
	return (_users[sd]);
}

User	*Server::getUserByNickname(std::string const & nickname)
{
	for (std::map<int, User>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if (nickname.compare(it->second.getNickname()) == 0)
			return (&(it->second));
	}
	return (NULL);
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


// ==========================================
// chanel
// ==========================================

Channel	*Server::getChannelByName(std::string const &channelName)
{
	std::map<std::string, Channel>::iterator it = _channels.find(channelName);
	if (it != _channels.end())
		return (&(it->second));
	return (NULL);
}

void	Server::createChannel(std::string const & channelName)
{
	_channels[channelName] = Channel(channelName);
}

// Channel * Server::findOrCreateChannel(std::string const &channelName)
// {
// 	Channel *chan = getChannelByName(channelName);
// 	if (!chan)
// 	{
// 		_channels[channelName] = Channel(ChannelName);
// 		// chan = new Channel(channelName);
// 		addChannel(chan);
// 		std::cout << "INFO: Created new channel: " << channelName << std::endl;
// 	}
// 	return chan;
// }
