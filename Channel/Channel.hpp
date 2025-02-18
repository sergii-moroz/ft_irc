/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:50:06 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/18 22:05:09 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <set>
#include "User.hpp"

class Server; 

class Channel
{
public:
	Channel(const std::string &name);
	~Channel();

	
	const std::string & getName() const;

	
	void addUser(int userFd);
	void removeUser(int userFd);
	bool hasUser(int userFd) const;

	void broadcast(Server &server, const std::string &senderNick, 
				   const std::string &message, int excludeFd);

private:
	std::string   _name;	  
	std::set<int> _userFds;   

};

#endif
