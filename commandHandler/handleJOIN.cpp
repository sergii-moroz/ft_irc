/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleJOIN.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:10:01 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/25 20:56:30 by smoreron         ###   ########.fr       */
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

	// 1. Проверка, что есть хотя бы один параметр (название канала)
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
		// Канала ещё нет, создаём
		_server->createChannel(channelName);
		channel = _server->getChannelByName(channelName);
		newChannel = true;
	}

	// 2. Проверяем бан-лист
	if (channel->isBanned(nick))
	{
		std::string err = "474 " + nick + " " + channelName + " :You are banned from this channel\r\n";
		_server->sendData(sd, err);
		return;
	}

	// 3. Если пароль установлен (channel->getPassword() != ""), проверяем 2-й параметр JOIN
	//    Пример: JOIN #channel key
	if (!channel->getPassword().empty())
	{
		// Проверим, передал ли пользователь пароль
		std::string key;
		if (cmd.hasParamAtPos(1, 0))
			key = cmd.getParamAtPos(1, 0);

		if (key != channel->getPassword())
		{
			std::string err = "475 " + nick + " " + channelName + " :Cannot join channel (+k)\r\n";
			_server->sendData(sd, err);
			return;
		}
	}

	// 4. Проверяем лимит, если он > 0
	if (channel->getUserLimit() > 0
	    && channel->getUsers().size() >= channel->getUserLimit())
	{
		std::string err = "471 " + nick + " " + channelName + " :Cannot join channel (+l)\r\n";
		_server->sendData(sd, err);
		return;
	}

	// 5. Добавляем пользователя, если он ещё не в канале
	if (!channel->hasUser(sd))
	{
		channel->addUser(sd);

		// Если канал только что создан, делаем вошедшего оператором
		if (newChannel)
			channel->addOperator(sd);

		// Формируем JOIN-сообщение для самого пользователя
		std::string joinMsg = ":" + nick + " JOIN :" + channelName + "\r\n";
		_server->sendData(sd, joinMsg);

		// Можно уведомить других участников канала, что nick присоединился:
		std::string broadcastMsg = ":" + nick + " JOIN " + channelName + "\r\n";
		channel->broadcastRaw(*_server, broadcastMsg);
	}
}
