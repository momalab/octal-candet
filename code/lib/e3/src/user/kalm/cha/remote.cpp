#include "e3int.h" // bob
#include "remote_support.hpp" // supporting functions
// to get random data, set 'isDataRandom = true' in 'remote_support.cpp'

using Secure = SecureInt<8>;

float cycleTime = 0.1; // seconds
uint64_t shift = 10; // bits -- to emulate fixed-point arithmetic on integers
uint64_t scale = 1 << shift;

int main()
{
    while (true)
    {
        float data = read_sensor();
        int64_t intData = data * scale;
        Secure encData(intData); // encrypt -- constructor calls Secure::encrypt(int64_t)
        send_data(encData); // to bob
        sleep(cycleTime);
    }
}
