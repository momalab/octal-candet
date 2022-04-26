#include <chrono>
#include <fstream>
#include <queue>
#include <thread>

#include "cloud_support.hpp"

using namespace std;

float cycleTime = 0.1; // seconds
bool isFileRead = false;
queue<Secure> dataBuffer;

void sleep(float stime)
{
    chrono::milliseconds utime( uint64_t(1000*stime) );
    this_thread::sleep_for(utime);
}

Secure wait_data()
{
    if ( !isFileRead )
    {
        ifstream fin("remote.data");
        string line;
        while ( getline(fin, line) ) dataBuffer.push(line);
        isFileRead = true;
    }
    if ( dataBuffer.empty() ) throw 0;
    sleep(cycleTime);
    auto r = dataBuffer.front();
    dataBuffer.pop();
    return r;
}
