// 15_9_DZ_chat _with_hash.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "chat.h"
#include <iostream>

int main()
{
	Chat chat;

	Login login;
	std::cout << "Enter login :";
	std::cin >> login;
	Password password;
	std::cout << "Enter password :";
	std::cin >> password;
	chat.reg(login, password, strlen(password));


	Login login1;
	std::cout << "Enter login :";
	std::cin >> login1;
	Password password1;
	std::cout << "Enter password :";
	std::cin >> password1;
	chat.reg(login1, password1, strlen(password1));


	Login login2;
	std::cout << "Enter login :";
	std::cin >> login2;
	Password password2;
	std::cout << "Enter password :";
	std::cin >> password2;


	if (chat.login(login2, password2, strlen(password2)))
		std::cout << "true";
	else
		std::cout << "false";
	return 0;
}
