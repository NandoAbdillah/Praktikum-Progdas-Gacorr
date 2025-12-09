#include "register.h"
#include "../user/user.h"
#include "../utils/helper.h"
#include <iostream>

using namespace std;

namespace auth
{
    bool isUsernameTaken(string usernameInput)
    {
        for (int i = 0; i < global::totalUsers; i++)
        {
            if (global::allUsers[i].username == usernameInput)
            {
                return true;
            }
        }

        return false;
    }

    bool isEmailTaken(string emailInput)
    {
        for (int i = 0; i < global::totalUsers; i++)
        {
            if (global::allUsers[i].email == emailInput)
            {
                return true;
            }
        }

        return false;
    }

    bool isNoTelpTaken(string no_telpInput)
    {
        for (int i = 0; i < global::totalUsers; i++)
        {
            if (global::allUsers[i].no_telp == no_telpInput)
            {
                return true;
            }
        }

        return false;
    }

    bool registerUser(global::User *userRegister)
    {

        userRegister->password = helper::simpleEncrypt(userRegister->password);

        helper::generateUserID(global::totalUsers, &userRegister->id);

        if (global::appendUserToCSV(*userRegister))
        {
            global::allUsers[global::totalUsers] = *userRegister;
            global::totalUsers++;
            global::authUser = *userRegister;

            cout << "[SUKSES] Registrasi berhasil! Silakan login dengan akun Anda." << endl;
            return true;
        }

        cout << "[ERROR] Gagal menyimpan data user. Silakan coba lagi." << endl;
        return false;
    }

}