/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:21:11 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/18 12:33:06 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
		std::make_pair("PING", &CommandHandler::handlePING),
		std::make_pair("PONG", &CommandHandler::handlePONG),
	};
	static const std::map<std::string, cmdFunc>	cmdMap(cmdArray, cmdArray + sizeof(cmdArray) / sizeof(cmdArray[0]));
	std::map<std::string, cmdFunc>::const_iterator	it = cmdMap.find(cmd.getName());

	if (it != cmdMap.end())
		(this->*(it->second))(sd, cmd);
	// else
	// 	"unknown command"
}
