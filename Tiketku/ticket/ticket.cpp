
#include <iostream>
#include <fstream>
#include "./ticket.h"
#include "../utils/helper.h"
#include "../user/user.h"

namespace ticket
{
    Ticket allTickets[100];
    Ticket authTickets[100];
    Ticket trainTickets[100];
    Ticket busTickets[100];

    int totalTickets = 0;
    int totalAuthTickets = 0;
    int totalTrainTickets = 0;
    int totalBusTickets = 0;

    bool appendTicketToCSV(ticket::Ticket newTicket)
    {
        ofstream file(DB_TICKET, ios::app);

        if (file.is_open())
        {
            file << newTicket.id_tiket << ","
                 << newTicket.id_user << ","
                 << newTicket.tipe_kendaraan << ","
                 << newTicket.asal << ","
                 << newTicket.tujuan << ","
                 << newTicket.kelas << ","
                 << newTicket.tanggal << ","
                 << newTicket.jam << ","
                 << newTicket.kursi << ","
                 << newTicket.harga << ","
                 << newTicket.status << endl;

            file.close();

            return true;
        }
        else
        {
            helper::messageBox("[ERROR] Gagal membuka file untuk menambahkan user baru.");

            return false;
        }
    }

    bool loadTickets()
    {
        ifstream file(DB_TICKET);
        string line;

        int count = 0;

        if (!file.is_open())
        {
            return false;
        }

        while (getline(file, line) && count < 100)
        {
            allTickets[count].id_tiket = helper::getCSVColumn(line, 0);
            allTickets[count].id_user = helper::getCSVColumn(line, 1);
            allTickets[count].tipe_kendaraan = helper::getCSVColumn(line, 2);
            allTickets[count].asal = helper::getCSVColumn(line, 3);
            allTickets[count].tujuan = helper::getCSVColumn(line, 4);
            allTickets[count].kelas = helper::getCSVColumn(line, 5);
            allTickets[count].tanggal = helper::getCSVColumn(line, 6);
            allTickets[count].jam = helper::getCSVColumn(line, 7);
            allTickets[count].kursi = helper::getCSVColumn(line, 8);
            allTickets[count].harga = stoll(helper::getCSVColumn(line, 9));
            allTickets[count].status = helper::getCSVColumn(line, 10);

            count++;
        }

        totalTickets = count;

        file.close();
        loadTrainTickets();
        loadBusTickets();

        return true;
    }

    bool loadTrainTickets()
    {
        int count = 0;
        for (int i = 0; i < totalTickets; i++)
        {
            if (allTickets[i].tipe_kendaraan == "Kereta Api")
            {
                trainTickets[i] = allTickets[i];
                count++;
            }
        }

        totalTrainTickets = count;

        return true;
    }

    bool loadBusTickets()
    {
        int count = 0;
        for (int i = 0; i < totalTickets; i++)
        {
            if (allTickets[i].tipe_kendaraan == "Bus")
            {
                busTickets[i] = allTickets[i];
                count++;
            }
        }

        totalBusTickets = count;

        return true;
    }

    bool loadAuthTickets()
    {
        int count = 0;
        for (int i = 0; i < totalTickets; i++)
        {
            if (allTickets[i].id_user == user::authUser.id)
            {
                authTickets[i] = allTickets[i];
                count++;
            }
        }

        totalAuthTickets = count;

        return true;
    }
}