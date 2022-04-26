#include <iostream>
#include <vector>

#include "e3int.h"
#include "timer.h"

#include "e3key.h"
template<class T> inline std::string de(T x) { return e3::decrypt<T>(x); }

#ifndef SZ
#define SZ 8
#endif
#define MAX_ITER 100

using namespace std;
using SecureInt  = TypeUint<SZ>;
using SecureBool = TypeBool;
using SecureMint = TypeMint;

template <class T>
T fib(const SecureInt & input, size_t niter, const T & one)
{
    T f1  = 0*one;
    T f2  = one;
    T fi  = one;
    SecureInt  i   = _1_Ep;
    T res = 0*one;
    for ( ; niter--; i++ )
    {
        res += (i == input) * fi;
        fi = f1 + f2;
        f1 = f2;
        f2 = fi;
    }
    return res;
}

template <class T>
void tmain(string name, const T & one)
{
    SecureInt input = _7_Ep;
    Timer t;
    auto f = fib<T>(input, MAX_ITER, one);
    auto r = t.get();
    cout << "Fibo: " << de(input) << " -> " << de(f) << '\n';
    cout << name << " Runtime: " << r << " us\n";
}

int main()
{
    tmain<SecureMint>("SecureMint", _1_Ea);
    tmain<SecureInt>("SecureInt", _1_Ep);
}
