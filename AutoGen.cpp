#include "AutoGen.h"
#include <sstream>
#include <iomanip>
using namespace std;

string autoGenerate(string type, int n)
{
    stringstream s;
    s << type << setw(4) << setfill('0') << n;
    return s.str();
}