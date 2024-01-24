#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"


class Chat
{
	bool work = false;
	std::vector<User> usersArr;
	std::vector<Message> messagesArr;
	std::shared_ptr<User> actualUserArr = nullptr;

	void login();                                                          //вход зарегистр пользователя 
	void signUp();                                                         //регистрация в чате 
	void showChat() const;                                                 //просмотр чата
	void showAllUsersName() const;                                         //просмотр текущего и всех пользователей
	void addMessage();                                                     //отправка сообщений 
	std::vector<User>& getAllUsers()                                       //для всех пользователей
	{
		return usersArr;
	}
	std::vector<Message>& getAllMessages()                                 //для сообщений
	{
		return messagesArr;
	}
	std::shared_ptr<User> getUserLogin(const std::string& login) const;    //если совпадает по логину      
	std::shared_ptr<User> getUserName(const std::string& name) const;      //если совпадает по имени

public:
	void begin();                                                          //запуск чата
	bool ChatWork() const                                                  //для работы чата (work true)
	{
		return work;
	}
	std::shared_ptr<User> getActualUser() const                            //для конкретного пользователя 
	{
		return actualUserArr;
	}
	void RegistrationShow();                                               //меню регистрации в чате 
	void MessagShow();                                                     //меню сообщений и пользователей
};


