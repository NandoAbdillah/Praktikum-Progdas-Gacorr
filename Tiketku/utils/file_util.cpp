#include "file_util.h"
#include "helper.h"
#include <iostream>
#include <fstream>

using namespace std;

int loadUsersToArray(string filename, User* usersArray, int maxLimit) {
    ifstream file(filename);
    string line;

    int count = 0;

    if(!file.is_open()) {
        return 0;
    }

    while (getline(file, line) && count < maxLimit) 
    {
        usersArray[count].id = getCSVColumn(line, 0);
        usersArray[count].username = getCSVColumn(line, 1);
        usersArray[count].password = getCSVColumn(line, 2);
        usersArray[count].nama_lengkap = getCSVColumn(line, 3);
        usersArray[count].email = getCSVColumn(line, 4);
        usersArray[count].no_telp = getCSVColumn(line, 5);
        usersArray[count].role = getCSVColumn(line, 6);
        usersArray[count].saldo = stoll(getCSVColumn(line, 7));

        count++;


    }

    file.close();
    return count;
    
}


void appendUserToCSV(string filename, User newUser) {
    ofstream file(filename, ios::app);

    if(file.is_open()) {
        file << newUser.id << ","
             << newUser.username << ","
             << newUser.password << ","
             << newUser.nama_lengkap << ","
             << newUser.email << ","
             << newUser.no_telp << ","
             << newUser.role << ","
             << newUser.saldo << "\n";

        file.close();
    } else {
        cout << "[ERROR] Gagal membuka file untuk menambahkan user baru." << endl;
    }
}