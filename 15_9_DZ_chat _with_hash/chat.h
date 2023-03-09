#pragma once

#include "sha1.h"
///#include "test.h"
#include "string.h"

#define LOGINLENGTH 10
typedef char Login[LOGINLENGTH]; 
#define PASSWORDLENGTH 20
typedef char Password[PASSWORDLENGTH];

class Chat {
public:
    Chat();
    ~Chat();

    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);

    ///friend void test(Chat& c);
private:
    enum enPairStatus {
        free,
        engaged,
        deleted
    };

    struct Pair {
        Pair() :
            login(""),
            pass_sha1_hash(nullptr),
            status(enPairStatus::free)
             {}
        ~Pair() {
            if (pass_sha1_hash != nullptr)
                delete[] pass_sha1_hash;
        }
        Pair(char _login[LOGINLENGTH], uint* sh1) {
            strcpy_s(login, _login);
            pass_sha1_hash = sh1;
            status = enPairStatus::engaged;
        }
        Pair& operator = (const Pair& other) {
            strcpy_s(login, other.login);

            if (pass_sha1_hash != nullptr)
                delete[] pass_sha1_hash;
            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
            
            memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);
            status = other.status;
            return *this;
        }
        Login login;
        uint* pass_sha1_hash;  // хеш пароля

        enPairStatus status;
    };
    int hash_func(Login login, int offset);  // для вычисления индекса в массиве

    Pair* data;  //  массив пар( логин, хеш пароля) - основное поле чата
    int mem_size;  // размер массива пар
    int data_count;  // число зарегистрированных пользователей
};    
