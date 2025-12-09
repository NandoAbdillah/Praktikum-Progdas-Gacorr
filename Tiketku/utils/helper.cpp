#include "helper.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

namespace helper
{
    string simpleEncrypt(string rawPass)
    {
        string result = "";
        for (int i = 0; i < rawPass.length(); i++)
        {
            char c = rawPass[i];
            c = c + 3;
            result += c;
        }
        return result;
    }

    string simpleDecrypt(string encPass)
    {
        string result = "";
        for (int i = 0; i < encPass.length(); i++)
        {
            char c = encPass[i];
            c = c - 3;
            result += c;
        }
        return result;
    }

    string getCSVColumn(string line, int colIndex)
    {
        string currentWord = "";
        int currentCol = 0;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ',')
            {
                if (currentCol == colIndex)
                {
                    return currentWord;
                }
                currentCol++;
                currentWord = "";
            }
            else
            {
                currentWord += line[i];
            }
        }

        if (currentCol == colIndex)
        {
            return currentWord;
        }

        return "";
    }

    bool saveCSVData(string filename, string *dataLines, int totalLines)
    {
        ofstream file(filename, ios::trunc);

        if (file.is_open())
        {
            for (int i = 0; i < totalLines; i++)
            {
                file << dataLines[i] << endl;
            }
            file.close();
            return true;
        }
        else
        {
            return false;
        }
    }

    void generateUserID(int totalData, string *outID)
    {

        string num = to_string(totalData + 1);
        *outID = "U" + num;
    }

    void generateIDJadwal(int totalData,  string *outID, string prefix) 
    {
        
        string padNum = totalData < 10 ? "00" : "0";
        string num = to_string(totalData);


        *outID = prefix + padNum +  num;
    }

    string messageBox(string message)
    {
        string border(message.length() + 4, '*');
        string box = border + "\n* " + message + " *\n" + border;
        return box;
    }

    string responseBox(bool status, string message)
    {
        string statusText = status ? "[SUKSES] " : "[GAGAL] ";
        return messageBox(statusText + message);
    }

    
    string getDate(int add_date)
    {
        time_t sekarang = time(0);
        time_t waktu_tujuan = sekarang + (add_date * 86400);
        tm *ltm = localtime(&waktu_tujuan);
        char buffer[80];
        strftime(buffer, 80, "%d/%m/%Y", ltm);
        return string(buffer);
    }

    string generateIDTiket()
    {
        time_t sekarang = time(0);
        tm *ltm = localtime(&sekarang);
        char buffer[80];
        strftime(buffer, 80, "TKT%Y%m%d%H%M%S", ltm);
        return string(buffer);
    }

    string padRight(string text, int width) {
    int len = text.length();
    while (len < width) {
        text += " ";
        len++;
    }
    return text;
}

}