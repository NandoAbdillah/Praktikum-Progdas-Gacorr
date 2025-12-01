#include "register.h"
#include "../user/user.h"
#include "../utils/helper.h"
#include "../utils/file_util.h"
#include <iostream>
using namespace std;

const string DB_USER = "database/users.csv";

bool isUsernameTaken (string usernameInput, User* userArray, int totalData) {
    for (int i = 0; i < totalData; i++)
    {
        if (userArray[i].username == usernameInput) {
            return true;
        }
    }

    return false;
    
}

void registerUser() {
    User newUser;
    User tempsUsers[MAX_USER_CACHE];
    string confirmPassword;


    int totalUsers = loadUsersToArray(DB_USER, tempsUsers, MAX_USER_CACHE);

    cout << "=== REGISTRASI PENGGUNA BARU ===" << endl;

    while (true) {
        cout << "Masukkan username: ";
        cin >> newUser.username;

        if (isUsernameTaken(newUser.username, tempsUsers, totalUsers)) {
            cout << "[ERROR] Username sudah digunakan. Silakan coba lagi." << endl;
        } else {
            break;
        }
    }

    cout << "Masukkan password: ";
    cin >> newUser.password;
    cout << "Konfirmasi password: ";
    cin >> confirmPassword;

    if(newUser.password != confirmPassword) {
        cout << "[ERROR] Password dan konfirmasi password tidak sesuai. Registrasi dibatalkan." << endl;
        return;
    }

    cin.ignore();
    cout << "Masukkan nama lengkap: ";
    getline(cin, newUser.nama_lengkap);
    cout << "Masukkan email: ";
    cin >> newUser.email;
    cout << "Masukkan nomor telepon: ";
    cin >> newUser.no_telp;

    newUser.role = "user";
    newUser.saldo = 0;

    generateUserID(totalUsers, &newUser.id);

    newUser.password = simpleEncrypt(newUser.password);
    appendUserToCSV(DB_USER, newUser);
    
}