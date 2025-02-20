/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleNumeric.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:56:32 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/17 16:05:28 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandHandler.hpp"

// ==========================================
// ERR_NOSUCHNICK (401)
// ==========================================

std::string	CommandHandler::errNoSuchNick(std::string const & serverName, std::string const & client, std::string const & nick) const
{
	return (":" + serverName + " 401 " + client + " " + nick + " :No such nick/channel\r\n");
}

// ==========================================
// ERR_NONICKNAMEGIVEN (431)
// ==========================================

std::string	CommandHandler::errNoNicknameGiven(std::string const & serverName, std::string const & client) const
{
	return (":" + serverName + " 431 " + client + " :No nickname given\r\n");
}

// ==========================================
// ERR_NICKNAMEINUSE (433)
// ==========================================

std::string	CommandHandler::errNicknameInUse(std::string const & serverName, std::string const & client, std::string const & nick) const
{
	return (":" + serverName + " 433 " + client + " " + nick + " :Nickname is already in use\r\n");
}

// ==========================================
// ERR_NEEDMOREPARAMS (461)
// ==========================================

std::string	CommandHandler::errNeedMoreParams(std::string const & serverName, std::string const & command) const
{
	return (":" + serverName + " 461 " + command + " :Not enough parameters\r\n");
}

// ==========================================
// ERR_ALREADYREGISTERED (462)
// ==========================================

std::string	CommandHandler::errAlreadyRegistered(std::string const & serverName, std::string const & client) const
{
	return (":" + serverName + " 462 " + client +" :You may not reregister\r\n");
}

// ==========================================
// ERR_PASSWDMISMATCH (464)
// ==========================================

std::string	CommandHandler::errPasswdMismatch(std::string const & serverName) const
{
	return (":" + serverName + " 464 * :password incorect\r\n");
}
