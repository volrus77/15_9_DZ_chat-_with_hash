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
    // ����� ����� �� ���� i �� 0 �� ������� �������
    for (; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (data[index].status == enPairStatus::free) {
            // ������� ������ ������, �������� ��
            data[index] = Pair(_login, sha1(_pass, pass_length));
            data_count++;
            break;  //������, ���������������
        }
        else
        std::cout << "login is busy" << std::endl;

    }
    if (i >= mem_size) return; // ��� ���������, ��� �����
}
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // ����� ������� true � ������ ��������� ������
    
    int index = -1, i = 0;
    // ����� ����� �� ���� i �� 0 �� ������� �������
    for (; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (data[index].status == enPairStatus::engaged && std::strcmp(data[index].login, _login) == 0)
        {
            uint* pass_sha1_ha = sha1(_pass, pass_length); //������� ��� ������
            for (int j = 0; j < SHA1HASHLENGTHUINTS; ++j)
            {
                if (data[index].pass_sha1_hash[j] != pass_sha1_ha[j]) // ���� ���� �� �����
                {
                    delete[] pass_sha1_ha;
                    return false;
                }
            }
            delete[] pass_sha1_ha;
            return true;   // ���� ���� �����
        }
        if (data[index].status == enPairStatus::free && std::strcmp(data[index].login, _login))
            return false;  // ����� �� free, ����� �� �����, ������� ���������������
    }
    return false;
}

int Chat::hash_func(Login login, int offset) {
    // ��������� ������
    int sum = 0, i = 0;
    for (; i < strlen(login); i++) {
        sum += login[i];
    }
    // �������� �����
    //return (sum % mem_size + offset) % mem_size;

    // ������������ �����
    return (sum % mem_size + offset * offset) % mem_size;

    // ������ �����������
    //int f2 = sum % (mem_size * 2);
    //// �����
    //return (sum % mem_size + offset * f2) % mem_size;
}
