/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:04:51 by smoreron          #+#    #+#             */
/*   Updated: 2025/02/19 00:16:39 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Command.hpp"

Command::Command() : _name(""), _tail("") {}

Command::Command(Command const & other)
{
	*this = other;
}

Command::~Command() {}

Command &	Command::operator=(Command const & other)
{
	if (this != &other)
	{
		_name = other.getName();
		_tail = other.getTail();
		_parameters = other.getParameters();
	}
	return (*this);
}

std::string const &	Command::getName(void) const
{
	return (_name);
}

std::string const &	Command::getTail(void) const
{
	return (_tail);
}

std::vector< std::vector<std::string> > const &	Command::getParameters() const
{
	return (_parameters);
}

void	Command::setName(std::string const & name)
{
	_name = name;
}

void	Command::setTail(std::string const & tail)
{
	_tail = tail;
}

void	Command::addParam(std::vector<std::string> const & param)
{
	_parameters.push_back(param);
}

std::string const &	Command::getParamAtPos(size_t row, size_t col) const
{
	return (_parameters[row][col]);
}

std::ostream &	Command::printParams(std::ostream & out) const
{
	for (size_t i=0; i<_parameters.size(); ++i)
		out << std::string(6, ' ') << i << ": [ "
			<< _parameters[i] << " ]" << std::endl;
	return (out);
}

bool	Command::isParamEmpty(void) const
{
	return (_parameters.empty());
}

bool Command::hasParamAtPos(size_t row, size_t col) const
{
	
	if (row >= _parameters.size())
		return false;

	
	if (col >= _parameters[row].size())
		return false;

	return true;
}


bool Command::hasParamAtPos(std::string const & key, size_t row, size_t col) const
{
	
	if (!hasParamAtPos(row, col))
		return false;

	return (key.compare(_parameters[row][col]) == 0);
}






std::ostream &	operator<<(std::ostream & out, Command const & cmd)
{
	out << "Command:" << std::endl
		<< "{" << std::endl
		<< std::string(3, ' ') << "name: " << cmd.getName() << std::endl
		<< std::string(3, ' ') << "parameters: " << std::endl
		<< std::string(3, ' ') << "{" << std::endl;
	cmd.printParams(out);
	out << std::string(3, ' ') << "}" << std::endl
		<< std::string(3, ' ') << "tail: " << cmd.getTail() << std::endl
		<< "}" << std::endl;
	return (out);
}

std::ostream &	operator<<(std::ostream & out, std::vector<std::string> const & v)
{
	for (size_t	i=0; i<v.size(); ++i)
	{
		out << v[i];
		if (i < v.size()-1)
			out << ", ";
	}
	return (out);
}
