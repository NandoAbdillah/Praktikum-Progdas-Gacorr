#ifndef HELPER_H
#define HELPER_H

#include <string>
using namespace std;

namespace helper
{
    string simpleEncrypt(string rawPass);
    string simpleDecrypt(std::string encPass);

    string getCSVColumn(std::string line, int colIndex);

    void generateUserID(int totalData, string *outID);

    string messageBox(string message);
    string responseBox(bool status, string message);

    string getDate(int add_date);
    string generateIDTiket();

    string padRight(string text, int width);

    void generateIDJadwal(int totalData,  string *outID, string prefix);
}

#endif // !HELPER_H