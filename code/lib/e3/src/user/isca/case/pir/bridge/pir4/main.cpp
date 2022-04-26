#include <iostream>
#include <vector>

#include "e3int.h"
#include "timer.h"

#include "e3key.h"
template<class T> inline std::string de(T x) { return e3::decrypt<T>(x); }

#ifndef SZ
#define SZ 4
#endif
#define MAX_ITER 10
#define N_ELEMENTS 12

using namespace std;
using SecureInt  = TypeUint<SZ>;
using SecureBool = TypeBool;
using SecureMint = TypeMint;

template <class T>
T pir(const SecureInt & key, const vector<SecureInt> & table_index, const vector<T> & table_value, const T & zero)
{
    T res = zero;
    for ( size_t i=0 ; i < table_index.size(); i++ )
    {
        res += (key == table_index[i]) * table_value[i];
    }
    return res;
}

template <class T>
void tmain(string name, const T & zero, const T & one)
{
    SecureInt key = _7_Ep;
    vector<SecureInt> table_index(N_ELEMENTS);
    vector<T> table_value(N_ELEMENTS);
    for (size_t i=0; i<table_index.size(); i++)
    {
        table_index[i] = SecureInt(i);
        table_value[i] = T(i);
    }
    Timer t;
    auto f = pir<T>(key, table_index, table_value, zero);
    auto r = t.get();
    // cout << "PIR: " << de(key) << " -> " << de(f) << '\n';
    cout << name << " Runtime: " << r << " us\n";
}

int main()
{
    tmain<SecureMint>("SecureMint", _0_Ea, _1_Ea);
}
