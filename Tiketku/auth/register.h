#ifndef REGISTER_H
#define REGISTER_H

#include "../user/user.h"


namespace auth
{
    bool isUsernameTaken(string usernameInput);
    bool isEmailTaken(string emailInput);
    bool isNoTelpTaken(string no_telpInput);
    bool registerUser(user::User *userRegister);
}

#endif // !REGISTER_H