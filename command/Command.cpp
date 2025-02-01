/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:04:51 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/01 15:37:03 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Command.hpp"

Command::Command() : _name(""), _tail("") {}

Command::Command(const std::string &name) : _name(name), _tail("") {}

Command::Command(const std::string &name, const std::string &tail) : _name(name), _tail(tail) {}

Command::Command(const Command &other) {
	*this = other;
}
	
Command::~Command() {}

Command &Command::operator=(const Command &other) {
	if (this != &other) {
		_name = other._name;
		_tail = other._tail;
		_parameters = other._parameters;
	}
	return *this;
}

const std::string &Command::getName() const {
	return _name;
}

const std::string &Command::getTail() const {
	return _tail;
}

const std::vector<std::string> &Command::getParameters() const {
	return _parameters;
}

void Command::setName(const std::string &name) {
	_name = name;
}

void Command::setTail(const std::string &tail) {
	_tail = tail;
}

void Command::addParam(const std::string &param) {
	_parameters.push_back(param);
}

void Command::printParams() const {
	if (_parameters.empty()) {
		std::cout << "No parameters." << std::endl;
		return;
	}
	std::cout << "Parameters:" << std::endl;
	for (size_t i = 0; i < _parameters.size(); ++i) {
		std::cout << " [" << i << "] " << _parameters[i] << std::endl;
	}
}

std::ostream &operator<<(std::ostream &out, const Command &cmd) {
	out << "Command: " << cmd.getName();
	if (!cmd.getTail().empty())
		out << " | Tail: " << cmd.getTail();

	const std::vector<std::string>& params = cmd.getParameters();
	if (!params.empty()) {
		out << " | Parameters: [";
		for (size_t i = 0; i < params.size(); ++i) {
			out << params[i];
			if (i < params.size() - 1)
				out << ", ";
		}
		out << "]";
	}
	return out;
}
