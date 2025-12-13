#include <iostream>
#include "../auth/login.h"
// Ensure the auth namespace has a valid loginUser function declaration
#include "../auth/register.h"
#include "../user/user.h"
#include "../utils/helper.h"
#include "../auth/forgot_password.h"

using namespace std;
using namespace user;
using namespace auth;

namespace general
{
    int choice;

    void clearScreen()
    {
        cout << "\033[2J\033[1;1H";
    }

    void loginScreen()
    {

        user::User userLogin;

        cout << "\n=== LOGIN TIKETKU ===" << endl;
        while (true)
        {

            string username, password;
            cout << "Tulis 'back' pada username untuk kembali ke menu sebelumnya." << endl;
            cout << "Tulis 'forgot' pada password untuk lupa password dan reset passwordnya"<< endl;
            cout << "Username: ";
            cin >> username;

            if (username == "back")
            {
                clearScreen();
                return;
            }

            cout << "Password: ";
            cin >> password;

            if (password == "forgot")
            {
                // clearScreen();
                // forgotPasswordScreen();
                if (auth::forgotPassword(username))
                {
                    clearScreen();
                    cout << "[SUKSES] Password berhasil direset. Silakan login dengan password baru." << endl;
                }
                continue;
            }

            userLogin.username = username;
            userLogin.password = password;

            if (auth::loginUser(&userLogin))
            {

                user::isLoggedIn = true;
                cout << "Selamat datang, " << authUser.nama_lengkap << "!" << endl;
                break;
            }
            else
            {
                // clearScreen();
                cout << "[GAGAL] Login gagal. Silakan coba lagi." << endl;
            }
        }
    }

    string getUsername()
    {
        string username;
        cout << "Masukkan username: ";
        cin >> username;

        if (auth::isUsernameTaken(username))
        {
            cout << "[ERROR] Username sudah digunakan. Silakan pilih username lain." << endl;

            return getUsername();
        }

        return username;
    }

    string getPassword()
    {

        string password, konfirmasiPassword;
        cout << "Masukkan password: ";
        cin >> password;
        cout << "Konfirmasi password: ";
        cin >> konfirmasiPassword;

        if (password != konfirmasiPassword)
        {
            cout << "[ERROR] Password dan konfirmasi password tidak sesuai. Silakan coba lagi." << endl;
            return getPassword();
        }

        return password;
    }
    void registerScreen()
    {
        user::User userRegister;

        cout << "=== REGISTRASI PENGGUNA BARU ===" << endl;

        while (true)
        {

            string id, username, password, konfirmasiPassword, namaLengkap, email, noTelp, role;
            long long saldo;

            cout << "Tulis 'back' pada username untuk kembali ke menu sebelumnya." << endl;

            username = getUsername();
            if (username == "back")
            {
                clearScreen();
                return;
            }

            password = getPassword();

            cin.ignore();
            cout << "Masukkan nama lengkap: ";
            getline(cin, namaLengkap);
            cout << "Masukkan email: ";
            cin >> email;
            cout << "Masukkan nomor telepon: ";
            cin >> noTelp;

            role = "user";
            saldo = 0;

            userRegister.username = username;
            userRegister.password = password;
            userRegister.nama_lengkap = namaLengkap;
            userRegister.email = email;
            userRegister.no_telp = noTelp;
            userRegister.role = role;
            userRegister.saldo = saldo;

            if (auth::registerUser(&userRegister))
            {

                user::isLoggedIn = true;
                cout << "Selamat datang, " << authUser.nama_lengkap << "!" << endl;
                break;
            }
            else
            {
                clearScreen();
                cout << "[GAGAL] Register gagal. Silakan coba lagi." << endl;
            }
        }
    }

    void authScreen()
    {
        cout << "=== SELAMAT DATANG DI TIKETKU ===" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih opsi: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            clearScreen();
            loginScreen();
            break;

        case 2:
            clearScreen();
            registerScreen();
            break;

        case 3:
            break;

        default:
            break;
        }
    }
}
