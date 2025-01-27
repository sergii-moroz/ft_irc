/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:11:32 by smoreron          #+#    #+#             */
/*   Updated: 2025/01/27 20:56:48 by smoreron         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


#include "User.hpp"
 
// User::User(int fd)
// : _fd(fd), _registered(false), _passOK(false)
// {}

User::User() : _fd(-1), _registered(false), _passOK(false) {} 
User::User(int fd) : _fd(fd), _registered(false), _passOK(false) {}


User::~User() {}

int User::getFd() const {
	return _fd;
}

bool User::isRegistered() const {
	return _registered;
}

void User::setRegistered(bool val) {
	_registered = val;
}

bool User::isPassOK() const {
	return _passOK;
}

void User::setPassOK(bool val) {
	_passOK = val;
}

const std::string & User::getNickname() const {
	return _nickname;
}

void User::setNickname(const std::string &nick) {
	_nickname = nick;
}

const std::string & User::getUsername() const {
	return _username;
}

void User::setUsername(const std::string &user) {
	_username = user;
}

const std::string & User::getRealname() const {
	return _realname;
}

void User::setRealname(const std::string &real) {
	_realname = real;
}
#include "User.hpp"

// Конструктор по умолчанию
User::User() : _fd(-1), _registered(false), _passOK(false) {}

// Конструктор с параметром
User::User(int fd) : _fd(fd), _registered(false), _passOK(false) {}

// Конструктор копирования
User::User(const User &other) {
	*this = other;
}

// Деструктор
User::~User() {}

// Оператор присваивания
User &User::operator=(const User &other) {
	if (this != &other) {
		_fd = other._fd;
		_registered = other._registered;
		_passOK = other._passOK;
		_nickname = other._nickname;
		_username = other._username;
		_realname = other._realname;
	}
	return *this;
}

// Геттеры
int User::getFd() const {
	return _fd;
}

bool User::isRegistered() const {
	return _registered;
}

bool User::isPassOK() const {
	return _passOK;
}

const std::string &User::getNickname() const {
	return _nickname;
}

const std::string &User::getUsername() const {
	return _username;
}

const std::string &User::getRealname() const {
	return _realname;
}

// Сеттеры
void User::setRegistered(bool val) {
	_registered = val;
}

void User::setPassOK(bool val) {
	_passOK = val;
}

void User::setNickname(const std::string &nick) {
	_nickname = nick;
}

void User::setUsername(const std::string &user) {
	_username = user;
}

void User::setRealname(const std::string &real) {
	_realname = real;
}
