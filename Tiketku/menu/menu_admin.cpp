#include <iostream>
#include "../auth/login.h"
#include "../utils/helper.h"
#include "../user/user.h"
#include "./menu_admin.h"
#include "../transport/transport.h"
#include "../ticket/ticket.h"
#include <cstring>

using namespace std;

namespace menu_admin
{

    void dataUser()
    {

        int wNama = 20;
        int wUsername = 15;
        int wEmail = 30;
        int wTelepon = 15;

        // Header
        cout << "+----------------------+-----------------+--------------------------------+-----------------+-----------------+\n";
        cout << "| " << helper::padRight("Nama Lengkap", wNama)
             << " | " << helper::padRight("Username", wUsername)
             << " | " << helper::padRight("Email", wEmail)
             << " | " << helper::padRight("No Telepon", wTelepon)
             << " |\n";
        cout << "+----------------------+-----------------+--------------------------------+-----------------+-----------------+\n";

        // Loop data user
        for (int i = 0; i < global::totalUsers; i++)
        {

            cout << "| " << helper::padRight(global::allUsers[i].nama_lengkap, wNama)
                 << " | " << helper::padRight(global::allUsers[i].username, wUsername)
                 << " | " << helper::padRight(global::allUsers[i].email, wEmail)
                 << " | " << helper::padRight(global::allUsers[i].no_telp, wTelepon)
                 << " |\n";
        }

        cout << "+----------------------+-----------------+--------------------------------+-----------------+-----------------+\n";
    }

    void dataTiket()
    {
        int choice;
        cout << "=== KENDARAAN ===" << endl;
        cout << "1. Kereta Api" << endl;
        cout << "2. Bus" << endl;

        cout << "Pilih opsi: ";
        cin >> choice;

        if (!ticket::loadBusTickets &&
            !ticket::loadTrainTickets)
        {
            cout << "Terjadi kesalahan saat memuat data tiket";
            return;
        }

        string kendaraan;
        int totalTiketTampil;
        ticket::Ticket tiketTampil[100];

        switch (choice)
        {
        case 1:
        {
            kendaraan = "Kereta Api";
            totalTiketTampil = ticket::totalTrainTickets;
        }
        break;

        default:
        {
            kendaraan = "Bus";
            totalTiketTampil = ticket::totalBusTickets;
        }
        break;
        }

        int wHistory = 65;

        cout << "\n+===================================================================+" << endl;
        cout << "|                      RIWAYAT PEMBELIAN TIKET " << kendaraan << "             |" << endl;
        cout << "+===================================================================+" << endl;

        cout << "| " << helper::padRight("Total Tiket Ditemukan: " + to_string(totalTiketTampil), wHistory) << " |" << endl;
        cout << "+===================================================================+" << endl;

        for (int i = 0; i < ticket::totalTickets; i++)
        {

            if (ticket::allTickets[i].tipe_kendaraan == kendaraan)
            {
                tiketTampil[i] = ticket::allTickets[i];
            }
            else
            {
                continue;
            }

            cout << "\n+-------------------------------------------------------------------+" << endl;
            cout << "| " << helper::padRight("TIKET KE-" + to_string(i + 1), wHistory) << " |" << endl;
            cout << "+-------------------------------------------------------------------+" << endl;
            cout << "| " << helper::padRight("ID Tiket    : " + tiketTampil[i].id_tiket, wHistory) << " |" << endl;
            cout << "| " << helper::padRight("Kendaraan   : " + tiketTampil[i].tipe_kendaraan, wHistory) << " |" << endl;
            cout << "| " << helper::padRight("Rute        : " + tiketTampil[i].asal + " - " + tiketTampil[i].tujuan, wHistory) << " |" << endl;
            cout << "| " << helper::padRight("Jadwal      : " + tiketTampil[i].tanggal + " " + tiketTampil[i].jam, wHistory) << " |" << endl;
            cout << "| " << helper::padRight("Kelas       : " + tiketTampil[i].kelas, wHistory) << " |" << endl;
            cout << "| " << helper::padRight("Kursi       : " + tiketTampil[i].kursi, wHistory) << " |" << endl;
            cout << "| " << helper::padRight("Total Bayar : Rp" + to_string(tiketTampil[i].harga), wHistory) << " |" << endl;
            cout << "+-------------------------------------------------------------------+" << endl;
        }
    }

    void AllTiket(int kendaraan)
    {
    }

    void jadwalKereta()
    {

        transport::TrainSchedule jadwalKeretaBaru;

        cout << "=== Tambah Jadwal Baru ===" << endl;
        cout << "Nama Kereta : ";
        getline(cin, jadwalKeretaBaru.nama_kereta);

        cout << "Stasiun Asal : ";

        getline(cin, jadwalKeretaBaru.stasiun_asal);
        cout << "Stasiun Tujuan : ";
        getline(cin, jadwalKeretaBaru.stasiun_tujuan);

        cout << "Via : ";
        getline(cin, jadwalKeretaBaru.via);

        cout << "Jam Berangkat : ";
        getline(cin, jadwalKeretaBaru.jam_berangkat);

        cout << "Jam Tiba : ";
        getline(cin, jadwalKeretaBaru.jam_tiba);

        int trainScheduleTotal = transport::totalTrainSchedules + 1;
        helper::generateIDJadwal(trainScheduleTotal, &jadwalKeretaBaru.id_jadwal, "KA");

        jadwalKeretaBaru.kode_rute = 1;

        if (transport::appendTrainScheduleToCSV(jadwalKeretaBaru))
        {
            transport::totalTrainSchedules++;
        }
        else
        {
            jadwalKereta();
        }
    }

    void jadwalBus()
    {

        transport::BusSchedule jadwalBusBaru;

        cout << "=== Tambah Jadwal Baru ===" << endl;
        cout << "Nama Bus : ";

        getline(cin, jadwalBusBaru.nama_bus);

        cout << "Stasiun Asal : ";
        getline(cin, jadwalBusBaru.terminal_asal);

        cout << "Stasiun Tujuan : ";
        getline(cin, jadwalBusBaru.terminal_tujuan);

        cout << "Jam Berangkat : ";
        getline(cin, jadwalBusBaru.jam_berangkat);

        cout << "Jam Tiba : ";
        getline(cin, jadwalBusBaru.estimasi_tiba);

        int busScheduleTotal = transport::totalBusSchedules + 1;
        helper::generateIDJadwal(busScheduleTotal, &jadwalBusBaru.id_jadwal, "BS");

        jadwalBusBaru.kode_rute = 1;

        if (transport::appendBusScheduleToCSV(jadwalBusBaru))
        {
            transport::totalBusSchedules++;
        }
        else
        {
            jadwalBus();
        }
    }

    void tambahJadwal()
    {
        int choice;

        cout << "=== KENDARAAN ===" << endl;
        cout << "1. Kereta Api" << endl;
        cout << "2. Bus" << endl;

        cout << "Pilih opsi: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1: // menambah jadwal kereta api
            // cout << "=== Tambah Jadwal Baru ===";
            // cout << "Kota Asal : ";
            // cout << "Kota Tujuan : ";
            // cout << "Tanggal Berangkat : ";
            // cout << "Jam Berangkat";

            jadwalKereta();

            break;
        case 2: // menambah jadwal bus

            jadwalBus();
            break;
        default:
            break;
        }
    }

    void logout()
    {
        auth::logout();
        cout << "Keluar dari program" << endl;
    }

    void adminMenu()
    {

        int choice;

        cout << "=== ADMIN MENU ===" << endl;
        cout << "1. Lihat Data User " << endl;
        cout << "2. Lihat Data Tiket " << endl;
        cout << "3. Tambahkan Jadwal " << endl;
        cout << "4. Logout " << endl;

        cout << "Pilih opsi: ";

        cin >> choice;
        // cin.ignore();

        switch (choice)
        {
        case 1:

            dataUser();
            break;
        case 2:
            dataTiket();
            break;
        case 3:
            tambahJadwal();
            break;
        case 4:
            logout();

        default:
            break;
        }
    }

}