
#include "../user/user.h"
#include "../utils/helper.h"
#include <iostream>

using namespace std;

namespace auth
{

    bool forgotPassword(string usernameInput)
    {

        bool userFound = false;
        for (int i = 0; i < user::totalUsers; i++)
        {

            if (user::allUsers[i].username == usernameInput)
            {

                userFound = true;

                cout << "Username ditemukan. Silakan masukkan password baru Anda." << endl;

                string newPassword;
                cout << "Masukkan password baru: ";
                cin >> newPassword;

                user::allUsers[i].password = helper::simpleEncrypt(newPassword);

                if (user::overwriteAllUsersToCSV())
                {

                    return true;
                }
                else
                {
                    cout << "[ERROR] Gagal memperbarui password. Silakan coba lagi." << endl;

                    return false;
                }
                break;
            }
        }

        if (!userFound)
        {
            cout << "[ERROR] Username tidak ditemukan." << endl;
            return false;
        }

        return true;
    }
}