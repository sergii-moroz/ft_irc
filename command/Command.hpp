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
# define COMMAND_HPP

# include <iostream>
# include <string>
# include <vector>

class Command {
	public:
		Command();
		~Command();
		Command(Command const &);
		Command &				operator=(Command const &);

		std::string const &		getName() const;
		std::string const &		getTail() const;
		void					setName(std::string const &);
		void					setTail(std::string const &);
		void					addParam(std::vector<std::string> const &);
		std::ostream &			printParams(std::ostream &) const;
		std::vector< std::vector<std::string> > const &	getParameters() const;
		bool					hasParamAtPos(size_t, size_t) const;
		bool					hasParamAtPos(std::string const &, size_t, size_t) const;
		bool					isParamEmpty(void) const;
		std::string const &		getParamAtPos(size_t, size_t) const;

	private:
		std::string								_name;
		std::string								_tail;
		std::vector< std::vector<std::string> >	_parameters;
};

std::ostream &	operator<<(std::ostream & out, Command const & cmd);
std::ostream &	operator<<(std::ostream & out, std::vector<std::string> const & v);

#endif
