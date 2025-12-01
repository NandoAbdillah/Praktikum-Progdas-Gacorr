
#include <iostream>
#include "auth/login.h"
#include "auth/register.h"
#include "user/user.h"

using namespace std;

User activeUser;
bool isLoggedIn = false;

void mainMenu()
{
    cout << "=== TIKETKU MAIN MENU ===" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Keluar" << endl;
    cout << "Pilih opsi: ";
}

void userMenu()
{
    cout << "=== USER MENU ===" << endl;
    cout << "Saldo : Rp " << activeUser.saldo << endl;
    cout << "1. Beli Tiket " << endl;
    cout << "2. Cek Saldo & Top Up" << endl;
    cout << "3. Logout" << endl;

    cout << "Pilih opsi: ";
}

void adminMenu()
{
    cout << "=== ADMIN MENU ===" << endl;
    cout << "1. Kelola Tiket " << endl;
    cout << "2. Cek Laporan" << endl;
    cout << "3. Logout" << endl;

    cout << "Pilih opsi: ";
}

int main()
{

    int choice;

    if (checkSession(&activeUser))
    {
        isLoggedIn = true;
        cout << "\n[INFO] Login kembali sebagai " << activeUser.username << "..." << endl;
    }

    while (true)
    {
        if (!isLoggedIn)
        {
            mainMenu();
            cin >> choice;

            if (choice == 1)
            {
                // Login sekarang mengisi struct activeUser
                if (loginUser(&activeUser))
                {
                    isLoggedIn = true;
                }
            }
            else if (choice == 2)
            {
                registerUser();
            }
            else if (choice == 3)
            {
                cout << "Terima kasih telah menggunakan Tiketku." << endl;
                break;
            }
            else
            {
                cout << "Pilihan tidak valid." << endl;
            }
        }
        else
        {
            // Jika sudah login, cek role dari struct
            if (activeUser.role == "admin")
            {
                adminMenu();
            }
            else
            {
                userMenu();
            }

            cin >> choice;
            if (choice == 3)
            {

                isLoggedIn = false;
                logout();

                activeUser.username = "";
                activeUser.role = "";

                cout << "Anda telah logout." << endl;
            }
            else
            {
                cout << "Fitur belum tersedia di demo ini." << endl;
            }
        }
    }

    return 0;
}