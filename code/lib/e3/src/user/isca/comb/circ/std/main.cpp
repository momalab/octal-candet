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
            case Operator::LAND: cycle_land(a,b); break;
            case Operator::BMUL: cycle_bmul(a,d); break;
            case Operator::BMUX: cycle_bmux(d,b,c);
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
        // cout << "\nHELI-a\n";
        // {
        //     for ( auto op : operators )
        //     {
        //         cout << names[int(op)] << flush;
        //         cout << "\t" << test<HeliUint<8> , HeliBool>( op, _2_Hp, _1_Hp, _3_Hp, _1_Hp, tim ) << flush;
        //         cout << "\t" << test<HeliUint<16>, HeliBool>( op, _2_Hp, _1_Hp, _3_Hp, _1_Hp, tim ) << flush;
        //         cout << "\t" << test<HeliUint<32>, HeliBool>( op, _2_Hp, _1_Hp, _3_Hp, _1_Hp, tim ) << flush;
        //         cout << "\n";
        //     }
        // }

        /*cout << "\nHELI-s\n";
        {
            for ( auto op : operators )
            {
                cout << names[int(op)] << flush;
                cout << "\t" << test<HelsUint<8> , HelsBool>( op, _2_Ip, _1_Ip, _3_Ip, _1_Ip, tim ) << flush;
                cout << "\t" << test<HelsUint<16>, HelsBool>( op, _2_Ip, _1_Ip, _3_Ip, _1_Ip, tim ) << flush;
                cout << "\t" << test<HelsUint<32>, HelsBool>( op, _2_Ip, _1_Ip, _3_Ip, _1_Ip, tim ) << flush;
                cout << "\n";
            }
        }*/

        cout << "\nSEAL-a\n";
        {
            for ( auto op : operators )
            {
                cout << names[int(op)] << flush;
                cout << "\t" << test<SealUint<8> , SealBool>( op, _2_Sp, _1_Sp, _3_Sp, _1_Sp, tim ) << flush;
                cout << "\t" << test<SealUint<16>, SealBool>( op, _2_Sp, _1_Sp, _3_Sp, _1_Sp, tim ) << flush;
                cout << "\t" << test<SealUint<32>, SealBool>( op, _2_Sp, _1_Sp, _3_Sp, _1_Sp, tim ) << flush;
                cout << "\n";
            }
        }

        cout << "\nSEAL-s\n";
        {
            for ( auto op : operators )
            {
                cout << names[int(op)] << flush;
                cout << "\t" << test<SeasUint<8> , SeasBool>( op, _2_Rp, _1_Rp, _3_Rp, _1_Rp, tim ) << flush;
                cout << "\t" << test<SeasUint<16>, SeasBool>( op, _2_Rp, _1_Rp, _3_Rp, _1_Rp, tim ) << flush;
                cout << "\t" << test<SeasUint<32>, SeasBool>( op, _2_Rp, _1_Rp, _3_Rp, _1_Rp, tim ) << flush;
                cout << "\n";
            }
        }

        cout << "\nTFHE\n";
        {
            for ( auto op : operators )
            {
                cout << names[int(op)] << flush;
                cout << "\t" << test<TfheUint<8> , TfheBool>( op, _2_Tp, _1_Tp, _3_Tp, _1_Tp, tim ) << flush;
                cout << "\t" << test<TfheUint<16>, TfheBool>( op, _2_Tp, _1_Tp, _3_Tp, _1_Tp, tim ) << flush;
                cout << "\t" << test<TfheUint<32>, TfheBool>( op, _2_Tp, _1_Tp, _3_Tp, _1_Tp, tim ) << flush;
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
