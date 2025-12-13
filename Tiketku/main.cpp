
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

    bool usersLoaded = user::loadUsers();
    bool authUserLoaded = user::loadAuthUser();
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

    if(user::isLoggedIn) {
        cout << "[SUKSES] Selamat datang kembali, " << user::authUser.nama_lengkap << "!" << endl;

    }

    int rand;

    while (true)
    {
        if(!user::isLoggedIn) {
            general::authScreen();

        } else {
            // cout << "dah login " << endl;
            if(user::authUser.role == "admin") {
                menu_admin::adminMenu();
            } else {
                menu_user::userMenu();
            }

            if(user::authUser.username == "") {
                isLoggedIn = false;
            }
        }
    }
    


     
}