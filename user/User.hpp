/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:04:09 by smoreron          #+#    #+#             */
/*   Updated: 2025/01/27 20:56:33 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
	private:
		int			_fd;
		bool		_registered;
		bool		_passOK;
		std::string	_nickname;
		std::string	_username;
		std::string	_realname;

	public:
		// Каноническая форма класса
		User();						// Конструктор по умолчанию
		User(const User &other);	// Конструктор копирования
		User(int fd);				// Конструктор с параметром
		~User();					// Деструктор
		User &operator=(const User &other);	// Оператор присваивания

		// Геттеры
		int		getFd() const;
		bool	isRegistered() const;
		bool	isPassOK() const;
		const std::string &getNickname() const;
		const std::string &getUsername() const;
		const std::string &getRealname() const;

		// Сеттеры
		void	setRegistered(bool val);
		void	setPassOK(bool val);
		void	setNickname(const std::string &nick);
		void	setUsername(const std::string &user);
		void	setRealname(const std::string &real);
};

#endif // USER_HPP
