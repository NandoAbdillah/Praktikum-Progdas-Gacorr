#ifndef USER_H
#define USER_H

#include <string>
#define MAX_USER_CACHE 100
#define DB_USERS "./database/users.csv"

using namespace std;

namespace user
{
    struct User
    {
        string id;
        string username;
        string password;
        string nama_lengkap;
        string email;
        string no_telp;
        string role;
        long long saldo;
    };

    extern User allUsers[MAX_USER_CACHE];
    extern int totalUsers;
    extern User authUser;
    extern bool isLoggedIn;
    extern int  indexAuthUser;

    bool loadUsers();
    bool loadAuthUser();
    bool appendUserToCSV(User newUser);
    bool overwriteAllUsersToCSV();
}


#endif // ! USER_H