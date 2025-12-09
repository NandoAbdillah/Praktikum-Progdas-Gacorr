#ifndef FORGOT_PASSWORD_H
#define FORGOT_PASSWORD_H
#include <string>
#include "../user/user.h"

using namespace std;

namespace auth {

    bool forgotPassword(string usernameInput);
}


#endif // !FORGOT_PASSWORD_H  