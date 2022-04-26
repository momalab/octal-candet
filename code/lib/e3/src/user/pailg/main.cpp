#include <iostream>
#include <string>
#include <vector>

#include "e3int.h"
#include "e3key.h"

using namespace std;

using Pail = PailmUint	;

template <class T>
void test2x2(T op, int mul, int inc)
{
    //cout<<"Processor: "<<Pail::showProcessor()<<'\n';

    const int SZ = 20;
    const int CL = 4;

    auto c = [CL](string s) -> string
    {
        while (s.size() < CL) s = " " + s;
        return s;
    };

    cout << c("") << ' ';
    for ( int i = 0; i <= SZ; i++ ) cout << c(std::to_string(i));
    cout << "\n ";
    for ( int i = -1; i <= SZ; i++ ) cout << c("-");
    cout << '\n';

    Pail x = _0_En;
    for ( int i = 0; i <= mul * SZ; i += inc, x += inc )
    {
        Pail y = _0_En;
        cout << c(std::to_string(i)) << ':';
        for ( int j = 0; j <= SZ; j++, ++y )
        {
            auto z = op(x, y);
            string s = e3::decrypt(z);
            while (s.size() < CL) s = " " + s;
            cout << s;
        }
        cout << '\n';
    }
}


int main(int ac, char * av[])
try
{
    Pail x = _2_En, y = _3_En;
    for ( int i = 0; i < 23; i++ )
        cout << e3::decrypt(++x) << ' ';

    cout << '\n';

    cout << e3::decrypt(x) << " + " << e3::decrypt(y) << " = " << e3::decrypt(x + y) << '\n';
    cout << e3::decrypt(x) << " - " << e3::decrypt(y) << " = " << e3::decrypt(x - y) << '\n';
    cout << e3::decrypt(x) << " + (" << 7 << ") = " << e3::decrypt(x + 7) << '\n';

    auto aG = [](Pail x, Pail y) -> Pail { return x.G(y); };
    auto aM = [](Pail x, Pail y) -> Pail { return x * y; };

    //test2x2(aG, 20, 16);
    //test2x2(aM, 2, 1);

    cout << "beta = " << Pail::beta() << '\n';
    //cout << e3::decrypt(x) << " * " << e3::decrypt(y) << " = " << e3::decrypt(x * y) << '\n';
    //cout << "beta = " << Pail::beta(3) << '\n';
    cout << e3::decrypt(x) << " * " << e3::decrypt(y) << " = " << e3::decrypt(x * y) << '\n';

    //test2x2(aM, 1, 1);

}
catch (string e)
{
    cout << "Error: " << e << "\n";
}
catch (const char * e)
{
    cout << "Error: " << e << "\n";
}
catch (...)
{
    cout << "exception\n";
}
