#include "AutoGen.h"
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

string autoGenerate(string type, int n)
{
    stringstream s;
    s << type << setw(4) << setfill('0') << n;
    return s.str();
}

void end()
{
    cout << "\nNhan phim Enter de quay lai...";
    cin.get();
}