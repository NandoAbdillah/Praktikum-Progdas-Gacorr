#ifndef TRANSPORT_H
#define TRANSPORT_H
#define DB_BUS "./database/schedule_bus.csv"
#define DB_KERETA "./database/schedule_train.csv"
#define DB_TICKET_PRICE "./database/prices.csv"
#define MAX_SCHEDULE_CACHE 100
#include <string>

using namespace std;

namespace transport
{

    struct TrainSchedule
    {
        string id_jadwal;
        int kode_rute;
        string nama_kereta;
        string stasiun_asal;
        string stasiun_tujuan;
        string via;
        string jam_berangkat;
        string jam_tiba;
    };

    struct BusSchedule
    {
        string id_jadwal;
        int kode_rute;
        string nama_bus;
        string terminal_asal;
        string terminal_tujuan;
        string jam_berangkat;
        string estimasi_tiba;
    };

    struct TicketPrice
    {
        string id_harga;
        string tipe_kendaraan;
        int kode_kelas;
        string nama_kelas;
        long harga_rupiah;
    };

    extern TrainSchedule allTrainSchedules[MAX_SCHEDULE_CACHE];
    extern BusSchedule allBusSchedules[MAX_SCHEDULE_CACHE];
    extern TicketPrice allTicketPrices[MAX_SCHEDULE_CACHE];

    extern int totalTrainSchedules;
    extern int totalBusSchedules;
    extern int totalTicketPrices;

    bool loadTransportData();
    bool appendTrainScheduleToCSV(TrainSchedule newTrainSchedule);
    bool appendBusScheduleToCSV(BusSchedule newBusSchedule);
    bool overwriteAllTrainScheduleToCSV();

}

#endif
