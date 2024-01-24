#include "Chat.h"
#include <iostream>

void Chat::begin()
{
	work = true;
}

std::shared_ptr<User> Chat::getUserLogin(const std::string& login) const
{
	for (auto& user : usersArr)
	{
		if (login == user.getLogin())
			return std::make_shared<User>(user);
	}
	return nullptr;
}

std::shared_ptr<User> Chat::getUserName(const std::string& name) const
{
	for (auto& user : usersArr)
	{
		if (name == user.getName())
			return std::make_shared<User>(user);
	}
	return nullptr;
}

void Chat::login()
{
	std::string login, password;
	char operation;

	do
	{
		std::cout << "Логин: ";
		std::cin >> login;
		std::cout << "Пароль: ";
		std::cin >> password;

		actualUserArr = getUserLogin(login);

		if (actualUserArr == nullptr || (password != actualUserArr->getPassword()))
		{
			actualUserArr = nullptr;

			std::cout << "Неверный логин" << std::endl;
			std::cout << "Для выхода: нажмите  |0|"             << std::endl
				     <<  "Для повтора: нажмите |любую клавишу|" << std::endl;
			std::cin >> operation;

			if (operation == '0')
				break;
		}

	} while (!actualUserArr);
}

void Chat::signUp()
{
	std::string login, password, name;

	std::cout << "Логин: ";
	std::cin >> login;
	std::cout << "Пароль: ";
	std::cin >> password;
	std::cout << "Имя: ";
	std::cin >> name;

	User user = User(login, password, name);
	usersArr.push_back(user);
	actualUserArr = std::make_shared<User>(user);
}

void Chat::showChat() const
{
	std::string from;
	std::string to;

	std::cout << "___________________________________" << std::endl;
	std::cout << "                 Чат               " << std::endl
		      << "___________________________________" << std::endl;

	for (auto& message : messagesArr)
	{

		if (actualUserArr->getLogin() == message.getFrom() || actualUserArr->getLogin() == message.getTo() || message.getTo() == "all")
		{
			from = (actualUserArr->getLogin() == message.getFrom()) ? "(текущего пользователя)" : getUserLogin(message.getFrom())->getName();      

			if (message.getTo() == "all")
			{
				to = "(all)";
			}
			else
			{
				to = (actualUserArr->getLogin() == message.getTo()) ? "(текущего пользователя)" : getUserLogin(message.getTo())->getName();
			}

			std::cout << "Сообщение от " << from << " :" << std::endl;
			std::cout << "текст сообщения: " << message.getText() << std::endl;

			std::cout << "___________________________________" << std::endl;
			std::cout << std::endl;
		}
	}

}

void Chat::RegistrationShow()
{
	actualUserArr = nullptr;

	char operation;

	do
	{
		std::cout << "Для ввода логина: нажмите-       |1|" << std::endl;
		std::cout << "Для регистрации в чате: нажмите- |2|" << std::endl;
		std::cout << "Для выхода из чата: нажмите-     |0|" << std::endl;
		std::cout << "Введите значение: ";
		std::cin >> operation;
		std::cout << "___________________________________" << std::endl;
		switch (operation)
		{
		case '1':
			login();
			break;
		case '2':
			{
				signUp();
			}
			break;
		case '0':
			work = false;
			break;

		default:
			std::cout << "Повторите попытку" << std::endl;
			break;
		}

	} while (!actualUserArr && work);
}

void Chat::MessagShow()
{
	char operation;
	std::cout << "___________________________________" << std::endl;
	std::cout << "Добро пожаловать в чат  " << actualUserArr->getName() << std::endl;            


	while (actualUserArr)
	{
   std::cout<< "Просмотр чата:           нажмите |1| " << std::endl
			<< "Добавить сообщение:      нажмите |2| " << std::endl
			<< "Пользователи:            нажмите |3| " << std::endl
			<< "Для выхода:              нажмите |0| " << std::endl;

		std::cout << std::endl << "_ ";
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsersName();
			break;
		case'0':
			actualUserArr = nullptr;
			break;
		default:
			std::cout << "Повторите попытку" << std::endl;
			break;
		}
	}
}

void Chat::showAllUsersName() const
{
	std::cout << "___________________________________" << std::endl;
	std::cout << "Пользователи:" << std::endl;
	for (auto& user : usersArr)
	{
		std::cout << user.getName();

		if (actualUserArr->getLogin() == user.getLogin())
			std::cout << "(текущий пользователь)";

		std::cout << std::endl;
	}	
}

void Chat::addMessage()                                             
{
	std::string to, text;
	std::cout << "___________________________________"                << std::endl;
	std::cout << "Отправить сообщение"                                << std::endl
		      << "Конкретному пользователю:        |введите его имя|" << std::endl
		      << "Всем пользователям:              |введите- all|   " << std::endl;
	std::cin >> to;
	std::cout << "текст сообщения: ";
	std::cin.ignore();
	getline(std::cin, text);

	if (!(to == "all" || getUserName(to)))
	{
		std::cout << "Ошибка. Нет такого имени " << to << std::endl;
		std::cout << std::endl;
	}	
	else if (to == "all")
	{
		messagesArr.push_back(Message{ actualUserArr->getLogin(), "all",text });
	}
	else
	{
		messagesArr.push_back(Message{ actualUserArr->getLogin(),getUserName(to)->getLogin(),text });
	}
}

