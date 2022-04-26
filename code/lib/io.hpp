#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::getline;
using std::ifstream;
using std::stod;
using std::string;
using std::vector;

namespace io
{

std::vector<std::string> split(const std::string & s, char delimiter);
std::string trim(const std::string & sin);
std::vector<std::string> trim(const std::vector<std::string> & v);
std::vector<std::string> loadtxt(std::string filename);
std::vector<std::vector<std::string>> loadtxt(const std::string & filename, char delimiter);

template <class T> vector<T>
load(const string & filename)
{
    vector<T> v;
    ifstream fin(filename);
    string line;
    while ( getline(fin, line) ) v.push_back( stod(line) );
    return v;
}

template <class T> vector<vector<T>>
load(const string & filename, char delimiter)
{
    vector<vector<T>> m;
    ifstream fin(filename);
    string line;
    while ( getline(fin, line) )
    {
        auto items = split(line, delimiter);
        vector<T> v;
        for ( auto & item : items )
            v.push_back( stod(trim(item)) );
        m.push_back(v);
    }
    return m;
}

} // io
