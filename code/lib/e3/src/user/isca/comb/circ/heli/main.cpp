#include <iostream>
#include <string>
#include <vector>

#include "e3int.h"
#include "timer.hpp"

using namespace std;

enum class Operator { ADD = 0, MUL, DIV, SHL, EQ, LAND, BMUL, BMUX  };
Operator operators[] = { Operator::ADD, Operator::MUL, Operator::DIV, Operator::SHL, Operator::EQ, Operator::LAND, Operator::BMUL, Operator::BMUX };
string names[] = { "ADD...", "MUL...", "DIV....", "SHL...", "EQ..", "LAND...", "BMUL..", "BMUX..." };
const unsigned us = 1000000;

template<class Sec> inline void cycle_add (Sec & a, Sec & b)
{
    a += b;
}

template<class Sec> inline void cycle_mul (Sec & a, Sec & b)
{
    a *= b;
}

template<class Sec> inline void cycle_div (Sec & a, Sec & b)
{
    a /= b;
}

template<class Sec> inline void cycle_shl (Sec & a, Sec & b)
{
    a >>= b;
}

template<class Sec> inline void cycle_eq  (Sec & a, Sec & b)
{
    a[0] = (a == b)[0];
}

template<class Sec> inline void cycle_land(Sec & a, Sec & b)
{
    a[0] = (a && b)[0];
}

template<class Sec, class SecBool> inline void cycle_bmul(Sec & a, SecBool & b)
{
    a = a * b;
}

template<class Sec, class SecBool> inline void cycle_bmux(SecBool & d, Sec & b, Sec & c)
{
    b = d.mux(b,c);
}

template<class Sec, class SecBool>
void test(Operator g, const Sec & _a, const Sec & _b, const Sec & _c, const SecBool & _d )
{
    Sec a = _a, b = _b, c = _c;
    SecBool d = _d;
    // unsigned long long elapsed;
    unsigned cycles = 1, counter = 0;
    Timer t;
    while ( counter < cycles )
    {
        switch (g)
        {
            case Operator::ADD : cycle_add (a,b); break;
            case Operator::MUL : cycle_mul (a,b); break;
            case Operator::DIV : cycle_div (a,b); break;
            case Operator::SHL : cycle_shl (a,b); break;
            case Operator::EQ  : cycle_eq  (a,b); break;
            case Operator::LAND: cycle_land(a,b); break;
            case Operator::BMUL: cycle_bmul(a,d); break;
            case Operator::BMUX: cycle_bmux(d,b,c);
        }
        counter++;
        cout << "\t" << double(t.get()) / counter << flush;
    }
    cout << ";" << flush;
}

int main(int ac, char * av[])
try
{
    for ( auto op : operators )
    {
        cout << names[int(op)] << flush;
        test<SecureUint<8> , SecureBool>( op, _2_Ep, _1_Ep, _3_Ep, _1_Ep );
        // test<SecureUint<16>, SecureBool>( op, _2_Ep, _1_Ep, _3_Ep, _1_Ep, tim );
        // test<SecureUint<32>, SecureBool>( op, _2_Ep, _1_Ep, _3_Ep, _1_Ep, tim );
        cout << "\n";
    }
}
catch (string e)
{
    cout << "Error: " << e << "\n";
}
catch (...)
{
    cout << "exception\n";
}
