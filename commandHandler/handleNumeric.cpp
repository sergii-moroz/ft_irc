/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleNumeric.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:56:32 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/16 12:56:32 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandHandler.hpp"



// ==========================================
// ERR_NEEDMOREPARAMS (461)
// ==========================================

std::string	CommandHandler::errNeedMoreParams(std::string const & serverName, std::string const & command) const
{
	return (":" + serverName + " 461 " + command + " :Not enough parameters\r\n");
}
