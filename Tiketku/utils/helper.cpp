#include "helper.h"
#include <iostream>
#include <string>

using namespace std;


string simpleEncrypt(string rawPass) {
    string result = "";
    for (int i = 0; i < rawPass.length(); i++) {
        char c = rawPass[i];
        c = c + 3; 
        result += c;
    }
    return result;
}

string simpleDecrypt(string encPass) {
    string result = "";
    for (int i = 0; i < encPass.length(); i++) {
        char c = encPass[i];
        c = c - 3;
        result += c;
    }
    return result; 
}

string getCSVColumn(string line, int colIndex) {
    string currentWord = "";
    int currentCol = 0;
    
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ',') {
            if (currentCol == colIndex) {
                return currentWord;
            }
            currentCol++;
            currentWord = "";
        } else {
            currentWord += line[i];
        }
    }
    
    if (currentCol == colIndex) {
        return currentWord;
    }
    
    return "";
}

void generateUserID(int userCount, string* outID) {
    
    string num = to_string(userCount + 1);
    *outID = "U" + num;
}