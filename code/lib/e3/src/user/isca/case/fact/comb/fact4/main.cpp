#include <iostream>
#include <vector>

#include "e3int.h"
#include "timer.h"

#include "e3key.h"
template<class T> inline std::string de(T x) { return e3::decrypt<T>(x); }

#ifndef SZ
//#define SZ 32
//#define SZ 16
#define SZ 4
#endif
#define MAX_ITER 10

using namespace std;
using SecureInt  = TypeUint<SZ>;
using SecureBool = TypeBool;

template <class T>
T fac(const T & input, size_t niter, const T & zero, const T & one)
{
    T fact = one;
    T i = one;
    T res = zero;

    for ( ; niter--; ++i)
    {
        fact *= i;
        res += (i == input) * fact;
    }

    return res;
}

template <class T>
void tmain(string name, const T & zero, const T & one)
{
    SecureInt input = _5_Ep;
    Timer t;
    auto f = fac<T>(input, MAX_ITER, zero, one);
    auto r = t.get();
    // cout << "factorial: " << de(input) << "! = " << de(f) << '\n';
    cout << name << " Runtime: " << r << " us\n";
}

int main()
try
{
    tmain<SecureInt> ( "SecureInt", _0_Ep, _1_Ep);
}
catch (string e)
{
    cout << "Oops: " << e << "\n";
    return 1;
}
catch (...)
{
    cout << "Oops ...\n";
    return 1;
}
