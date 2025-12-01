#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <string>
#include "../user/user.h"

const int MAX_USER_CACHE = 100;

int loadUsersToArray(string filename, User* usersArray, int maxLimit);

void appendUserToCSV(string filename, User newUser);


#endif // !FILE_UTIL_H
