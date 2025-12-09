
#include <iostream>
#include "auth/login.h"
#include "auth/register.h"
#include "user/user.h"
#include "menu/menu_user.h"
#include "menu/menu_admin.h"
#include "menu/menu_general.h"
#include "utils/helper.h"
#include "transport/transport.h"
#include "ticket/ticket.h"


using namespace std;




bool initData()
{
    cout << "=== MEMUAT DATA APLIKASI ===" << endl;

    bool usersLoaded = global::loadUsers();
    bool authUserLoaded = global::loadAuthUser();
    bool transportLoaded = transport::loadTransportData();
    bool ticketsLoaded = ticket::loadTickets();
    bool authTicketsLoaded = ticket::loadAuthTickets();
    

    // cout << helper::responseBox(usersLoaded,"Memuat data pengguna dari database.")
    //      << endl;

    if (!usersLoaded && !authUserLoaded && !transportLoaded && !ticketsLoaded && !authTicketsLoaded)
        return false;

    // bool ticketsLoaded = loadTickets();
    // bool transLoaded = loadTransactions();

    return true;
}

int main()
{

    if (!initData())
    {
        cout << "\n[ERROR] Inisialisasi gagal. Program dihentikan.\n";
        return 0;
    }

    //  cout << "\n[SUKSES] Semua data berhasil dimuat. Program dijalankan.\n\n";

    general::clearScreen();

    if(global::isLoggedIn) {
        cout << "[SUKSES] Selamat datang kembali, " << global::authUser.nama_lengkap << "!" << endl;

    }

    int rand;

    while (true)
    {
        if(!global::isLoggedIn) {
            general::authScreen();

        } else {
            // cout << "dah login " << endl;
            if(global::authUser.role == "admin") {
                menu_admin::adminMenu();
            } else {
                menu_user::userMenu();
            }

            if(global::authUser.username == "") {
                isLoggedIn = false;
            }
        }
    }
    


     
}