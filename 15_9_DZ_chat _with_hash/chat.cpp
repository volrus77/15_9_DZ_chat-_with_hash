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

void Chat::reg(Login _login, char _pass[], int pass_length) {
    if (data_count / mem_size > 0.9)
       resize();

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
bool Chat::login(Login _login, char _pass[], int pass_length) {
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

int Chat::hash_func(Login _login, int offset) {
    // вычисляем индекс
    int sum = 0, i = 0;
    for (; i < strlen(_login); i++) {
        sum += _login[i];
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

void Chat::resize() {
    
    Pair* save = data; // запоминаем старый массив
    int oldSize = mem_size;

    mem_size *= 2;  // увеличиваем размер в два раза  
    data_count = 0; // обнуляем количество элементов
    data = new Pair[mem_size]; // создаём новый массив 

    int index = -1;
    for (int i = 0; i < oldSize; i++)
    {
        if (save[i].status == enPairStatus::engaged) {
            index = hash_func(save[i].login, i);
            data[index] = Pair(save[i].login, save[i].pass_sha1_hash);
            data_count++;
        }
    }
    delete[] save;
}

bool Chat::del(Login _login, char _pass[], int pass_length) {

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
            data[index].status = enPairStatus::deleted;
            data_count--;
            return true;   // если хеши равны
        }
        if (data[index].status == enPairStatus::free && std::strcmp(data[index].login, _login))
            return false;  // дошли до free, далее не будет, поэтому останавливаемся
    }
    return false;
}

   

// возвращаем указатель на хеш пароля
//uint* Chat::find(Login _login) {
//
//    /*for (int i = 0; i < mem_size; i++) {
//        int index = hash_func(fr_name, i);
//        if (array[index].status == enPairStatus::engaged &&
//            !strcmp(array[index].fruit_name, fr_name)) {
//            return array[index].fruit_count;
//        }
//        else if (array[index].status == enPairStatus::free) {
//            return -1;
//        }
//    }
//    return -1;*/
//}

void test(Chat& chat)
{

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


    //Login login2;
    //std::cout << "Enter login :";
    //std::cin >> login2;
    //Password password2;
    //std::cout << "Enter password :";
    //std::cin >> password2;


    //if (chat.login(login2, password2, strlen(password2)))
    //	std::cout << "true" << std::endl;
    //else
    //	std::cout << "false" << std::endl;

    Login login3;
    std::cout << "Enter login :";
    std::cin >> login3;
    Password password3;
    std::cout << "Enter password :";
    std::cin >> password3;


    if (chat.del(login3, password3, strlen(password3)))
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;


    Login login4;
    std::cout << "Enter login :";
    std::cin >> login4;
    Password password4;
    std::cout << "Enter password :";
    std::cin >> password4;


    if (chat.login(login4, password4, strlen(password4)))
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;

}