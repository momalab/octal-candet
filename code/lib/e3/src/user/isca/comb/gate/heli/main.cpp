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
    Bit t = a0;
    a0 = Bit::gate_not(b1);
    b1 = Bit::gate_not(b0);
    b0 = Bit::gate_not(a1);
    a1 = Bit::gate_not(t);
}
template<class Bit> inline void cycle_and (Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    a1 = Bit::gate_and(a1, b1);
    b1 = Bit::gate_and(b1, a1);
    a0 = Bit::gate_and(b0, a1);
    b0 = Bit::gate_and(a0, b0);
}
template<class Bit> inline void cycle_or  (Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    a0 = Bit::gate_or(a0, b0);
    b0 = Bit::gate_or(b0, a0);
    a1 = Bit::gate_or(b1, a0);
    b1 = Bit::gate_or(a1, b1);
}
template<class Bit> inline void cycle_xor (Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    a0 = Bit::gate_xor(a0, b0);
    b0 = Bit::gate_xor(b1, a1);
    a1 = Bit::gate_xor(a0, b1);
    b1 = Bit::gate_xor(a1, b0);
}
template<class Bit> inline void cycle_nand(Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    a0 = Bit::gate_nand(a1, b1);
    a1 = Bit::gate_nand(a0, b1); // (b0, a0);
    b1 = Bit::gate_nand(b0, a1);
    b0 = Bit::gate_nand(b1, a1);
}
template<class Bit> inline void cycle_nor (Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    a1 = Bit::gate_nor(a0, b0);
    a0 = Bit::gate_nor(b0, a1);
    b0 = Bit::gate_nor(a1, a0); // was a1 b1
    b1 = Bit::gate_nor(a0, b0);
}
template<class Bit> inline void cycle_xnor(Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    a0 = Bit::gate_xnor(b0, b1);
    b0 = Bit::gate_xnor(b1, a0);
    a1 = Bit::gate_xnor(a0, b0);
    b1 = Bit::gate_xnor(a1, b1);
}
template<class Bit> inline void cycle_mux (Bit & a0, Bit & a1, Bit & b0, Bit & b1)
{
    a0 = Bit::gate_mux(a0, b1, b0);
    a1 = Bit::gate_mux(b1, a1, a0);
    b0 = Bit::gate_mux(a1, a0, b1);
    b1 = Bit::gate_mux(b0, a0, a1);
}

template<class Bit>
void test(Gate g, const Bit & zero, const Bit & one )
{
    Bit a0, a1, b0, b1;
    a0 = b0 = zero;
    a1 = b1 = one;
    unsigned long long elapsed;
    unsigned cycles = 100, cycleSize = 4, counter = 0;
    Timer t;
    while ( counter < cycles )
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
        counter += cycleSize;
        cout << "\t" << double(t.get()) / counter << flush;
    }
}

int main()
try
{
    cout << "\nHELI\n";
    {
        HeliUint<2> t = _2_Hp;
        for ( auto g : gates )
        {
            cout << names[int(g)] << " " << flush;
            test<HeliBit>( g, t[0], t[1] );
            cout << '\n';
        }
    }
    cout << "\n";
}
catch (string e)
{
    cout << "Error: " << e << "\n";
}
catch (...)
{
    cout << "exception\n";
}
