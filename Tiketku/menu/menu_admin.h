#ifndef MENU_ADMIN_H
#define MENU_ADMIN_H

namespace menu_admin
{
    struct schedule
    {
        string kota_asal;
        string kota_tujuan;
        string tanggal_berangkat;
        string jam_berangkat;
    };

    // schedule kereta;

    void dataUser();
    void dataTiket();
    void tambahJadwal();
    void ubahTarif();
    void logout();
    void adminMenu();

}

#endif // !MENU_ADMIN_H