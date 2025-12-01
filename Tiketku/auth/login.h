#ifndef LOGIN_H
#define LOGIN_H
#include "../user/user.h"

bool loginUser(User* activeUser);
bool checkSession(User* activeUser);

void logout();

#endif // !LOGIN_H
