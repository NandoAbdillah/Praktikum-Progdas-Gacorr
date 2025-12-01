#ifndef HELPER_H
#define HELPER_H

#include <string>
using namespace std;

string simpleEncrypt(string rawPass);
string simpleDecrypt(string encPass);

string getCSVColumn(string line, int colIndex);

void generateUserID(int userCount, string* outID);



#endif // !HELPER_H