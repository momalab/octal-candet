#include <iostream>
#include <string>
#include <vector>

#include "e3int.h"
#include "e3key.h"

using namespace std;

int main(int ac, char * av[])
try
{
    Pailm x = _2_En, y = _3_En;
    for ( int i = 0; i < 23; i++ )
        cout << dec(++x) << ' ';

    cout << '\n';

    cout << dec(x) << " + " << dec(y) << " = " << dec(x + y) << '\n';
    cout << dec(x) << " - " << dec(y) << " = " << dec(x - y) << '\n';
    cout << dec(x) << " + (" << 7 << ") = " << dec(x + 7) << '\n';
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
