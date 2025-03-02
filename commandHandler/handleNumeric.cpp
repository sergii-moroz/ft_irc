/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleNumeric.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:56:32 by smoroz            #+#    #+#             */
/*   Updated: 2025/03/02 20:02:05 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"

// ==========================================
// RPL_WELCOME (001)
// ==========================================

std::string	CommandHandler::rplWelcome(std::string const & serverName, std::string const & nickname) const
{
	return (":" + serverName + " 001 " + nickname + " :Welcome to the IRC Network, " + nickname + "!\r\n");
}

// ==========================================
// RPL_CHANNELMODEIS (324)
// ==========================================

std::string	CommandHandler::rplChannelModeIs(std::string const & serverName, std::string const & client, Channel *channel) const
{
	return (":" + serverName + " 324 " + client + " " + channel->getName() + " " + channel->getModeList() + " " + channel->getModeArgs() + "\r\n");
}

// ==========================================
// RPL_NOTOPIC (331)
// ==========================================

std::string	CommandHandler::rplNoTopic(
	std::string const & serverName,
	std::string const & client,
	std::string const & channelName) const
{
	return (":" + serverName + " 331 " + client + " " + channelName + " :No topic is set\r\n");
}

// ==========================================
// RPL_TOPIC (332)
// ==========================================

std::string	CommandHandler::rplTopic(
	std::string const & serverName,
	std::string const & client,
	std::string const & channelName,
	std::string const & topic) const
{
	return (":" + serverName + " 332 " + client + " " + channelName + " :" + topic + "\r\n");
}

// ==========================================
// RPL_INVITING (341)
// ==========================================

std::string	CommandHandler::rplInviting(std::string const & serverName, std::string const & client, std::string const & nick, std::string const & channel) const
{
	return (":" + serverName + " 341 " + client + " " + nick + " " + channel + "\r\n");
}

// ==========================================
// RPL_NAMREPLY (353)
// ==========================================

std::string	CommandHandler::rplNamReply(
	std::string const & serverName,
	std::string const & client,
	std::string const & channelName,
	std::string const & members) const
{
	return (":" + serverName + " 353 " + client + " = " + channelName + " :" + members + "\r\n");
}

// ==========================================
// RPL_ENDOFNAMES (366)
// ==========================================

std::string	CommandHandler::rplEndOfNames(std::string const & serverName, std::string const & client, std::string const & channel) const
{
	return (":" + serverName + " 366 " + client + " " + channel + " :End of /NAMES list\r\n");
}

// ==========================================
// ERR_NOSUCHNICK (401)
// ==========================================

std::string	CommandHandler::errNoSuchNick(std::string const & serverName, std::string const & client, std::string const & nick) const
{
	return (":" + serverName + " 401 " + client + " " + nick + " :No such nick/channel\r\n");
}

// ==========================================
// ERR_NOSUCHCHANNEL (403)
// ==========================================

std::string	CommandHandler::errNoSuchChannel(std::string const & serverName, std::string const & client, std::string const & channel) const
{
	return (":" + serverName + " 403 " + client + " " + channel + " :No such channel\r\n");
}

// ==========================================
// ERR_NONICKNAMEGIVEN (431)
// ==========================================

std::string	CommandHandler::errNoNicknameGiven(std::string const & serverName, std::string const & client) const
{
	return (":" + serverName + " 431 " + client + " :No nickname given\r\n");
}

// ==========================================
// ERR_ERRONEUSNICKNAME (432)
// ==========================================

std::string	CommandHandler::errErroneusNickName(std::string const & serverName, std::string const & client, std::string const & nick) const
{
	return (":" + serverName + " 432 " + client + " " + nick + " :Erroneus nickname\r\n");
}

// ==========================================
// ERR_NICKNAMEINUSE (433)
// ==========================================

std::string	CommandHandler::errNicknameInUse(std::string const & serverName, std::string const & client, std::string const & nick) const
{
	return (":" + serverName + " 433 " + client + " " + nick + " :Nickname is already in use\r\n");
}

// ==========================================
// ERR_NOTONCHANNEL (442)
// ==========================================

std::string	CommandHandler::errNotOnChannel(std::string const & serverName, std::string const & client, std::string const & channel) const
{
	return (":" + serverName + " 442 " + client + " " + channel + " :You're not on that channel\r\n");
}

// ==========================================
// ERR_USERONCHANNEL (443)
// ==========================================

std::string	CommandHandler::errUserOnChannel(std::string const & serverName, std::string const & client, std::string const & nick, std::string const & channel) const
{
	return (":" + serverName + " 443 " + client + " " + nick + " " + channel + " :is already on channel\r\n");
}

// ==========================================
// ERR_NOTREGISTERED (451)
// ==========================================

std::string	CommandHandler::errNotRegistered(std::string const & serverName, std::string const & client) const
{
	return (":" + serverName + " 451 " + client + " :You have not registered\r\n");
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

// ==========================================
// ERR_CHANNELISFULL (471)
// ==========================================

std::string	CommandHandler::errChannelIsFull(std::string const & serverName, std::string const & client, std::string const & channel) const
{
	return (":" + serverName + " 471 " + client + " " + channel + " :Cannot join channel (+l)\r\n");
}

// ==========================================
// ERR_INVITEONLYCHAN (473)
// ==========================================

std::string	CommandHandler::errInviteOnlyChan(std::string const & serverName, std::string const & client, std::string const & channel) const
{
	return (":" + serverName + " 473 " + client + " " + channel + " :Cannot join channel (+i)\r\n");
}

// ==========================================
// ERR_BADCHANNELKEY (475)
// ==========================================

std::string	CommandHandler::errBadChannelKey(std::string const & serverName, std::string const & client, std::string const & channel) const
{
	return (":" + serverName + " 475 " + client + " " + channel + " :Cannot join channel (+k)\r\n");
}

// ==========================================
// ERR_CHANOPRIVSNEEDED (482)
// ==========================================

std::string	CommandHandler::errChanOpPrivsNeeded(std::string const & serverName, std::string const & client, std::string const & channel) const
{
	return (":" + serverName + " 482 " + client + " " + channel + " :You're not channel operator\r\n");
}

// ==========================================
// ERR_UMODEUNKNOWNFLAG (501)
// ==========================================

std::string	CommandHandler::errUModeUnknownFlag(std::string const & serverName, std::string const & client)
{
	return (":" + serverName + " " + client +" :Unknown MODE flag\r\n");
}
