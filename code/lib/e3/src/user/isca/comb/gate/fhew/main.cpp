#include <iostream>
#include <string>
#include <vector>

#include "e3int.h"
#include "timer.hpp"

using namespace std;

enum class Gate { NOT = 0, AND, OR, XOR, NAND, NOR, XNOR, MUX };
Gate gates[] = { Gate::NOT, Gate::AND, Gate::OR, Gate::XOR, Gate::NAND, Gate::NOR, Gate::XNOR, Gate::MUX };
string names[] = { "NOT...", "AND...", "OR....", "XOR...", "NAND..", "NOR...", "XNOR..", "MUX..." };
const unsigned us = 1000000;

template<class Bit> inline void cycle_not (Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    // Bit t = a0;
    auto _a0 = Bit::gate_not(b1);
    auto _b1 = Bit::gate_not(b0);
    auto _b0 = Bit::gate_not(a1);
    auto _a1 = Bit::gate_not(a0);
}
template<class Bit> inline void cycle_and (Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    auto _a1 = Bit::gate_and(a1, b1);
    auto _b1 = Bit::gate_and(b1, a1);
    auto _a0 = Bit::gate_and(b0, a1);
    auto _b0 = Bit::gate_and(a0, b0);
}
template<class Bit> inline void cycle_or  (Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    auto _a0 = Bit::gate_or(a0, b0);
    auto _b0 = Bit::gate_or(b0, a0);
    auto _a1 = Bit::gate_or(b1, a0);
    auto _b1 = Bit::gate_or(a1, b1);
}
template<class Bit> inline void cycle_xor (Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    cout << "AAA 1\n";
    auto _a0 = Bit::gate_xor(a0, b0);
    cout << "AAA 2\n";
    auto _b0 = Bit::gate_xor(b1, a1);
    cout << "AAA 3\n";
    auto _a1 = Bit::gate_xor(a0, b1);
    cout << "AAA 4\n";
    auto _b1 = Bit::gate_xor(a1, b0);
    cout << "AAA 5\n";
}
template<class Bit> inline void cycle_nand(Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    auto _a0 = Bit::gate_nand(a1, b1);
    auto _a1 = Bit::gate_nand(a0, b1); // (b0, a0);
    auto _b1 = Bit::gate_nand(b0, a1);
    auto _b0 = Bit::gate_nand(b1, a1);
}
template<class Bit> inline void cycle_nor (Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    auto _a1 = Bit::gate_nor(a0, b0);
    auto _a0 = Bit::gate_nor(b0, a1);
    auto _b0 = Bit::gate_nor(a1, a0); // was a1 b1
    auto _b1 = Bit::gate_nor(a0, b0);
}
template<class Bit> inline void cycle_xnor(Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    auto _a0 = Bit::gate_xnor(b0, b1);
    auto _b0 = Bit::gate_xnor(b1, a0);
    auto _a1 = Bit::gate_xnor(a0, b0);
    auto _b1 = Bit::gate_xnor(a1, b1);
}
template<class Bit> inline void cycle_mux (Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    auto _a0 = Bit::gate_mux(a0, b1, b0);
    auto _a1 = Bit::gate_mux(b1, a1, a0);
    auto _b0 = Bit::gate_mux(a1, a0, b1);
    auto _b1 = Bit::gate_mux(b0, a0, a1);
}

template<class Bit>
double test(Gate g, const Bit & zero, const Bit & one, const Bit & zero2, const Bit & one2, unsigned time)
{
    Bit a0, a1, b0, b1;
    a0 = zero;
    b0 = zero2;
    a1 = one;
    b1 = one2;
    unsigned long long elapsed;
    unsigned cycleSize = 4, counter = 0;
    Timer t;
    while ( (elapsed = t.get()) < time )
    {
        switch (g)
        {
            case Gate::NOT : cycle_not (a0, a1, b0, b1); break;
            case Gate::AND : cycle_and (a0, a1, b0, b1); break;
            case Gate::OR  : cycle_or  (a0, a1, b0, b1); break;
            case Gate::XOR : cycle_xor (a0, a1, b0, b1); break;
            case Gate::NAND: cycle_nand(a0, a1, b0, b1); break;
            case Gate::NOR : cycle_nor (a0, a1, b0, b1); break;
            case Gate::XNOR: cycle_xnor(a0, a1, b0, b1); break;
            case Gate::MUX : cycle_mux (a0, a1, b0, b1);
        }
        counter++;
    }
    return double(elapsed) / counter / cycleSize;
}

template<class U, class B>
void validateGates(U zero, U unit)
{
    const bool PR = false;

    U s0 = zero, s1 = unit, s, pass, passt;
    vector<B> b = { s0[0], s1[0] }, bo;
    passt = s1;

    cout << zero << ' ' << unit << " NOT";
    pass = s1;
    for ( size_t i = 0; i < b.size(); i++ )
    {
        s[0] = B::gate_not(b[i]);
        if (PR) cout << " - ~" << i << " = " << s << ' ' << flush;

        s[0] = i ? B::gate_not(s[0]) : s[0];
        pass[0] = B::gate_and(pass[0], s[0]);
    }
    cout << ": " << pass << ' ' << std::flush;
    passt[0] = B::gate_and(passt[0], pass[0]);

    cout << "AND";
    pass = s1;
    for ( size_t i = 0; i < b.size(); i++ )
    {
        for ( size_t j = 0; j < b.size(); j++ )
        {
            s[0] = B::gate_and(b[i], b[j]);
            if (PR) cout << " - " << i << '&' << j << " = " << s << ' ' << flush;

            s[0] = i & j ? s[0] : B::gate_not(s[0]);
            pass[0] = B::gate_and(pass[0], s[0]);
        }
    }
    cout << ": " << pass << ' ' << std::flush;
    passt[0] = B::gate_and(passt[0], pass[0]);

    cout << "OR";
    pass = s1;
    for ( size_t i = 0; i < b.size(); i++ )
    {
        for ( size_t j = 0; j < b.size(); j++ )
        {
            s[0] = B::gate_or(b[i], b[j]);
            if (PR) cout << " - " << i << '|' << j << " = " << s << ' ' << flush;

            s[0] = i | j ? s[0] : B::gate_not(s[0]);
            pass[0] = B::gate_and(pass[0], s[0]);
        }
    }
    cout << ": " << pass << ' ' << std::flush;
    passt[0] = B::gate_and(passt[0], pass[0]);

    cout << "XOR";
    pass = s1;
    for ( size_t i = 0; i < b.size(); i++ )
    {
        for ( size_t j = 0; j < b.size(); j++ )
        {
            s[0] = B::gate_xor(b[i], b[j]);
            if (PR) cout << " - " << i << '^' << j << " = " << s << ' ' << flush;

            s[0] = i ^ j ? s[0] : B::gate_not(s[0]);
            pass[0] = B::gate_and(pass[0], s[0]);
        }
    }
    cout << ": " << pass << ' ' << std::flush;
    passt[0] = B::gate_and(passt[0], pass[0]);

    cout << "NAND";
    pass = s1;
    for ( size_t i = 0; i < b.size(); i++ )
    {
        for ( size_t j = 0; j < b.size(); j++ )
        {
            s[0] = B::gate_nand(b[i], b[j]);
            if (PR) cout << " - " << i << "!&" << j << " = " << s << ' ' << flush;

            s[0] = i & j ? B::gate_not(s[0]) : s[0];
            pass[0] = B::gate_and(pass[0], s[0]);
        }
    }
    cout << ": " << pass << ' ' << std::flush;
    passt[0] = B::gate_and(passt[0], pass[0]);

    cout << "NOR";
    pass = s1;
    for ( size_t i = 0; i < b.size(); i++ )
    {
        for ( size_t j = 0; j < b.size(); j++ )
        {
            s[0] = B::gate_nor(b[i], b[j]);
            if (PR) cout << " - " << i << "!|" << j << " = " << s << ' ' << flush;

            s[0] = i | j ? B::gate_not(s[0]) : s[0];
            pass[0] = B::gate_and(pass[0], s[0]);
        }
    }
    cout << ": " << pass << ' ' << std::flush;
    passt[0] = B::gate_and(passt[0], pass[0]);

    cout << "XNOR";
    pass = s1;
    for ( size_t i = 0; i < b.size(); i++ )
    {
        for ( size_t j = 0; j < b.size(); j++ )
        {
            s[0] = B::gate_xnor(b[i], b[j]);
            if (PR) cout << " - " << i << "!^" << j << " = " << s << ' ' << flush;

            s[0] = i ^ j ? B::gate_not(s[0]) : s[0];
            pass[0] = B::gate_and(pass[0], s[0]);
        }
    }
    cout << ": " << pass << ' ' << std::flush;
    passt[0] = B::gate_and(passt[0], pass[0]);


    cout << "MUX";
    pass = s1;
    for ( size_t i = 0; i < b.size(); i++ )
    {
        for ( size_t j = 0; j < b.size(); j++ )
        {
            for ( size_t k = 0; k < b.size(); k++ )
            {
                s[0] = B::gate_mux(b[i], b[j], b[k]);
                if (PR) cout << " - " << i << '?' << j << ':' << k << " = " << s << ' ' << flush;

                s[0] = (i ? j : k) ? s[0] : B::gate_not(s[0]);
                pass[0] = B::gate_and(pass[0], s[0]);
            }
        }
    }
    cout << ": " << pass << ' ' << std::flush;
    passt[0] = B::gate_and(passt[0], pass[0]);

    cout << "ALL: " << passt << '\n';
}

int main(int ac, char * av[])
try
{
    double input_time = 0; // s
    if ( ac > 1 ) input_time = std::stod(av[1]); // s
    unsigned tim = us * input_time; // us

    if (tim)
    {
        cout << "\nFHEW\n";
        {
            FhewUint<2> t = _2_Fp, u = _1_Fp;
            for ( auto g : gates )
                cout << names[int(g)] << " " << test<FhewBit>( g, t[0], t[1], u[1], u[0], tim ) << '\n';
        }

        // cout << "\nHELI\n";
        // {
        //     HeliUint<2> t = _2_Hp;
        //     for ( auto g : gates )
        //         cout << names[int(g)] << " " << test<HeliBit>( g, t[0], t[1], tim ) << '\n';
        // }

        cout << "\nSEAL\n";
        {
            SealUint<2> t = _2_Sp, u = _2_Sp;
            for ( auto g : gates )
                cout << names[int(g)] << " " << test<SealBit>( g, t[0], t[1], u[1], u[0], tim ) << '\n';
        }

        cout << "\nTFHE\n";
        {
            TfheUint<2> t = _2_Tp, u = _2_Tp;
            for ( auto g : gates )
                cout << names[int(g)] << " " << test<TfheBit>( g, t[0], t[1], u[1], u[0], tim ) << '\n';
        }

        cout << "\n";
    }

    // cout << "FHEW... "; validateGates<FhewUint<1>, FhewBit>(_0_Fp, _1_Fp);
    // // cout << "HELI... "; validateGates<HeliUint<1>, HeliBit>(_0_Hp, _1_Hp);
    // cout << "SEAL... "; validateGates<SealUint<1>, SealBit>(_0_Sp, _1_Sp);
    // cout << "TFHE... "; validateGates<TfheUint<1>, TfheBit>(_0_Tp, _1_Tp);
}
catch (string e)
{
    cout << "Error: " << e << "\n";
}
catch (...)
{
    cout << "exception\n";
}
