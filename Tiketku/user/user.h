#ifndef  USER_H
#define USER_H

#include <string>
using namespace std;

struct User {
    string id;
    string username;
    string password;
    string nama_lengkap;
    string email;
    string no_telp;
    string role;
    long long saldo;
};

#endif // ! USER_H