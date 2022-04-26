#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "e3int.h"



#include "e3key.h"
template<class T> inline std::string de(T x) { return e3::decrypt<T>(x); }

using namespace std;


int main(int ac, char * av[])
try
{

    PilcUint<8> y(_13_Eu);
    std::cout << "AAA 1\n" ;
    std::cout << "PilcUint8 = " << y << '\n' ;
    std::cout << "PilcUint8 = " << de(y) << '\n' ;
    std::cout << "AAA 2\n" ;

}
catch (string e)
{
    cout << "Error: " << e << "\n";
}
catch (...)
{
    cout << "exception\n";
}
