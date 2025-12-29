#define _CRT_SECURE_NO_WARNINGS
#include "PrintTime.h"
#include <iomanip>
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