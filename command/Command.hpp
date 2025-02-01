/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:04:54 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/01 15:36:45 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


#ifndef COMMAND_HPP 
#define COMMAND_HPP

#include <iostream>
#include <string>
#include <vector>  

class Command {
private:
	std::string _name;
	std::string _tail;
	std::vector<std::string> _parameters; 

public:
	Command();
	Command(const std::string &name);
	Command(const std::string &name, const std::string &tail);
	Command(const Command &other);
	~Command();
	Command &operator=(const Command &other);

	const std::string &getName() const;
	const std::string &getTail() const;
	const std::vector<std::string> &getParameters() const; 

	void setName(const std::string &name);
	void setTail(const std::string &tail);

	void addParam(const std::string &param); 
void printParams() const;	   
};

std::ostream &operator<<(std::ostream &out, const Command &cmd);

#endif
