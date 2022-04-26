#include <iostream>
#include <string>
#include <vector>

#include "e3int.h"
#include "timer.hpp"

using namespace std;

// enum class Operator { ADD = 0, MUL, DIV, SHL, EQ, LAND, BMUL, BMUX  };
enum class Operator { ADD = 0, MUL, DIV, SHL, EQ, BMUL  };
Operator operators[] = { Operator::ADD, Operator::MUL, Operator::DIV, Operator::SHL, Operator::EQ, Operator::BMUL };
string names[] = { "ADD...", "MUL...", "DIV....", "SHL...", "EQ..", "BMUL.." };
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
double test(Operator g, const Sec & _a, const Sec & _b, const Sec & _c, const SecBool & _d, unsigned time)
{
    Sec a = _a, b = _b, c = _c;
    SecBool d = _d;
    unsigned long long elapsed;
    unsigned counter = 0;
    Timer t;
    while ( (elapsed = t.get()) < time )
    {
        switch (g)
        {
            case Operator::ADD : cycle_add (a,b); break;
            case Operator::MUL : cycle_mul (a,b); break;
            case Operator::DIV : cycle_div (a,b); break;
            case Operator::SHL : cycle_shl (a,b); break;
            case Operator::EQ  : cycle_eq  (a,b); break;
            // case Operator::LAND: cycle_land(a,b); break;
            case Operator::BMUL: cycle_bmul(a,d); break;
            // case Operator::BMUX: cycle_bmux(d,b,c);
        }
        counter++;
    }
    return double(elapsed) / counter;
}

int main(int ac, char * av[])
try
{
    double input_time = 0; // s
    if ( ac > 1 ) input_time = std::stod(av[1]); // s
    unsigned tim = us * input_time; // us

    if (tim)
    {
        {
            for ( auto op : operators )
            {
                cout << names[int(op)] << flush;
                cout << "\t" << test<SecureUint<2> , SecureBool>( op, _2_Ep, _1_Ep, _3_Ep, _1_Ep, tim ) << flush;
                cout << "\t" << test<SecureUint<4> , SecureBool>( op, _2_Ep, _1_Ep, _3_Ep, _1_Ep, tim ) << flush;
                cout << "\t" << test<SecureUint<8> , SecureBool>( op, _2_Ep, _1_Ep, _3_Ep, _1_Ep, tim ) << flush;
                // cout << "\t" << test<SecureUint<16>, SecureBool>( op, _2_Ep, _1_Ep, _3_Ep, _1_Ep, tim ) << flush;
                // cout << "\t" << test<SecureUint<32>, SecureBool>( op, _2_Ep, _1_Ep, _3_Ep, _1_Ep, tim ) << flush;
                cout << "\n";
            }
        }
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
