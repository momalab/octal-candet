#pragma once

#include <fstream>

float read_sensor();

template <class T>
void send_data(T data)
{
    std::ofstream fout("remote.data", std::fstream::app);
    fout << data << "\n";
}

void sleep(float);
