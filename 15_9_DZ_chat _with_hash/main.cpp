// 15_9_DZ_chat _with_hash.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "chat.h"
#include <iostream>


void throwHere(const std::string& text) {
	std::cout << "Throw text: " << text.c_str() << std::endl;
	throw 1;
}

int main()
{
	//Chat c;
	//test(chat);
    bool good = false;
    setlocale(LC_CTYPE, "rus");
    try {
        Chat c;

        c.reg((char*)"user1", (char*)"qwerty12345", sizeof("qwerty12345"));
        c.reg((char*)"user2", (char*)"asdfg", sizeof("asdfg"));
        c.reg((char*)"user3", (char*)"zsdrt", sizeof("zsdrt"));
        c.reg((char*)"user4", (char*)"pasgas", sizeof("pasgas"));
        c.reg((char*)"dfd11111", (char*)"pasgas", sizeof("pasgas"));
        c.reg((char*)"sdgss", (char*)"pasgas", sizeof("pasgas"));
        c.reg((char*)"xzxvxcccc", (char*)"pasgas", sizeof("pasgas"));
        c.reg((char*)"123", (char*)"pasgas", sizeof("pasgas"));
        c.reg((char*)"34", (char*)"pasgas", sizeof("pasgas"));
        c.reg((char*)"111", (char*)"pasgas", sizeof("pasgas"));

        c.del((char*)"111", (char*)"pasgas", sizeof("pasgas"));
        c.del((char*)"dfd11111", (char*)"pasgas", sizeof("pasgas"));


        if (!c.login((char*)"user1", (char*)"qwerty12345", sizeof("qwerty12345")))  throwHere("in c.login() user1");
        if (!c.login((char*)"user2", (char*)"asdfg", sizeof("asdfg")))  throwHere("in c.login() user2");
        if (!c.login((char*)"user3", (char*)"zsdrt", sizeof("zsdrt")))  throwHere("in c.login() user3");
        if (!c.login((char*)"user3", (char*)"zsdrt", sizeof("zsdrt")))  throwHere("in c.login() user3");
        if (!c.login((char*)"user4", (char*)"pasgas", sizeof("pasgas")))  throwHere("in c.login() user4");
        if (!c.login((char*)"xzxvxcccc", (char*)"pasgas", sizeof("pasgas")))  throwHere("in c.login() xzxvxcccc");
        if (!c.login((char*)"123", (char*)"pasgas", sizeof("pasgas")))  throwHere("in c.login() 123");
        if (!c.login((char*)"34", (char*)"pasgas", sizeof("pasgas")))  throwHere("in c.login() 34");

        if (c.login((char*)"111", (char*)"pasgas", sizeof("pasgas")))  throwHere("in c.login() 111");
        if (c.login((char*)"dfd11111", (char*)"pasgas", sizeof("pasgas")))  throwHere("in c.login() dfd11111");

        if (c.login((char*)"user2", (char*)"qwerty12345", sizeof("qwerty12345"))) throwHere("in test() user2 bad pass");
        if (c.login((char*)"non-exuser", (char*)"pass", sizeof("pass"))) throwHere("in test() non-ex_user");

        good = true;
    }
    catch (...) {
        good = false;
    }

    if (good) {
        std::cout << "Тесты пройдены" << std::endl;
    }
    else {
        std::cout << "Тесты провалены" << std::endl;
    }

	return 0;
}

