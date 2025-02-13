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

class CommandHandler
{
	public:
		CommandHandler();
		~CommandHandler();
		CommandHandler(CommandHandler const &);
		CommandHandler &	operator=(CommandHandler const &);
};

#endif
