#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "io.hpp"

using namespace std;

namespace io
{

vector<string> loadtxt(string filename)
{
    vector<string> v;
    ifstream fin(filename);
    string line;
    while ( getline(fin, line) ) v.push_back( trim(line) );
    return v;
}

vector<vector<string>> loadtxt(const string & filename, char delimiter)
{
    vector<vector<string>> m;
    ifstream fin(filename);
    string line;
    while ( getline(fin, line) )
    {
        auto items = split(line, delimiter);
        vector<string> v;
        for ( auto & item : items ) v.push_back( trim(item) );
        m.push_back(v);
    }
    return m;
}

vector<string> split(const string & s, char delimiter)
{
    vector<string> v;
    string item = "";
    for ( auto & c : s )
    {
        if ( c == delimiter )
        {
            v.push_back(item);
            item = "";
        }
        else item += c;
    }
    v.push_back(item);
    return v;
}

string trim(const string & sin)
{
    string s = sin;
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
        return !isspace(ch);
    }));
    s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), s.end());
    return s;
}

vector<string> trim(const vector<string> & v)
{
    vector<string> vout;
    for ( auto e : v ) vout.push_back(trim(e));
    return vout;
}

} // io
