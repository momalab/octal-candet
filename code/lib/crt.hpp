#pragma once

#include <vector>

namespace crt
{

// Class

template <class T, class U>
class CRT
{
    private:
        std::vector<T> v;
        static std::vector<T> vt;
        static std::vector<T> n; // n = mod / t
        static std::vector<T> x; // inv n
        static T mod;

    public:
        CRT(){} // check this
        CRT(const U &);
        CRT(const std::vector<T> &);

        T decode() const;
        static T decode(const CRT &);
        static CRT encode(const U &);
        std::vector<T> get();
        static void setCoprimes(const std::vector<T> &);
        static size_t size();
};

// Static variables

template <class T, class U> std::vector<T> CRT<T,U>::vt;
template <class T, class U> std::vector<T> CRT<T,U>::n;
template <class T, class U> std::vector<T> CRT<T,U>::x;
template <class T, class U> T CRT<T,U>::mod;

// Implementations

template <class T, class U>
CRT<T,U>::CRT(const U & a)
{
    *this = encode(a);
}

template <class T, class U>
CRT<T,U>::CRT(const std::vector<T> & a)
{
    v.assign( a.begin(), a.end() );
}

template <class T, class U>
T CRT<T,U>::decode() const
{
    T r = 0;
    for ( size_t i=0; i < v.size(); i++ )
        r += v[i] * n[i] * x[i];
    r %= mod;
    return U(r);
}

template <class T, class U>
T CRT<T,U>::decode(const CRT<T,U> & a)
{
    return a.decode();
}

template <class T, class U>
CRT<T,U> CRT<T,U>::encode(const U & a)
{
    auto b = a % U(mod);
    if ( b<0 ) b = U(mod) + b;
    std::vector<T> v;
    for ( auto t : vt ) v.push_back( T(b % t) );
    return CRT<T,U>(v);
}

template <class T, class U>
std::vector<T> CRT<T,U>::get()
{
    return v;
}

template <class T, class U>
void CRT<T,U>::setCoprimes(const std::vector<T> & coprimes)
{
    vt.clear();
    vt.assign( coprimes.begin(), coprimes.end() );
    mod = 1;
    for ( auto & t : vt ) mod *= t;

    n.clear();
    x.clear();
    for ( auto t : vt )
    {
        auto ni = mod / t;
        T xi = 0;
        while ( xi * ni % t != 1 ) xi++;
        n.push_back(ni);
        x.push_back(xi);
    }
}

template <class T, class U>
size_t CRT<T,U>::size()
{
    return vt.size();
}

} // CRT
