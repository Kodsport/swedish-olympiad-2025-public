#include <string>
using namespace std;

#include "karleksbrev.h"

string encode(string S)
{
    string E = "";
    for (char c : S)
    {
        E += c;
        E += c;
        E += c;
        E += c;
        E += c;
    }
    return E;
}

// Note: this is E after it has been corrupted
string decode(string E)
{
    string ret = "";
    while (E.size())
    {
        string chunk = E.substr(0, 5);
        E = E.substr(5);
        ret += chunk[2];
    }
    return ret;
}
