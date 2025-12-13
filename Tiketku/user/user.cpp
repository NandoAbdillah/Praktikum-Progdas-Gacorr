#include <string>
#include "user.h"
#include "../utils/helper.h"
#include <fstream>
#include <iostream>

namespace user
{
    User allUsers[MAX_USER_CACHE];
    User authUser;

    int totalUsers = 0;
    bool isLoggedIn = false;
    int indexAuthUser = -1;

    bool appendUserToCSV(User newUser)
    {
        ofstream file(DB_USERS, ios::app);

        if (file.is_open())
        {
            file << newUser.id << ","
                 << newUser.username << ","
                 << newUser.password << ","
                 << newUser.nama_lengkap << ","
                 << newUser.email << ","
                 << newUser.no_telp << ","
                 << newUser.role << ","
                 << newUser.saldo << endl;

            file.close();

            return true;
        }
        else
        {

            helper::messageBox("[ERROR] Gagal membuka file untuk menambahkan user baru.");

            return false;
        }
    }

    bool overwriteAllUsersToCSV()
    {
        ofstream file("./database/users.csv");

        if (!file.is_open())
        {
            return false;
        }

        for (int i = 0; i < user::totalUsers; i++)
        {
            file << user::allUsers[i].id << "," << user::allUsers[i].username << "," << user::allUsers[i].password << "," << user::allUsers[i].nama_lengkap << "," << user::allUsers[i].email << "," << user::allUsers[i].no_telp << "," << user::allUsers[i].role << "," << user::allUsers[i].saldo << endl;
        }

        file.close();

        return true;
    }

    bool loadUsers()
    {
        ifstream file(DB_USERS);
        string line;

        int count = 0;

        if (!file.is_open())
        {
            return false;
        }

        while (getline(file, line) && count < MAX_USER_CACHE)
        {
            allUsers[count].id = helper::getCSVColumn(line, 0);
            allUsers[count].username = helper::getCSVColumn(line, 1);
            allUsers[count].password = helper::getCSVColumn(line, 2);
            allUsers[count].nama_lengkap = helper::getCSVColumn(line, 3);
            allUsers[count].email = helper::getCSVColumn(line, 4);
            allUsers[count].no_telp = helper::getCSVColumn(line, 5);
            allUsers[count].role = helper::getCSVColumn(line, 6);
            allUsers[count].saldo = stoll(helper::getCSVColumn(line, 7));

            count++;
        }

        totalUsers = count;

        file.close();

        return true;
    }

    bool loadAuthUser()
    {
        ifstream file("./database/session.txt");

        string usernameSession;
        if (!file.is_open())
        {
            return false;
        }
        if (getline(file, usernameSession))
        {
            for (int i = 0; i < totalUsers; i++)
            {
                if (allUsers[i].username == usernameSession)
                {
                    user::authUser = user::allUsers[i];
                    isLoggedIn = true;
                    file.close();

                    return true;
                }
            }
        }

        return true;
    }

}
