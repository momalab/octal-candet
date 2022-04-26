#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <typeinfo>

#include "e3int.h"

#include "e3key.h"
template<class T> inline std::string de(T x) { return e3::decrypt<T>(x); }

using namespace std;

string shrt(string s)
{
    if ( s.size() < 25 ) return s;
    return s.substr(0, 10) + "..." + s.substr(s.size() - 10);
}

template <class T>
void general()
{
    //- 1 None   ::  Scope resolution operator
    //-  ::  (unary)
    //-      (binary)
    //- 2 L->R   ()  Parentheses
    //-  ()  Function call

    //-  ()  Initialization
    T x(11);

    //-  {}  Uniform initialization (C++11)
    T y {1};

    //-  type()  Functional cast
    x = T(1);

    //-  type{}  Functional cast (C++11)
    y = T {1};

    //-  []  Array subscript
    //-  .   Member access from the object
    //-  ->  Member access from object ptr
    //-  ++  Post-increment
    x++;
    //-  ––  Post-decrement
    y--;

    //-  typeid  Run-time type information
    auto name = typeid(x).name();
    cout << "typeid: " << name << '\n';

    //-  const_cast  Cast away const
    //-  dynamic_cast    Run-time type-checked cast
    //-  reinterpret_cast    Cast one type to anotherCompile-time type-checked cast
    //-  static_cast
    {
        const T * z = &x;
        x = *const_cast<T *>(z);
        static_cast<T>(x);
        reinterpret_cast<T *>(&x);
    }

    //- 3 R->L   +   Unary plus
    //-  -   Unary minus
    x = +x;
    x = - -x;

    //-  ++  Pre-increment
    //-  ––  Pre-decrement
    ++x;
    --x;

    //-  !   Logical NOT
    //-  ~   Bitwise NOT

    //-  (type)  C-style cast
    { auto z = (T)x; }
    //-  sizeof  Size in bytes
    cout << "sizeof: " << sizeof(x) << '\n';

    //-  &   Address of
    //-  *   Dereference
    //-  new Dynamic memory allocation
    //-  new[]   Dynamic array allocation 
    //-  delete  Dynamic memory deletion
    //-  delete[]    Dynamic array deletion
    //- 4 L->R   ->* Member pointer selector
    //-  .*  Member object selector

    //- 5 L->R   *   Multiplication
    { auto z = x * y; }

    //-  /   Division
    //-  %   Modulus

    //- 6 L->R   +   Addition
    { auto z = x + y; }
    //-  -   Subtraction
    { auto z = x - y; }

    //- 7 L->R   <<  Bitwise shift left
    //-  >>  Bitwise shift right

    //- 7 L->R   <<  Bitwise shift left by int
    { auto z = x << 1; }

    //- 8 L->R   <   Comparison less than
    //-  <=  Comparison less than or equals
    //-  >   Comparison greater than
    //-  >=  Comparison greater than or equals
    //- 9 L->R  Equality/Inequality

    //- 10 L->R  &   Bitwise AND
    //- 11 L->R  ^   Bitwise XOR
    //- 12 L->R  |   Bitwise OR

    //- 13 L->R  &&  Logical AND
    //- 14 L->R  ||  Logical OR

    //- 15 R->L  ?:  Conditional
    //{ auto z = x.mux(x,y); }

    //-  =   Assignment
    y = x;

    //-  *=  Multiplication assignment
    //-  /=  Division assignment
    //-  %=  Modulus assignment
    //-  +=  Addition assignment
    //-  -=  Subtraction assignment
    y *= x;
    y += x;
    y -= x;

    //-  <<= Bitwise shift left assignment
    //-  >>= Bitwise shift right assignment
    y <<= 1;

    //-  &=  Bitwise AND assignment
    //-  |=  Bitwise OR assignment
    //-  ^=  Bitwise XOR assignment

    //- 16 R->L  throw   Throw expression
    if (0) throw x;

    //- 17 L->R  "," Comma operator
    x = (y, x);

    cout << "done for [" << name << "]\n";
}


template <class T>
void special()
{
    cout << "Names (typ,fil,cls) : " << T::typname() << ' ' << T::filname() << ' ' << T::clsname() << '\n';
    cout << "Traits (sign,size,circ) : " << T::is_signed << ' ' << T::size << ' ' << T::is_circuit << '\n';
    T x;
    x = 1ull * x;

    cout << "String: " << shrt(x.str()) << '\n';

    cout << "Names (typ,fil,cls) : " << x.typname() << ' ' << x.filname() << ' ' << x.clsname() << '\n';
    cout << "String: " << shrt(x.str()) << '\n';

    //- 15 R->L  ?:  Conditional

    general<T>();
}

int main(int ac, char * av[])
try
{
    general<int>();
    special<Secure>();
}
catch (const char * e)
{
    cout << "Error: " << e << "\n";
}
catch (string e)
{
    cout << "Error: " << e << "\n";
}
catch (...)
{
    cout << "exception\n";
}


