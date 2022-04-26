#include <iostream>

#include "e3int.h"
#include "e3key.h"
using Secure = SecureUint<4>;

using namespace std;

void swap(Secure & x, Secure & y, SecureBool cond)
{
    auto t = x ;
    x = cond * y + !cond * x;
    y = cond * t + !cond * y;
}

void bubbleSort(Secure arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            swap(arr[j], arr[j + 1], arr[j + 1] < arr[j] );
}

void printArray(Secure arr[], int size)
{
    for (int i = 0; i < size; i++) cout << ' ' << e3::decrypt(arr[i]);
    cout << '\n';
}

int main()
{
    Secure arr[] = {_6_e, _3_e, _5_e, _12_e, _2_e, _9_e, _1_e};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array :"; printArray(arr, n);
    bubbleSort(arr, n);
    cout << "Sorted  array  :"; printArray(arr, n);
}
