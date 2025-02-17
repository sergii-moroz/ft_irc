/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:21:11 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/16 19:50:48 by smoroz           ###   ########.fr       */
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
