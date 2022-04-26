#include <iostream>
#include <vector>

#include "e3int.h"
#include "timer.h"

#include "e3key.h"
template<class T> inline std::string de(T x) { return e3::decrypt<T>(x); }

#ifndef SZ
#define SZ 8
#endif
#define MAX_ITER 10
#define N_ELEMENTS 12

using namespace std;
using SecureInt  = TypeUint<SZ>;
using SecureBool = TypeBool;

template <class T>
T pir(const T & key, const vector<vector<T>> & table, const T & zero)
{
    T res = zero;
    for ( size_t i=0 ; i < table.size(); i++ )
    {
        res += (key == table[i][0]) * table[i][1];
    }
    return res;
}

template <class T>
void tmain(string name, const T & zero, const T & one)
{
    T key = _7_Ep;
    vector<vector<T>> table(N_ELEMENTS);
    for (size_t i=0; i<table.size(); i++)
    {
        auto c = T(i);
        table[i].push_back(c);
        table[i].push_back(c);
    }
    Timer t;
    auto f = pir<T>(key, table, zero);
    auto r = t.get();
    // cout << "PIR: " << de(key) << " -> " << de(f) << '\n';
    cout << name << " Runtime: " << r << " us\n";
}

int main()
{
    tmain<SecureInt> ( "SecureInt", _0_Ep, _1_Ep);
}
