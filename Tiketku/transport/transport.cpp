#include <iostream>
#include <fstream>
#include "transport.h"
#include "../utils/helper.h"
#include "../ticket/ticket.h"

using namespace std;

namespace transport
{

    TrainSchedule allTrainSchedules[MAX_SCHEDULE_CACHE];
    BusSchedule allBusSchedules[MAX_SCHEDULE_CACHE];
    TicketPrice allTicketPrices[MAX_SCHEDULE_CACHE];

    int totalTrainSchedules = 0;
    int totalBusSchedules = 0;
    int totalTicketPrices = 0;

    bool loadTransportData()
    {
        ifstream fileBus(DB_BUS);
        ifstream fileKereta(DB_KERETA);
        ifstream filePrice(DB_TICKET_PRICE);

        string line;

        int count = 0;

        if (!fileBus.is_open() || !fileKereta.is_open())
        {
            return false;
        }

        while (getline(fileBus, line) && count < MAX_SCHEDULE_CACHE)
        {
            allBusSchedules[count].id_jadwal = helper::getCSVColumn(line, 0);
            allBusSchedules[count].kode_rute = stoi(helper::getCSVColumn(line, 1));
            allBusSchedules[count].nama_bus = helper::getCSVColumn(line, 2);
            allBusSchedules[count].terminal_asal = helper::getCSVColumn(line, 3);
            allBusSchedules[count].terminal_tujuan = helper::getCSVColumn(line, 4);
            allBusSchedules[count].jam_berangkat = helper::getCSVColumn(line, 5);
            allBusSchedules[count].estimasi_tiba = helper::getCSVColumn(line, 6);

            count++;
        }

        totalBusSchedules = count;

        fileBus.close();

        count = 0;
        while (getline(fileKereta, line) && count < MAX_SCHEDULE_CACHE)
        {
            allTrainSchedules[count].id_jadwal = helper::getCSVColumn(line, 0);
            allTrainSchedules[count].kode_rute = stoi(helper::getCSVColumn(line, 1));
            allTrainSchedules[count].nama_kereta = helper::getCSVColumn(line, 2);
            allTrainSchedules[count].stasiun_asal = helper::getCSVColumn(line, 3);
            allTrainSchedules[count].stasiun_tujuan = helper::getCSVColumn(line, 4);
            allTrainSchedules[count].via = helper::getCSVColumn(line, 5);
            allTrainSchedules[count].jam_berangkat = helper::getCSVColumn(line, 6);
            allTrainSchedules[count].jam_tiba = helper::getCSVColumn(line, 7);

            count++;
        }

        totalTrainSchedules = count;

        fileKereta.close();

        count = 0;
        while (getline(filePrice, line) && count < MAX_SCHEDULE_CACHE)
        {
            allTicketPrices[count].id_harga = helper::getCSVColumn(line, 0);
            allTicketPrices[count].tipe_kendaraan = helper::getCSVColumn(line, 1);
            allTicketPrices[count].kode_kelas = stoi(helper::getCSVColumn(line, 2));
            allTicketPrices[count].nama_kelas = helper::getCSVColumn(line, 3);
            allTicketPrices[count].harga_rupiah = stoll(helper::getCSVColumn(line, 4));

            count++;
        }

        totalTicketPrices = count;

        filePrice.close();

        return true;
    }

    bool appendTrainScheduleToCSV(TrainSchedule newTrainSchedule)
    {
        ofstream file(DB_KERETA, ios::app);

        if (file.is_open())
        {
            file << newTrainSchedule.id_jadwal << ","
                 << newTrainSchedule.kode_rute << ","
                 << newTrainSchedule.nama_kereta << ","
                 << newTrainSchedule.stasiun_asal << ","
                 << newTrainSchedule.stasiun_tujuan << ","
                 << newTrainSchedule.via << ","
                 << newTrainSchedule.jam_berangkat << ","
                 << newTrainSchedule.jam_tiba << endl;

            file.close();

            return true;
        }
        else
        {

            helper::messageBox("[ERROR] Gagal membuka file untuk menambahkan user baru.");

            return false;
        }
    }

    bool overwriteAllTrainScheduleToCSV()
    {
        ofstream file(DB_KERETA);

        if (!file.is_open())
        {
            return false;
        }

        for (int i = 0; i < transport::totalTrainSchedules; i++)
        {
            file << allTrainSchedules[i].id_jadwal << ","
                 << allTrainSchedules[i].kode_rute << ","
                 << allTrainSchedules[i].nama_kereta << ","
                 << allTrainSchedules[i].stasiun_asal << ","
                 << allTrainSchedules[i].stasiun_tujuan << ","
                 << allTrainSchedules[i].via << ","
                 << allTrainSchedules[i].jam_berangkat << ","
                 << allTrainSchedules[i].jam_tiba << endl;
        }

        file.close();

        return true;
    }

    bool appendBusScheduleToCSV(BusSchedule newBusSchedule)
    {
        ofstream file(DB_BUS, ios::app);

        if (file.is_open())
        {
            file << newBusSchedule.id_jadwal << ","
                 << newBusSchedule.kode_rute << ","
                 << newBusSchedule.nama_bus << ","
                 << newBusSchedule.terminal_asal << ","
                 << newBusSchedule.terminal_asal << ","
                 << newBusSchedule.jam_berangkat << ","
                 << newBusSchedule.estimasi_tiba << endl;

            file.close();

            return true;
        }
        else
        {

            helper::messageBox("[ERROR] Gagal membuka file untuk menambahkan user baru.");

            return false;
        }
    }

    bool overwriteAllBusScheduleToCSV()
    {
        ofstream file(DB_BUS);

        if (!file.is_open())
        {
            return false;
        }

        for (int i = 0; i < transport::totalBusSchedules; i++)
        {
            file << allBusSchedules[i].id_jadwal << ","
                 << allBusSchedules[i].kode_rute << ","
                 << allBusSchedules[i].nama_bus << ","
                 << allBusSchedules[i].terminal_asal << ","
                 << allBusSchedules[i].terminal_asal << ","
                 << allBusSchedules[i].jam_berangkat << ","
                 << allBusSchedules[i].estimasi_tiba << endl;
        }

        file.close();

        return true;
    }

}