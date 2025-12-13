#include <iostream>
#include <string>
#include "../transport/transport.h"
#include "../user/user.h"
#include "../auth/login.h"
#include "../auth/register.h"
#include "../utils/helper.h"
#include "../ticket/ticket.h"
#include "../auth/forgot_password.h"

using namespace std;

namespace menu_user
{
    // Variabel untuk border kanan dinamis
    const int wContent = 43; // Lebar standar untuk box tiket/profi
    const int wRute = 59;    // Lebar untuk box rute
    const int wKelas = 35;   // Lebar untuk box kelas/tanggal

    void kereta()
    {
        int ruteIndex, kelasKode, pilihanHari;
        string tanggalFix, kursi;

        // Menggunakan padRight karena loop data dinamis belum ada border kanan
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|                  PILIH RUTE KERETA API                      |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        for (int i = 0; i < transport::totalTrainSchedules; i++)
        {
            string baris1 = to_string(i + 1) + ". " + transport::allTrainSchedules[i].stasiun_asal + " - " + transport::allTrainSchedules[i].stasiun_tujuan;

            if (transport::allTrainSchedules[i].via != "-")
            {
                baris1 += " (Via " + transport::allTrainSchedules[i].via + ")";
            }

            cout << "| " << helper::padRight(baris1, wRute) << " |" << endl;

            string baris2 = "   Jam: " + transport::allTrainSchedules[i].jam_berangkat;

            cout << "| " << helper::padRight(baris2, wRute) << " |" << endl;
            cout << "+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +" << endl;
        }

        cout << ">> Pilih rute (1-" << transport::totalTrainSchedules << "): ";
        cin >> ruteIndex;

        if (ruteIndex < 1 || ruteIndex > transport::totalTrainSchedules)
        {
            cout << "\n[!] Rute tidak valid!" << endl;
            return;
        }

        transport::TrainSchedule jadwalTerpilih = transport::allTrainSchedules[ruteIndex - 1];

        // pilih kelas
        cout << "\n+-------------------------------------+" << endl;
        cout << "|         PILIH KELAS LAYANAN         |" << endl;
        cout << "+-------------------------------------+" << endl;

        for (int i = 0; i < transport::totalTicketPrices; i++)
        {
            if (transport::allTicketPrices[i].tipe_kendaraan == "Kereta Api")
            {
                string infoKelas = to_string(transport::allTicketPrices[i].kode_kelas) + ". " +
                                   transport::allTicketPrices[i].nama_kelas + " -> Rp" +
                                   to_string(transport::allTicketPrices[i].harga_rupiah);

                cout << "| " << helper::padRight(infoKelas, wKelas) << " |" << endl;
            }
        }
        cout << "+-------------------------------------+" << endl;

        cout << ">> Pilih kode kelas: ";
        cin >> kelasKode;

        transport::TicketPrice hargaTerpilih;
        bool found = false;
        for (int i = 0; i < transport::totalTicketPrices; i++)
        {
            if (transport::allTicketPrices[i].tipe_kendaraan == "Kereta Api" &&
                transport::allTicketPrices[i].kode_kelas == kelasKode)
            {
                hargaTerpilih = transport::allTicketPrices[i];
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "\n[!] Kelas tidak ditemukan!" << endl;
            return;
        }

        // pilih tanggal
        cout << "\n+-------------------------------------+" << endl;
        cout << "|     PILIH TANGGAL KEBERANGKATAN     |" << endl;
        cout << "+-------------------------------------+" << endl;
        string hari1 = helper::getDate(0);
        string hari2 = helper::getDate(1);
        string hari3 = helper::getDate(2);

        cout << "| " << helper::padRight("1. Hari Ini (" + hari1 + ")", wKelas) << " |" << endl;
        cout << "| " << helper::padRight("2. Besok    (" + hari2 + ")", wKelas) << " |" << endl;
        cout << "| " << helper::padRight("3. Lusa     (" + hari3 + ")", wKelas) << " |" << endl;
        cout << "+-------------------------------------+" << endl;

        cout << ">> Pilih tanggal (1-3): ";
        cin >> pilihanHari;

        if (pilihanHari == 1)
            tanggalFix = hari1;
        else if (pilihanHari == 2)
            tanggalFix = hari2;
        else if (pilihanHari == 3)
            tanggalFix = hari3;
        else
        {
            cout << "\n[!] Pilihan tanggal salah!";
            return;
        }

        // pilih kursi
        bool kursiValid = false;
        do
        {
            cout << "\n+======================================+" << endl;
            cout << "|   DENAH KURSI KERETA (Kapasitas 80)  |" << endl;
            cout << "+======================================+" << endl;
            cout << "| Format: [No] -> Tersedia, [XX]=Penuh |" << endl;
            cout << "+--------------------------------------+" << endl;

            for (int row = 0; row < 20; row++)
            {
                cout << " "; // margin kiri
                for (int col = 1; col <= 4; col++)
                {
                    int nomorKursi = (row * 4) + col;
                    string strNomorKursi = to_string(nomorKursi);
                    bool isTaken = false;

                    for (int i = 0; i < ticket::totalTickets; i++)
                    {
                        if (ticket::allTickets[i].tanggal == tanggalFix &&
                            ticket::allTickets[i].jam == jadwalTerpilih.jam_berangkat &&
                            ticket::allTickets[i].asal == jadwalTerpilih.stasiun_asal &&
                            ticket::allTickets[i].kelas == hargaTerpilih.nama_kelas &&
                            ticket::allTickets[i].tujuan == jadwalTerpilih.stasiun_tujuan &&
                            ticket::allTickets[i].kursi == strNomorKursi)
                        {
                            isTaken = true;
                            break;
                        }
                    }

                    if (isTaken)
                        cout << "[XX]";
                    else
                    {
                        if (nomorKursi < 10)
                            cout << "[ " << nomorKursi << "]";
                        else
                            cout << "[" << nomorKursi << "]";
                    }

                    if (col == 2)
                        cout << "    ";
                    else
                        cout << " ";
                }
                cout << endl;
            }
            cout << "+--------------------------------------+" << endl;

            cout << ">> Masukkan nomor kursi (1-80): ";
            cin >> kursi;

            int kursiInt = stoi(kursi);
            if (kursiInt < 1 || kursiInt > 80)
            {
                cout << "[!] Nomor kursi tidak valid! Masukkan angka 1-80.\n";
                continue;
            }

            bool isBooked = false;
            for (int i = 0; i < ticket::totalTickets; i++)
            {
                if (ticket::allTickets[i].tanggal == tanggalFix &&
                    ticket::allTickets[i].jam == jadwalTerpilih.jam_berangkat &&
                    ticket::allTickets[i].asal == jadwalTerpilih.stasiun_asal &&
                    ticket::allTickets[i].kelas == hargaTerpilih.nama_kelas &&
                    ticket::allTickets[i].tujuan == jadwalTerpilih.stasiun_tujuan &&
                    ticket::allTickets[i].kursi == kursi)
                {
                    isBooked = true;
                    break;
                }
            }

            if (isBooked)
                cout << "[!] Maaf, kursi nomor " << kursi << " sudah terisi. Pilih yang lain!\n";
            else
                kursiValid = true;

        } while (!kursiValid);

        // finalisasi
        ticket::Ticket tiketBaru;
        tiketBaru.id_tiket = helper::generateIDTiket();
        tiketBaru.id_user = user::authUser.id;
        tiketBaru.tipe_kendaraan = "Kereta Api";
        tiketBaru.asal = jadwalTerpilih.stasiun_asal;
        tiketBaru.tujuan = jadwalTerpilih.stasiun_tujuan;
        tiketBaru.kelas = hargaTerpilih.nama_kelas;
        tiketBaru.harga = hargaTerpilih.harga_rupiah;
        tiketBaru.tanggal = tanggalFix;
        tiketBaru.jam = jadwalTerpilih.jam_berangkat;
        tiketBaru.kursi = kursi;

        // cetak pembelian tiket berhasil
        cout << "\n+=============================================+" << endl;
        cout << "|           TIKET BERHASIL DIPESAN            |" << endl;
        cout << "+=============================================+" << endl;
        cout << "| " << helper::padRight("ID Tiket    : " + tiketBaru.id_tiket, wContent) << " |" << endl;
        cout << "| " << helper::padRight("Kendaraan   : " + tiketBaru.tipe_kendaraan + " (" + jadwalTerpilih.nama_kereta + ")", wContent) << " |" << endl;
        cout << "| " << helper::padRight("Rute        : " + tiketBaru.asal + " - " + tiketBaru.tujuan, wContent) << " |" << endl;
        if (jadwalTerpilih.via != "-")
            cout << "| " << helper::padRight("Via         : " + jadwalTerpilih.via, wContent) << " |" << endl;
        cout << "| " << helper::padRight("Jadwal      : " + tiketBaru.tanggal + " " + tiketBaru.jam, wContent) << " |" << endl;
        cout << "| " << helper::padRight("Kelas       : " + tiketBaru.kelas, wContent) << " |" << endl;
        cout << "| " << helper::padRight("Kursi       : " + tiketBaru.kursi, wContent) << " |" << endl;
        cout << "+---------------------------------------------+" << endl;
        cout << "| " << helper::padRight("Total Bayar : Rp" + to_string(tiketBaru.harga), wContent) << " |" << endl;
        cout << "+=============================================+" << endl;

        ticket::appendTicketToCSV(tiketBaru);
        ticket::loadTickets();
    }

    void bus()
    {
        int ruteIndex, kelasKode, pilihanHari;
        string tanggalFix, kursi;

        // rute bus
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|                  PILIH RUTE BUS ANTAR KOTA                  |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        for (int i = 0; i < transport::totalBusSchedules; i++)
        {
            string baris1 = to_string(i + 1) + ". " + transport::allBusSchedules[i].terminal_asal + " - " + transport::allBusSchedules[i].terminal_tujuan;
            string baris2 = "   Jam: " + transport::allBusSchedules[i].jam_berangkat + " (Tiba: " + transport::allBusSchedules[i].estimasi_tiba + ")";

            cout << "| " << helper::padRight(baris1, wRute) << " |" << endl;
            cout << "| " << helper::padRight(baris2, wRute) << " |" << endl;
            cout << "+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +" << endl;
        }

        cout << ">> Pilih rute (1-" << transport::totalBusSchedules << "): ";
        cin >> ruteIndex;

        if (ruteIndex < 1 || ruteIndex > transport::totalBusSchedules)
        {
            cout << "\n[!] Rute tidak valid!" << endl;
            return;
        }

        transport::BusSchedule jadwalTerpilih = transport::allBusSchedules[ruteIndex - 1];

        // kelas
        cout << "\n+-------------------------------------+" << endl;
        cout << "|         PILIH KELAS LAYANAN         |" << endl;
        cout << "+-------------------------------------+" << endl;

        for (int i = 0; i < transport::totalTicketPrices; i++)
        {
            if (transport::allTicketPrices[i].tipe_kendaraan == "Bus")
            {
                string infoKelas = to_string(transport::allTicketPrices[i].kode_kelas) + ". " +
                                   transport::allTicketPrices[i].nama_kelas + " -> Rp" +
                                   to_string(transport::allTicketPrices[i].harga_rupiah);

                cout << "| " << helper::padRight(infoKelas, wKelas) << " |" << endl;
            }
        }
        cout << "+-------------------------------------+" << endl;

        cout << ">> Pilih kode kelas: ";
        cin >> kelasKode;

        transport::TicketPrice hargaTerpilih;
        bool found = false;
        for (int i = 0; i < transport::totalTicketPrices; i++)
        {
            if (transport::allTicketPrices[i].tipe_kendaraan == "Bus" &&
                transport::allTicketPrices[i].kode_kelas == kelasKode)
            {
                hargaTerpilih = transport::allTicketPrices[i];
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "\n[!] Kelas tidak ditemukan!" << endl;
            return;
        }

        // tanggal
        cout << "\n+-------------------------------------+" << endl;
        cout << "|     PILIH TANGGAL KEBERANGKATAN     |" << endl;
        cout << "+-------------------------------------+" << endl;
        string hari1 = helper::getDate(0);
        string hari2 = helper::getDate(1);
        string hari3 = helper::getDate(2);

        cout << "| " << helper::padRight("1. Hari Ini (" + hari1 + ")", wKelas) << " |" << endl;
        cout << "| " << helper::padRight("2. Besok    (" + hari2 + ")", wKelas) << " |" << endl;
        cout << "| " << helper::padRight("3. Lusa     (" + hari3 + ")", wKelas) << " |" << endl;
        cout << "+-------------------------------------+" << endl;

        cout << ">> Pilih tanggal (1-3): ";
        cin >> pilihanHari;

        if (pilihanHari == 1)
            tanggalFix = hari1;
        else if (pilihanHari == 2)
            tanggalFix = hari2;
        else if (pilihanHari == 3)
            tanggalFix = hari3;
        else
        {
            cout << "\n[!] Pilihan tanggal salah!";
            return;
        }

        // kursi
        bool kursiValid = false;
        do
        {
            cout << "\n+======================================+" << endl;
            cout << "|      DENAH KURSI BUS (Kapasitas 48)  |" << endl;
            cout << "+======================================+" << endl;
            cout << "|             [  SOPIR  ]              |" << endl;
            cout << "+--------------------------------------+" << endl;

            for (int row = 0; row < 12; row++)
            {
                cout << " ";
                for (int col = 1; col <= 4; col++)
                {
                    int nomorKursi = (row * 4) + col;
                    string strNomorKursi = to_string(nomorKursi);
                    bool isTaken = false;

                    for (int i = 0; i < ticket::totalTickets; i++)
                    {
                        if (ticket::allTickets[i].tanggal == tanggalFix &&
                            ticket::allTickets[i].jam == jadwalTerpilih.jam_berangkat &&
                            ticket::allTickets[i].asal == jadwalTerpilih.terminal_asal &&
                            ticket::allTickets[i].kelas == hargaTerpilih.nama_kelas &&
                            ticket::allTickets[i].tujuan == jadwalTerpilih.terminal_tujuan &&
                            ticket::allTickets[i].kursi == strNomorKursi)
                        {
                            isTaken = true;
                            break;
                        }
                    }

                    if (isTaken)
                        cout << "[XX]";
                    else
                    {
                        if (nomorKursi < 10)
                            cout << "[ " << nomorKursi << "]";
                        else
                            cout << "[" << nomorKursi << "]";
                    }

                    if (col == 2)
                        cout << "    ";
                    else
                        cout << " ";
                }
                cout << endl;
            }
            cout << "+--------------------------------------+" << endl;
            cout << "| Keterangan: [XX] = Terisi            |" << endl;
            cout << "+--------------------------------------+" << endl;

            cout << ">> Masukkan nomor kursi (1-48): ";
            cin >> kursi;

            int kursiInt = stoi(kursi);
            if (kursiInt < 1 || kursiInt > 48)
            {
                cout << "[!] Nomor kursi tidak valid! Masukkan angka 1-48.\n";
                continue;
            }

            bool isBooked = false;
            for (int i = 0; i < ticket::totalTickets; i++)
            {
                if (ticket::allTickets[i].tanggal == tanggalFix &&
                    ticket::allTickets[i].jam == jadwalTerpilih.jam_berangkat &&
                    ticket::allTickets[i].asal == jadwalTerpilih.terminal_asal &&
                    ticket::allTickets[i].kelas == hargaTerpilih.nama_kelas &&
                    ticket::allTickets[i].tujuan == jadwalTerpilih.terminal_tujuan &&
                    ticket::allTickets[i].kursi == kursi)
                {
                    isBooked = true;
                    break;
                }
            }

            if (isBooked)
                cout << "[!] Maaf, kursi nomor " << kursi << " sudah terisi. Pilih yang lain!\n";
            else
                kursiValid = true;

        } while (!kursiValid);

        // finalisasi
        ticket::Ticket tiketBaru;
        tiketBaru.id_tiket = helper::generateIDTiket();
        tiketBaru.id_user = user::authUser.id;
        tiketBaru.tipe_kendaraan = "Bus";
        tiketBaru.asal = jadwalTerpilih.terminal_asal;
        tiketBaru.tujuan = jadwalTerpilih.terminal_tujuan;
        tiketBaru.kelas = hargaTerpilih.nama_kelas;
        tiketBaru.harga = hargaTerpilih.harga_rupiah;
        tiketBaru.tanggal = tanggalFix;
        tiketBaru.jam = jadwalTerpilih.jam_berangkat;
        tiketBaru.kursi = kursi;

        // output
        cout << "\n+=============================================+" << endl;
        cout << "|           TIKET BERHASIL DIPESAN            |" << endl;
        cout << "+=============================================+" << endl;
        cout << "| " << helper::padRight("ID Tiket    : " + tiketBaru.id_tiket, wContent) << " |" << endl;
        cout << "| " << helper::padRight("Kendaraan   : " + tiketBaru.tipe_kendaraan, wContent) << " |" << endl;
        cout << "| " << helper::padRight("Rute        : " + tiketBaru.asal + " - " + tiketBaru.tujuan, wContent) << " |" << endl;
        cout << "| " << helper::padRight("Jadwal      : " + tiketBaru.tanggal + " " + tiketBaru.jam, wContent) << " |" << endl;
        cout << "| " << helper::padRight("Kelas       : " + tiketBaru.kelas, wContent) << " |" << endl;
        cout << "| " << helper::padRight("Kursi       : " + tiketBaru.kursi, wContent) << " |" << endl;
        cout << "+---------------------------------------------+" << endl;
        cout << "| " << helper::padRight("Total Bayar : Rp" + to_string(tiketBaru.harga), wContent) << " |" << endl;
        cout << "+=============================================+" << endl;

        ticket::appendTicketToCSV(tiketBaru);
        ticket::loadTickets();
    }

    void pilihKendaraan()
    {
        int choice;
        // tidak pakai padright karena statis
        cout << "\n+---------------------------------+" << endl;
        cout << "|      PILIH JENIS KENDARAAN      |" << endl;
        cout << "+---------------------------------+" << endl;
        cout << "| 1. Kereta Api                   |" << endl;
        cout << "| 2. Bus                          |" << endl;
        cout << "+---------------------------------+" << endl;
        cout << ">> Masukkan pilihan: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            kereta();
            break;

        case 2:
            bus();
            break;
        }
    }

    void cekStatusTiket()
    {
        string id;
        cout << "\n+---------------------------------+" << endl;
        cout << "|        CEK STATUS TIKET         |" << endl;
        cout << "+---------------------------------+" << endl;
        cout << ">> Masukkan ID Pembelian: ";
        cin >> id;

        bool found = false;
        int index = -1;

        // cari ID di database array
        for (int i = 0; i < ticket::totalTickets; i++)
        {
            if (ticket::allTickets[i].id_tiket == id)
            {
                found = true;
                index = i;
                break;
            }
        }

        if (found)
        {
            ticket::Ticket t = ticket::allTickets[index];
            string status = "AKTIF";
            string keterangan = "Tiket dapat digunakan";

            // cek kadaluarsa
            string today = helper::getDate(0);

            int yearNow = stoi(today.substr(6, 4));
            int yearTiket = stoi(t.tanggal.substr(6, 4));

            int monthNow = stoi(today.substr(3, 2));
            int monthTiket = stoi(t.tanggal.substr(3, 2));

            int dayNow = stoi(today.substr(0, 2));
            int dayTiket = stoi(t.tanggal.substr(0, 2));

            if (yearTiket < yearNow)
            {
                status = "KADALUARSA";
            }
            else if (yearTiket == yearNow && monthTiket < monthNow)
            {
                status = "KADALUARSA";
            }
            else if (yearTiket == yearNow && monthTiket == monthNow && dayTiket < dayNow)
            {
                status = "KADALUARSA";
            }

            if (status == "KADALUARSA")
            {
                keterangan = "Jadwal telah lewat";
                cout << "\n+=============================================+" << endl;
                cout << "|             STATUS: KADALUARSA              |" << endl;
                cout << "+=============================================+" << endl;
            }
            else
            {
                cout << "\n+=============================================+" << endl;
                cout << "|                DETAIL TIKET                 |" << endl;
                cout << "+=============================================+" << endl;
            }

            cout << "| " << helper::padRight("ID           : " + t.id_tiket, wContent) << " |" << endl;
            cout << "| " << helper::padRight("Status       : " + status, wContent) << " |" << endl;
            cout << "| " << helper::padRight("Keterangan   : " + keterangan, wContent) << " |" << endl;
            cout << "| " << helper::padRight("Kendaraan    : " + t.tipe_kendaraan, wContent) << " |" << endl;
            cout << "| " << helper::padRight("Rute         : " + t.asal + " - " + t.tujuan, wContent) << " |" << endl;
            cout << "| " << helper::padRight("Kelas        : " + t.kelas, wContent) << " |" << endl;
            cout << "| " << helper::padRight("Jadwal       : " + t.tanggal + " " + t.jam, wContent) << " |" << endl;
            cout << "| " << helper::padRight("Kursi        : " + t.kursi, wContent) << " |" << endl;
            cout << "| " << helper::padRight("Harga        : Rp" + to_string(t.harga), wContent) << " |" << endl;
            cout << "+=============================================+" << endl;
        }
        else
        {

            cout << "\n+=============================================+" << endl;
            cout << "|           STATUS: TIDAK DITEMUKAN           |" << endl;
            cout << "+=============================================+" << endl;
            cout << "| " << helper::padRight("ID tiket     : " + id, wContent) << " |" << endl;
            cout << "| " << helper::padRight("Keterangan   : ID anda tidak terdaftar", wContent) << " |" << endl;
            cout << "+=============================================+" << endl;
        }
    }

    void riwayatPembelianTiket()
    {
        int wHistory = 65;

        cout << "\n+===================================================================+" << endl;
        cout << "|                      RIWAYAT PEMBELIAN TIKET                      |" << endl;
        cout << "+===================================================================+" << endl;

        cout << "| " << helper::padRight("Total Tiket Ditemukan: " + to_string(ticket::totalAuthTickets), wHistory) << " |" << endl;
        cout << "+===================================================================+" << endl;

        for (int i = 0; i < ticket::totalAuthTickets; i++)
        {
            cout << "\n+-------------------------------------------------------------------+" << endl;
            cout << "| " << helper::padRight("TIKET KE-" + to_string(i + 1), wHistory) << " |" << endl;
            cout << "+-------------------------------------------------------------------+" << endl;
            cout << "| " << helper::padRight("ID Tiket    : " + ticket::authTickets[i].id_tiket, wHistory) << " |" << endl;
            cout << "| " << helper::padRight("Kendaraan   : " + ticket::authTickets[i].tipe_kendaraan, wHistory) << " |" << endl;
            cout << "| " << helper::padRight("Rute        : " + ticket::authTickets[i].asal + " - " + ticket::authTickets[i].tujuan, wHistory) << " |" << endl;
            cout << "| " << helper::padRight("Jadwal      : " + ticket::authTickets[i].tanggal + " " + ticket::authTickets[i].jam, wHistory) << " |" << endl;
            cout << "| " << helper::padRight("Kelas       : " + ticket::authTickets[i].kelas, wHistory) << " |" << endl;
            cout << "| " << helper::padRight("Kursi       : " + ticket::authTickets[i].kursi, wHistory) << " |" << endl;
            cout << "| " << helper::padRight("Total Bayar : Rp" + to_string(ticket::authTickets[i].harga), wHistory) << " |" << endl;
            cout << "+-------------------------------------------------------------------+" << endl;
        }
    }

    void gantiPassword()
    {
        cout << "\n+---------------------------------+" << endl;
        cout << "|         GANTI PASSWORD          |" << endl;
        cout << "+---------------------------------+" << endl;

        if (auth::forgotPassword(user::authUser.username))
        {
            cout << "[SUKSES] Password berhasil diubah." << endl;
        }
        else
        {
            cout << "[GAGAL] Ganti password gagal. Silakan coba lagi." << endl;
        };
    }

    void editProfile()
    {
        cout << "\n+---------------------------------+" << endl;
        cout << "|           EDIT PROFIL           |" << endl;
        cout << "+---------------------------------+" << endl;
        cout << "| 1. Username                     |" << endl;
        cout << "| 2. Nama Lengkap                 |" << endl;
        cout << "| 3. Email                        |" << endl;
        cout << "| 4. Nomor Telepon                |" << endl;
        cout << "| 5. Kembali ke Menu Profil       |" << endl;
        cout << "+---------------------------------+" << endl;

        int pilihan;
        cout << ">> Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
        {
            string usernameBaru;
            cout << "Masukkan username baru: ";
            getline(cin, usernameBaru);

            if (auth::isUsernameTaken(usernameBaru))
            {
                cout << "[!] Username sudah digunakan. Silakan pilih username lain." << endl;
                editProfile();
            }
            else
            {
                user::authUser.username = usernameBaru;
                user::allUsers[user::indexAuthUser].username = usernameBaru;

                if (user::overwriteAllUsersToCSV())
                    cout << "[OK] Username berhasil diubah." << endl;
                else
                    cout << "[Error] Gagal mengubah Username." << endl;
            }
            break;
        }
        case 2:
        {
            string namaBaru;
            cout << "Masukkan Nama Lengkap baru: ";
            getline(cin, namaBaru);

            user::authUser.nama_lengkap = namaBaru;
            user::allUsers[user::indexAuthUser].nama_lengkap = namaBaru;

            if (user::overwriteAllUsersToCSV())
                cout << "[OK] Nama Lengkap berhasil diubah." << endl;
            else
                cout << "[Error] Gagal mengubah Nama Lengkap." << endl;
            break;
        }

        case 3:
        {
            string emailBaru;
            cout << "Masukkan email baru: ";
            getline(cin, emailBaru);

            if (auth::isEmailTaken(emailBaru))
            {
                cout << "[!] Email sudah digunakan. Silakan masukkan email lain." << endl;
                editProfile();
            }
            else
            {
                user::authUser.email = emailBaru;
                user::allUsers[user::indexAuthUser].email = emailBaru;

                if (user::overwriteAllUsersToCSV())
                    cout << "[OK] Email berhasil diubah." << endl;
                else
                    cout << "[Error] Gagal mengubah Email." << endl;
            }
            break;
        }

        case 4:
        {
            string noTelpBaru;
            cout << "Masukkan Nomor Telepon baru: ";
            getline(cin, noTelpBaru);

            if (auth::isNoTelpTaken(noTelpBaru))
            {
                cout << "[!] Nomor Telepon sudah digunakan." << endl;
                editProfile();
            }
            else
            {
                user::authUser.no_telp = noTelpBaru;
                user::allUsers[user::indexAuthUser].no_telp = noTelpBaru;

                if (user::overwriteAllUsersToCSV())
                    cout << "[OK] Nomor Telepon berhasil diubah." << endl;
                else
                    cout << "[Error] Gagal mengubah Nomor Telepon." << endl;
            }
            break;
        }
        default:
            cout << "Kembali ke Menu Profil..." << endl;
            break;
        }
    }

    void profilPengguna()
    {
        int opsi;

        cout << "\n+=============================================+" << endl;
        cout << "|               PROFIL PENGGUNA               |" << endl;
        cout << "+=============================================+" << endl;
        cout << "| " << helper::padRight("Username : " + user::authUser.username, wContent) << " |" << endl;
        cout << "| " << helper::padRight("Nama     : " + user::authUser.nama_lengkap, wContent) << " |" << endl;
        cout << "| " << helper::padRight("Email    : " + user::authUser.email, wContent) << " |" << endl;
        cout << "| " << helper::padRight("No HP    : " + user::authUser.no_telp, wContent) << " |" << endl;
        cout << "+---------------------------------------------+" << endl;
        cout << "| Opsi:                                       |" << endl;
        cout << "| 1. Ubah Profil                              |" << endl;
        cout << "| 2. Ubah Password                            |" << endl;
        cout << "| 3. Kembali ke Menu Utama                    |" << endl;
        cout << "+=============================================+" << endl;

        cout << ">> Pilih opsi: ";
        cin >> opsi;

        switch (opsi)
        {
        case 1:
            editProfile();
            break;

        case 2:
            gantiPassword();
            break;

        default:
            break;
        }
    }

    void logout()
    {
        auth::logout();
        cout << "\n[INFO] Keluar dari program..." << endl;
    }

    void userMenu()
    {
        int choice;

        cout << "\n+=============================================+" << endl;
        cout << "|              MAIN MENU - USER               |" << endl;
        cout << "+=============================================+" << endl;
        cout << "| 1. Beli Tiket                               |" << endl;
        cout << "| 2. Cek Status Tiket                         |" << endl;
        cout << "| 3. Riwayat Pembelian Tiket                  |" << endl;
        cout << "| 4. Profil Pengguna                          |" << endl;
        cout << "| 5. Ganti Password                           |" << endl;
        cout << "| 6. Logout                                   |" << endl;
        cout << "+=============================================+" << endl;

        cout << ">> Pilih opsi: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            pilihKendaraan();
            break;
        }
        case 2:
        {
            cekStatusTiket();
            break;
        }
        case 3:
        {
            riwayatPembelianTiket();
            break;
        }
        case 4:
        {
            profilPengguna();
            break;
        }
        case 5:
        {
            gantiPassword();
            break;
        }
        case 6:
        {
            logout();
            break;
        }
        default:
            break;
        }
    }
}