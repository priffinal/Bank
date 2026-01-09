#pragma once
#include <string>
#include <ctime>
using namespace std;

ostream &operator<<(ostream &os, const tm ltm);
string tmToString(const tm& t);
tm stringToTm(const string& s);