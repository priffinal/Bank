#define _CRT_SECURE_NO_WARNINGS
#include "PrintTime.h"
#include <iomanip>
#include <iostream>
using namespace std;

ostream& operator<<(ostream &os, const tm ltm) 
{
    os << setfill('0')
    << right
    << setw(2) << ltm.tm_hour<< ":" 
    << setw(2) << ltm.tm_min << ":" 
    << setw(2) << ltm.tm_sec << " " 
    << setw(2) << ltm.tm_mday << "/"
    << setw(2) << ltm.tm_mon + 1 << "/"
    << ltm.tm_year + 1900
    << setfill(' ');
    return os;
}

string tmToString(const tm& t) {
    ostringstream oss;
    oss << put_time(&t, "%d/%m/%Y %H:%M:%S");
    return oss.str();
}

tm stringToTm(const string& s) {
    tm t{};
    istringstream iss(s);
    iss >> get_time(&t, "%d/%m/%Y %H:%M:%S");
    mktime(&t);
    return t;
}