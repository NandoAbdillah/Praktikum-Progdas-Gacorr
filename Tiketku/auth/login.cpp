#include "login.h"
#include "../utils/helper.h"
#include "../utils/file_util.h"
#include <iostream>
#include <fstream>

using namespace std;

const string DB_USERS = "database/users.csv";
const string FILE_SESSION = "database/session.txt";

void saveSession(string username) {
    ofstream file(FILE_SESSION);
    if (file.is_open()) {
        file << username; 
        file.close();
    }
}

void logout() {
    ofstream file(FILE_SESSION, ios::trunc);
    file.close();
}

bool loginUser(User* activeUser) {
    string inputUser, inputPass;
    
    User daftarUser[MAX_USER_CACHE]; 
    int totalUser = loadUsersToArray(DB_USERS, daftarUser, MAX_USER_CACHE);

    
    if (totalUser == 0) {
        cout << "[INFO] Database kosong/tidak ditemukan." << endl;
        return false; 
    }

    cout << "\n=== LOGIN TIKETKU ===" << endl;
    cout << "Username: ";
    cin >> inputUser;
    cout << "Password: ";
    cin >> inputPass;

    for (int i = 0; i < totalUser; i++) {
        if (daftarUser[i].username == inputUser) {
            string dbPassDec = simpleDecrypt(daftarUser[i].password);
            
            if (dbPassDec == inputPass) {
                *activeUser = daftarUser[i]; 
                saveSession(activeUser->username);
                cout << "[SUKSES] Selamat datang, " << activeUser->nama_lengkap << "!" << endl;
                return true;
            } else {
                cout << "[ERROR] Password salah!" << endl;
                return false;
            }
        }
    }

    cout << "[ERROR] Username tidak ditemukan." << endl;
    return false;
}

bool checkSession(User* activeUser) {
    ifstream file(FILE_SESSION);
    string sessionUsername;

    if (file.is_open()) {
        if (getline(file, sessionUsername)) {
            User daftarUser[MAX_USER_CACHE];
            int totalUser = loadUsersToArray(DB_USERS, daftarUser, MAX_USER_CACHE);
            
            for(int i = 0; i < totalUser; i++) {
                if(daftarUser[i].username == sessionUsername) {
                    *activeUser = daftarUser[i]; 
                    file.close();
                    return true;
                }
            }
        }
        file.close();
    }
    
    return false;
}