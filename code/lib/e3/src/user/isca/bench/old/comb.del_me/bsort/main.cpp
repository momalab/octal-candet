#include <iostream>
#include <vector>

#include "e3int.h"
#include "timer.h"

#ifndef SZ
#define SZ 8
#endif

using namespace std;
using SecureInt  = TypeUint<SZ>;
using SecureBool = TypeBool;

template <class T>
void printArray(const vector<T> & arr)
{
    for ( size_t i = 0; i < arr.size(); i++ ) cout << arr[i] << " ";
    std::cout << std::endl;
}

void bubbleSort(vector<SecureInt> & arr)
{
    auto n = arr.size();
    SecureInt smaller;
    SecureBool cond;

    for ( size_t i = 0; i < n - 1; i++ )
    {
        for ( size_t j = 0; j < n - i - 1; j++ )
        {
            cond = arr[j] <= arr[j + 1];
            smaller = cond.mux(arr[j], arr[j + 1]);
            arr[j + 1] = cond.mux(arr[j + 1], arr[j]);
            arr[j] = smaller;
        }
    }
}

int main()
{
    vector<SecureInt> a = { _7_Ep, _12_Ep, _2_Ep, _0_Ep, _1_En, _15_Ep };
    Timer t;
    bubbleSort(a);
    auto r = t.get();
    // printArray(a);
    cout << "Runtime: " << r << " us\n";
}
