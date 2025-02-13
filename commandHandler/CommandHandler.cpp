/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:21:11 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/13 09:21:11 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandHandler.hpp"

// ==========================================
// Constructors
// ==========================================

CommandHandler::CommandHandler() : _server(NULL)
{
	std::cout << "CommandHandler: default constructor called" << std::endl;
}

CommandHandler::CommandHandler(CommandHandler const & copy)
{
	std::cout << "CommandHandler: Copy constructor called" << std::endl;
	*this = copy;
}

CommandHandler::CommandHandler(Server & server) : _server(&server)
{
	std::cout << "CommandHandler: Special constructor called" << std::endl;
}

// ==========================================
// Destructor
// ==========================================

CommandHandler::~CommandHandler()
{
	std::cout << "CommandHandler: destructor called" << std::endl;
}

// ==========================================
// Assignment operator=()
// ==========================================

CommandHandler &	CommandHandler::operator=(CommandHandler const & rhs)
{
	if (this != &rhs)
	{
		std::cout << "CommandHandler: Assignment operator called" << std::endl;
		_server = rhs._server;
	}
	return (*this);
}

// ==========================================
// Getters / Setters
// ==========================================

void	CommandHandler::setServer(Server &server)
{
	_server = &server;
}

// ==========================================
// Handle Commands
// ==========================================

void	CommandHandler::executeCommand(int sd, Command const & cmd)
{
	typedef void (CommandHandler::*cmdFunc)(int, Command const &);
	static const	std::pair<std::string, cmdFunc> cmdArray[] = {
		std::make_pair("CAP", &CommandHandler::handleCAP),
		std::make_pair("PASS", &CommandHandler::handlePASS),
		std::make_pair("NICK", &CommandHandler::handleNICK),
		std::make_pair("USER", &CommandHandler::handleUSER),
	};
	static const std::map<std::string, cmdFunc>	cmdMap(cmdArray, cmdArray + sizeof(cmdArray) / sizeof(cmdArray[0]));
	std::map<std::string, cmdFunc>::const_iterator	it = cmdMap.find(cmd.getName());

	if (it != cmdMap.end())
		(this->*(it->second))(sd, cmd);
	// else
	// 	"unknown command"
}

void	CommandHandler::handleCAP(int sd, Command const & cmd)
{
	std::vector< std::vector<std::string> >	params = cmd.getParameters();
	if (params.empty())
	{
		std::string	msg = ":localhost 461\r\n";
		_server->sendData(sd, msg);
		// close connection ???
	}
	else if (params[0][0] == "LS")
	{
		std::string	msg = ":localhost CAP * LS :\r\n";
		_server->sendData(sd, msg);
	}
}

void	CommandHandler::handlePASS(int sd, Command const & cmd)
{
	std::vector< std::vector<std::string> >	params = cmd.getParameters();
	if (params.empty())
	{
		std::string	msg = ":localhost 461 * :Not enough parameters\r\n";
		_server->sendData(sd, msg);
	}
	else if (params[0][0] != _server->getPass())
	{
		std::string	msg = ":localhost 400 * :password incorect\r\n";
		_server->sendData(sd, msg);
		std::cout << "ERROR: ERR_PASSWDMISMATCH (464)" << std::endl; // <-- Server Side Logging
		_server->clearClient(sd);
	}
}

void	CommandHandler::handleNICK(int sd, Command const & cmd)
{
	std::vector< std::vector<std::string> >	params = cmd.getParameters();
	if (!params.empty())
	{
		_server->getUser(sd).setNickname(params[0][0]);
 		std::cout << "INFO: " << _server->getUser(sd) << std::endl; // <-- Server Side Logging
	}
}

void	CommandHandler::handleUSER(int sd, const Command &cmd)
{
	std::vector< std::vector<std::string> >	params = cmd.getParameters();
	if (!params.empty()) {
		_server->getUser(sd).setUsername(params[0][0]);
		_server->getUser(sd).setRealname(cmd.getTail());
		std::cout << "INFO: " << _server->getUser(sd) << std::endl; // <-- Server Side Logging
		// User is registered --> send Welcome message
		std::string	msg = ":localhost 001 root :Welcome to the IRC Network, <nickname>!<user>@<host>\r\n";
		_server->sendData(sd, msg);
	}
}
