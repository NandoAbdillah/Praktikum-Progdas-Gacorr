#include "login.h"
#include "../utils/helper.h"
#include <iostream>
#include <fstream>
#include "../user/user.h"

using namespace std;
using namespace global;
using namespace helper;

namespace auth
{


    void saveSession(string username)
    {
        ofstream file(FILE_SESSION);
        if (file.is_open())
        {
            file << username;
            file.close();
        }
    }

    void logout()
    {

        global::isLoggedIn = false;
        global::authUser = User();
        ofstream file(FILE_SESSION, ios::trunc);
        file.close();
    }

    bool loginUser(User *userLogin)
    {

        for (int i = 0; i < totalUsers; i++)
        {
            if (allUsers[i].username == userLogin->username)
            {
                string dbPassDec = simpleDecrypt(allUsers[i].password);

                if (dbPassDec == userLogin->password)
                {
                    authUser = allUsers[i];
                    global::indexAuthUser = i;
                    saveSession(userLogin->username);
                    cout << "[SUKSES] Selamat datang, " << userLogin->nama_lengkap << "!" << endl;
                    return true;
                }
                else
                {
                    cout << "[ERROR] Password salah!" << endl;
                    return false;
                }
            }
        }

        cout << "[ERROR] Username tidak ditemukan." << endl;
        return false;
    }

    bool checkSession(User *activeUser)
    {
        ifstream file(FILE_SESSION);
        string sessionUsername;

        if (file.is_open())
        {
            if (getline(file, sessionUsername))
            {
                User allUsers[MAX_USER_CACHE];

                for (int i = 0; i < totalUsers; i++)
                {
                    if (allUsers[i].username == sessionUsername)
                    {
                        // *activeUser = daftarUser[i];

                        authUser = allUsers[i];
                        file.close();
                        return true;
                    }
                }
            }
            file.close();
        }

        return false;
    }
}
