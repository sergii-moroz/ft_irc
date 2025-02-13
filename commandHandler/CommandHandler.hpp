/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:19:48 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/13 09:19:48 by smoroz           ###   ########.fr       */
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
};

#endif
