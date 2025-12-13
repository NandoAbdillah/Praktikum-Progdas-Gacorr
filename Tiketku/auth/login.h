#ifndef LOGIN_H
#define LOGIN_H
#define FILE_SESSION "./database/session.txt"
#include "../user/user.h"
#include <string>


using namespace user;


namespace auth
{
    bool loginUser(User *userLogin);
    bool checkSession(User *userLogin);
    void saveSession(string username);


    void logout();
}

#endif // !LOGIN_H
