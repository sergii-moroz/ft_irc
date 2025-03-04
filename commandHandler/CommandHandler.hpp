/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:19:48 by smoroz            #+#    #+#             */
/*   Updated: 2025/03/04 15:50:29 by smoroz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef COMMAND_HANDLER_HPP
# define COMMAND_HANDLER_HPP

# include <iostream>
# include "Channel.hpp"
# include "Server.hpp"

class Server;
class Channel;
class User;

class CommandHandler
{
	public:
		CommandHandler();
		~CommandHandler();
		CommandHandler(Server &);
		CommandHandler(CommandHandler const &);
		CommandHandler &	operator=(CommandHandler const &);

		void	setServer(Server & server);
		void	executeCommand(int, Command const &);

	private:
		Server	*_server;

		void	handleCAP(int, Command const &);
		void	handlePASS(int, Command const &);
		void	handleNICK(int, Command const &);
		void	handleUSER(int, Command const &);

		void	handleQUIT(int, Command const &);
		void	handlePONG(int, Command const &);
		void	handlePING(int, Command const &);
		void	handlePRIVMSG(int, Command const &);
		void	handleNOTICE(int, Command const &);

		void	handleJOIN(int, Command const &);
		void	handlePART(int, Command const &);
		void	handleKICK(int, Command const &);

		void	handleMODE(int, Command const &);
		void	handleINVITE(int sd, Command const &cmd);
		void	handleTOPIC(int sd, Command const &cmd);

		std::vector<std::string>	splitByComma(std::string const & input, size_t len) const;
		void	joinChannel(std::string const & channelName, std::string const & key, User & user) const;
		void	leaveChannel(std::string const & channelName, std::string const & reason, User & user) const;
		void	kickSingleUser(std::string const & channelName, std::string const & targetNick, std::string const & reason, User & sender) const;
		void	sendSingleMsg(std::string const & target, std::string const & text, User & sender) const;
		void	sendSingleNotification(std::string const & target, std::string const & text, User & sender) const;

		std::string	rplWelcome(std::string const &, std::string const &) const;											// 001
		std::string	rplChannelModeIs(std::string const & serverName, std::string const & client, Channel *channel) const;	// 324
		std::string	rplNoTopic(std::string const &, std::string const &, std::string const &) const;					// 331
		std::string	rplTopic(std::string const &, std::string const &, std::string const &, std::string const &) const;	// 332
		std::string	rplInviting(std::string const &, std::string const &, std::string const &, std::string const &) const;	// 341
		std::string	rplNamReply(std::string const &, std::string const &, std::string const &, std::string const &) const;	// 353
		std::string	rplEndOfNames(std::string const &, std::string const &, std::string const &) const;					// 366
		std::string	errNoSuchNick(std::string const &, std::string const &, std::string const &) const;					// 401
		std::string	errNoSuchChannel(std::string const &, std::string const &, std::string const &) const;				// 403
		std::string	errNoTextToSend(std::string const & serverName, std::string const & client) const;					// 412
		std::string	errNoNicknameGiven(std::string const &, std::string const &) const;									// 431
		std::string	errErroneusNickName(std::string const &, std::string const &, std::string const &) const;			// 432
		std::string	errNicknameInUse(std::string const &, std::string const &, std::string const &) const;				// 433
		std::string	errNotOnChannel(std::string const &, std::string const &, std::string const &) const;				// 442
		std::string	errUserOnChannel(std::string const &, std::string const &, std::string const &, std::string const &) const;	// 443
		std::string	errNotRegistered(std::string const &, std::string const &) const;									// 451
		std::string	errNeedMoreParams(std::string const &, std::string const &) const;									// 461
		std::string	errAlreadyRegistered(std::string const &, std::string const &) const;								// 462
		std::string	errPasswdMismatch(std::string const &) const;														// 464
		std::string	errChannelIsFull(std::string const &, std::string const &, std::string const &) const;				// 471
		std::string	errInviteOnlyChan(std::string const &, std::string const &, std::string const &) const;				// 473
		std::string	errBadChannelKey(std::string const &, std::string const &, std::string const &) const;				// 475
		std::string	errChanOpPrivsNeeded(std::string const &, std::string const &, std::string const &) const;			// 482
		std::string	errUModeUnknownFlag(std::string const & serverName, std::string const & client);					// 501
};

#endif
