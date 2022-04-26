#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>

#include "remote_support.hpp"

using namespace std;

bool isDataRandom = false; // for debug
bool isRandomInit = false;
const uint64_t minValue = 1;
const uint64_t maxValue = 99;
const uint64_t noise = 1;
const float multiplier = 1.0; //100.0;

float read_sensor()
{
    if ( !isRandomInit )
    {
        if ( isDataRandom ) srand( time(NULL) );
        isRandomInit = true;
    }
    auto top = maxValue + noise;
    auto bottom = minValue - noise;
    auto interval = top - bottom + 1;
    auto r = bottom + ( rand() % interval );
    return multiplier * r / top; // (min-noise, max+noise)
}

void sleep(float stime)
{
    chrono::milliseconds utime( uint64_t(1000*stime) );
    this_thread::sleep_for(utime);
}
