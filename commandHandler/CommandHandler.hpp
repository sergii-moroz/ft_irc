/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:19:48 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/17 16:05:14 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HANDLER_HPP
# define COMMAND_HANDLER_HPP

# include <iostream>
# include <map>

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

		std::string	errNoNicknameGiven(std::string const &, std::string const &) const;		// 431
		std::string	errNicknameInUse(std::string const &, std::string const &, std::string const &) const;	// 433
		std::string	errNeedMoreParams(std::string const &, std::string const &) const;		// 461
		std::string	errAlreadyRegistered(std::string const &, std::string const &) const;	// 462
		std::string	errPasswdMismatch(std::string const &) const; 							// 464
};

#endif
