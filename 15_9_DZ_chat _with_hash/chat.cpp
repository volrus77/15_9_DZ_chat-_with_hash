#include "chat.h"
#include "iostream"
#include "string.h"


Chat::Chat() {
    data_count = 0;
    mem_size = 8;
    data = new Pair[mem_size];
}

Chat::~Chat()
{
    delete[] data;
}

void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    if (data_count / mem_size > 0.9)
        ; //resize();

    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (data[index].status == enPairStatus::free) {
            // найдена пустая ячейка, занимаем ее
            data[index] = Pair(_login, sha1(_pass, pass_length));
            data_count++;
            break;  //заняли, останавливаемся
        }
        else
        std::cout << "login is busy" << std::endl;

    }
    if (i >= mem_size) return; // все перебрали, нет места
}
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // Нужно вернуть true в случае успешного логина
    
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (data[index].status == enPairStatus::engaged && std::strcmp(data[index].login, _login) == 0)
        {
            uint* pass_sha1_ha = sha1(_pass, pass_length); //находим хеш пароля
            for (int j = 0; j < SHA1HASHLENGTHUINTS; ++j)
            {
                if (data[index].pass_sha1_hash[j] != pass_sha1_ha[j]) // если хеши не равны
                {
                    delete[] pass_sha1_ha;
                    return false;
                }
            }
            delete[] pass_sha1_ha;
            return true;   // если хеши равны
        }
        if (data[index].status == enPairStatus::free && std::strcmp(data[index].login, _login))
            return false;  // дошли до free, далее не будет, поэтому останавливаемся
    }
    return false;
}

int Chat::hash_func(Login login, int offset) {
    // вычисляем индекс
    int sum = 0, i = 0;
    for (; i < strlen(login); i++) {
        sum += login[i];
    }
    // линейные пробы
    //return (sum % mem_size + offset) % mem_size;

    // квадратичные пробы
    return (sum % mem_size + offset * offset) % mem_size;

    // второе хеширование
    //int f2 = sum % (mem_size * 2);
    //// проба
    //return (sum % mem_size + offset * f2) % mem_size;
}
