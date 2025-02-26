/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleJOIN.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:10:01 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/25 22:38:55 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include <iostream>


void CommandHandler::handleJOIN(int sd, Command const & cmd)
{
	User &user = _server->getUser(sd);
	std::string nick = user.getNickname();

	// Проверка, что есть хотя бы один параметр (название канала)
	if (cmd.isParamEmpty() || !cmd.hasParamAtPos(0, 0))
	{
		std::string errorMsg = "461 " + nick + " JOIN :Not enough parameters\r\n";
		_server->sendData(sd, errorMsg);
		return;
	}

	std::string channelName = cmd.getParamAtPos(0, 0);
	Channel *channel = _server->getChannelByName(channelName);

	bool newChannel = false;
	if (!channel)
	{
		// Канала нет, создаём
		_server->createChannel(channelName);
		channel = _server->getChannelByName(channelName);
		newChannel = true;
	}

	// Проверяем ban-лист
	if (channel->isBanned(nick))
	{
		std::string err = "474 " + nick + " " + channelName
						  + " :You are banned from this channel\r\n";
		_server->sendData(sd, err);
		return;
	}

	// Invite-only режим (+i): проверяем, приглашён ли пользователь
	if (channel->hasMode(MODE_INVITE_ONLY) && !channel->isInvited(nick))
	{
		// 473 — ERR_INVITEONLYCHAN
		std::string err = "473 " + nick + " " + channelName
						  + " :Cannot join channel (+i)\r\n";
		_server->sendData(sd, err);
		return;
	}

	// Если установлен пароль (+k), проверяем его
	if (!channel->getPassword().empty())
	{
		std::string key;
		if (cmd.hasParamAtPos(1, 0))
			key = cmd.getParamAtPos(1, 0);

		if (key != channel->getPassword())
		{
			std::string err = "475 " + nick + " " + channelName
							  + " :Cannot join channel (+k)\r\n";
			_server->sendData(sd, err);
			return;
		}
	}

	// Лимит (+l)
	if (channel->getUserLimit() > 0
		&& channel->getUsers().size() >= channel->getUserLimit())
	{
		std::string err = "471 " + nick + " " + channelName
						  + " :Cannot join channel (+l)\r\n";
		_server->sendData(sd, err);
		return;
	}

	// Непосредственно присоединяем
	if (!channel->hasUser(sd))
	{
		channel->addUser(sd);

		// Если канал только что создан — делаем пользователя оператором
		if (newChannel)
			channel->addOperator(sd);

		// Если пользователь был в списке приглашённых, удаляем его оттуда
		if (channel->isInvited(nick))
			channel->removeInvited(nick);

		// Сообщаем самому пользователю о JOIN
		std::string joinMsg = ":" + nick + " JOIN :" + channelName + "\r\n";
		_server->sendData(sd, joinMsg);

		// Уведомляем остальных участников канала
		std::string broadcastMsg = ":" + nick + " JOIN " + channelName + "\r\n";
		channel->broadcastRaw(*_server, broadcastMsg);
	}
}
