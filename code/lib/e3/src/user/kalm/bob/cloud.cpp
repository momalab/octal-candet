#include <fstream>
#include "cloud_support.hpp"

uint64_t shift = 10; // bits -- to emulate fixed-point arithmetic on integers
uint64_t scale = 1 << shift;

int main()
{
    auto errInit = Secure(_2_Ep) << shift;
    auto qInit = Secure(scale) / Secure(_100_Ep);
    KalmanFilter filter(errInit, errInit, qInit, shift);
    std::ofstream fout("cloud.data");
    try
    {
        while (true)
        {
            auto data = wait_data(); // encrypted data from remote entity
            auto currentEstimate = filter.update(data);
            fout << currentEstimate << "\n";
        }
    } catch (...) { }
}
