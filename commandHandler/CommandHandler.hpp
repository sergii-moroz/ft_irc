/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:19:48 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/26 02:24:43 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef COMMAND_HANDLER_HPP
# define COMMAND_HANDLER_HPP

# include <iostream>
#include "Channel.hpp"
# include "Server.hpp"

class Server;

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

		void	handlePONG(int, Command const &);
		void	handlePING(int, Command const &);
		void	handlePRIVMSG(int, Command const &);

		void	handleJOIN(int, Command const &);
		void	handleKICK(int, Command const &);

		void	handleMODE(int, Command const &);
		void	handleINVITE(int sd, Command const &cmd);
		void	handleTOPIC(int sd, Command const &cmd);

		std::string	errNoSuchNick(std::string const &, std::string const &, std::string const &) const;		// 401
		std::string	errNoNicknameGiven(std::string const &, std::string const &) const;		// 431
		std::string	errNicknameInUse(std::string const &, std::string const &, std::string const &) const;	// 433
		std::string	errNeedMoreParams(std::string const &, std::string const &) const;		// 461
		std::string	errAlreadyRegistered(std::string const &, std::string const &) const;	// 462
		std::string	errPasswdMismatch(std::string const &) const; 							// 464
};

#endif
