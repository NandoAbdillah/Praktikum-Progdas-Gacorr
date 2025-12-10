#ifndef TICKET_H
#define TICKET_H
#include <string>
#define DB_TICKET "./database/tickets.csv"
using namespace std;

namespace ticket
{

    struct Ticket
    {
        string id_tiket;  
        string id_user;        
        string tipe_kendaraan; 
        string asal;           
        string tujuan;         
        string kelas;          
        string tanggal;        
        string jam;             
        string kursi;      
        long harga;             
        string status;   
    };

    extern Ticket allTickets[100];
    extern Ticket authTickets[100];
    extern Ticket busTickets[100];
    extern Ticket trainTickets[100];
    extern int totalAuthTickets;
    extern int totalTickets;
    extern int totalBusTickets;
    extern int totalTrainTickets;

    bool loadTickets();
    bool loadAuthTickets();
    bool loadTrainTickets();
    bool loadBusTickets();
    bool appendTicketToCSV(Ticket newTicket);
    // bool overwriteAllTicketsToCSV();

}

#endif // !TICKET_H