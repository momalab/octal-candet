#pragma once

#include <atomic>
#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>
#include <variant>
#include <vector>

#include "e3int.h"
#include "e3key.h"
#include "numpy.hpp"
#include "plaintext.hpp"

namespace crt
{

template <class T>
class Ciphertext
{
    private:
        std::vector<T> vc; // std::vector<std::variant<...>>
        static std::vector<T> types;

    public:
        Ciphertext(){}
        Ciphertext(const std::vector<unsigned long long> & a) : Ciphertext( Plaintext(a) ){}
        Ciphertext(const std::vector<std::vector<unsigned long long>> &);
        Ciphertext(const Plaintext & a) : Ciphertext(a.vp){}
        Ciphertext(const Ciphertext &);
        Ciphertext(const std::vector<std::string> &);

        Ciphertext & operator += (const Ciphertext &);
        Ciphertext & operator += (const Plaintext &);
        Ciphertext & operator *= (const Plaintext &);
        Ciphertext & operator <<= (int);
        Ciphertext & operator >>= (int);
        Ciphertext operator + (const Ciphertext &) const;
        Ciphertext operator + (const Plaintext &) const;
        Ciphertext operator * (const Plaintext &) const;
        Ciphertext operator << (int) const;
        Ciphertext operator >> (int) const;

        std::vector<unsigned long long> decode() const;
        static std::vector<unsigned long long> decode(const Ciphertext &);
        Plaintext decrypt() const;
        static Plaintext decrypt(const Ciphertext &);
        static Ciphertext encrypt(const Plaintext &);
        static Ciphertext encrypt(const std::vector<std::vector<unsigned long long>> &);

        static void setTypes(const std::vector<T> &);
        std::vector<std::string> str() const;

        static size_t slots();

        template <class U>
        friend std::ostream & operator <<(std::ostream &, const Ciphertext<U> &);

        template <class U>
        friend std::vector<std::vector<U>> loadCiphertext(const std::string &, char);
};
template <class T> std::vector<T> Ciphertext<T>::types;

template <class T>
Ciphertext<T>::Ciphertext(const std::vector<std::vector<unsigned long long>> & vp)
{
    vc.clear();
    for ( size_t i=0; i < vp.size(); i++ )
    {
        switch (i)
        {
            case 0:
            {
                auto tmp = std::get<0>( types[i] );
                vc.push_back( decltype(tmp)(vp[i]) );
                break;
            }
            case 1:
            {
                auto tmp = std::get<1>( types[i] );
                vc.push_back( decltype(tmp)(vp[i]) );
                break;
            }
            default: throw "Unsuported number of coprimes";
        }
    }
}

template <class T>
Ciphertext<T>::Ciphertext(const std::vector<std::string> & a)
{
    vc.clear();
    for ( size_t i=0; i < a.size(); i++ )
    {
        switch (i)
        {
            case 0:
            {
                auto tmp = std::get<0>( types[i] );
                vc.push_back( decltype(tmp)(a[i]) );
                break;
            }
            case 1:
            {
                auto tmp = std::get<1>( types[i] );
                vc.push_back( decltype(tmp)(a[i]) );
                break;
            }
            default: throw "Unsuported number of coprimes";
        }
    }
}

template <class T>
Ciphertext<T>::Ciphertext(const Ciphertext<T> & a)
{
    vc.assign( a.vc.begin(), a.vc.end() );
}

template <class T>
Ciphertext<T> & Ciphertext<T>::operator += (const Ciphertext<T> & a)
{
    for ( size_t i=0; i < vc.size(); i++ )
    {
        switch (i)
        {
            case 0: vc[i] = std::get<0>(vc[i]) + std::get<0>(a.vc[i]); break;
            case 1: vc[i] = std::get<1>(vc[i]) + std::get<1>(a.vc[i]); break;
            default: throw "Unsuported number of coprimes";
        }
    }
    return *this;
}

template <class T>
Ciphertext<T> & Ciphertext<T>::operator += (const Plaintext & a)
{
    for ( size_t i=0; i < vc.size(); i++ )
    {
        switch (i)
        {
            case 0: vc[i] = std::get<0>(vc[i]) + a.vp[i]; break;
            case 1: vc[i] = std::get<1>(vc[i]) + a.vp[i]; break;
            default: throw "Unsuported number of coprimes";
        }
    }
    return *this;
}

template <class T>
Ciphertext<T> & Ciphertext<T>::operator *= (const Plaintext & a)
{
    for ( size_t i=0; i < vc.size(); i++ )
    {
        switch (i)
        {
            case 0: vc[i] = std::get<0>(vc[i]) * a.vp[i]; break;
            case 1: vc[i] = std::get<1>(vc[i]) * a.vp[i]; break;
            default: throw "Unsuported number of coprimes";
        }
    }
    return *this;
}

template <class T>
Ciphertext<T> & Ciphertext<T>::operator <<= (int s)
{
    for ( size_t i=0; i < vc.size(); i++ )
    {
        switch (i)
        {
            case 0: vc[i] = s ? std::get<0>(vc[i]).rotate_rows(s) : std::get<0>(vc[i]).rotate_columns(); break;
            case 1: vc[i] = s ? std::get<1>(vc[i]).rotate_rows(s) : std::get<1>(vc[i]).rotate_columns(); break;
            default: throw "Unsuported number of coprimes";
        }
    }
    return *this;
}

template <class T>
Ciphertext<T> & Ciphertext<T>::operator >>= (int s)
{
    *this <<= -s;
    return *this;
}

template <class T>
Ciphertext<T> Ciphertext<T>::operator + (const Ciphertext<T> & a) const
{
    Ciphertext<T> r(*this);
    r += a;
    return r;
}

template <class T>
Ciphertext<T> Ciphertext<T>::operator + (const Plaintext & a) const
{
    Ciphertext<T> r(*this);
    r += a;
    return r;
}

template <class T>
Ciphertext<T> Ciphertext<T>::operator * (const Plaintext & a) const
{
    Ciphertext<T> r(*this);
    r *= a;
    return r;
}

template <class T>
Ciphertext<T> Ciphertext<T>::operator << (int s) const
{
    Ciphertext<T> r(*this);
    r <<= s;
    return r;
}

template <class T>
Ciphertext<T> Ciphertext<T>::operator >> (int s) const
{
    Ciphertext<T> r(*this);
    r >>= s;
    return r;
}

template <class T>
std::vector<unsigned long long> Ciphertext<T>::decode() const
{
    return decrypt().decode();
}

template <class T>
std::vector<unsigned long long> Ciphertext<T>::decode(const Ciphertext & a)
{
    return a.decode();
}

template <class T>
Plaintext Ciphertext<T>::decrypt() const
try {
    size_t slots;
    std::vector<std::vector<unsigned long long>> vp;
    for ( size_t i=0; i<vc.size(); i++ )
    {
        std::string str;
        switch (i)
        {
            case 0:
            {
                auto c = std::get<0>(vc[i]);
                slots = decltype(c)::slots();
                str = e3::decrypt(c);
                break;
                // str = e3::decrypt( std::get<0>(vc[i]) ); break;
            }
            case 1: str = e3::decrypt( std::get<1>(vc[i]) ); break;
            default: throw "Unsuported number of coprimes";
        }
        auto l = str.size();
        if ( l > 3 && str.substr(l-3, l) == "..." ) str = str.substr(0,l-3);
        auto vstr = e3::util::split(str, '_');
        std::vector<unsigned long long> vull;
        for ( auto & e : vstr ) vull.push_back( std::stoull(e) );
        vull.resize( slots, vull.back() );
        vp.push_back(vull);
    }
    return Plaintext(vp);
}
catch (...) { throw "Cannot decrypt without private key"; }

template <class T>
Plaintext Ciphertext<T>::decrypt(const Ciphertext & a)
{
    return a.decrypt();
}

template <class T>
Ciphertext<T> Ciphertext<T>::encrypt(const Plaintext & a)
{
    return encrypt(a.vp);
}

template <class T>
Ciphertext<T> Ciphertext<T>::encrypt(const std::vector<std::vector<unsigned long long>> & a)
{
    return Ciphertext<T>(a);
}

template <class T>
void Ciphertext<T>::setTypes(const std::vector<T> & t)
{
    types.assign(t.begin(), t.end());
}

template <class T>
size_t Ciphertext<T>::slots()
{
    return std::get<0>( types[0] ).slots();
}

template <class T>
std::vector<std::string> Ciphertext<T>::str() const
{
    std::vector<std::string> vstr;
    for ( size_t i=0; i < vc.size(); i++ )
    {
        switch (i)
        {
            case 0: vstr.push_back( std::get<0>(vc[i]).str() ); break;
            case 1: vstr.push_back( std::get<1>(vc[i]).str() ); break;
            default: throw "Unsuported number of coprimes";
        }
    }
    return vstr;
}

template <class T>
std::ostream & operator <<(std::ostream & out, const Ciphertext<T> & a)
{
    auto vstr = a.str();
    std::string str = "";
    for ( auto & e : vstr ) str += e + ' ';
    if ( !str.empty() ) str = str.substr( 0, str.size()-1 );
    out << str;
    return out;
}

// --- Extra functions

template <class C, class P> void
dot_core(std::vector<std::vector<C>> & r, const std::vector<std::vector<C>> & a, const std::vector<std::vector<P>> & b, size_t nthreads, size_t id)
{
    auto slots = C::slots();
    Plaintext p( std::vector<long long>(slots, 0) );
    size_t idx  = 0;
    for ( size_t i=id; i < a.size(); i+=nthreads )
    {
        for ( size_t j=0; j < b.size(); j++ )
        {
            std::vector<C> tmp;
            for ( size_t k=0; k < a[i].size(); k++ )
                tmp.push_back( a[i][k] * b[j][k] );
            auto c = numpy::add_vector(tmp);
            for ( int s=slots>>1; s>0; )
            {
                s >>= 1;
                c += c << s;
            }
            p.encodeAt(idx, 0);
            idx  = ( i*b.size() + j ) % slots;
            p.encodeAt(idx, 1);
            r[i].push_back(c * p);
        }
    }
}

template <class C, class P> std::vector<C>
dot_compress(const std::vector<std::vector<C>> & a, const std::vector<std::vector<P>> & b, size_t nthreads)
{
    auto slots = C::slots();
    std::vector<std::vector<C>> r( a.size() );
    std::vector<std::thread> threads(nthreads);
    for ( size_t id=0; id<nthreads; id++ ) threads[id] = std::thread( dot_core<C,P>, std::ref(r), std::ref(a), std::ref(b), nthreads, id );
    for ( size_t id=0; id<nthreads; id++ ) threads[id].join();
    std::vector<C> r2;
    std::vector<C> tmp;
    size_t i = 0;
    for ( const auto & v : r )
    {
        for ( const auto & e : v )
        {
            if ( i == 0 )
            {
                if ( !tmp.empty() )
                {
                    r2.push_back( numpy::add_vector(tmp) );
                    tmp.clear();
                }
            }
            tmp.push_back( e );
            i = (i+1) % slots;
        }
    }
    if ( !tmp.empty() ) r2.push_back( numpy::add_vector(tmp) );
    return r2;
}

template <class C> void
encrypt_core(std::vector<std::vector<C>> & ciphertexts, const std::vector<std::vector<Plaintext>> & plaintexts, size_t nthreads, size_t id)
{
    auto size = plaintexts.size();
    for ( size_t i=id; i < size; i+=nthreads )
        for ( auto & p : plaintexts[i] )
            ciphertexts[i].push_back( C(p) );
}

template <class C> std::vector<std::vector<C>>
encrypt(const std::vector<std::vector<long long>> & a, size_t nthreads)
{
    auto slots = C::slots();
    auto plaintexts = encode(a, slots);
    auto size = plaintexts.size();
    std::vector<std::vector<C>> ciphertexts( size );
    std::vector<std::thread> threads(nthreads);
    for ( size_t id=0; id<nthreads; id++ ) threads[id] = std::thread( encrypt_core<C>, std::ref(ciphertexts), std::ref(plaintexts), nthreads, id );
    for ( size_t id=0; id<nthreads; id++ ) threads[id].join();
    return ciphertexts;
}

template <class C> void
encrypt_write_core(const std::vector<std::vector<Plaintext>> & plaintexts, std::ofstream & fout, char delimiter, size_t nthreads, size_t id, std::atomic<size_t> & idx, std::mutex & locker)
{
    auto size = plaintexts.size();
    for ( size_t i=id; i < size; i+=nthreads )
    {
        std::vector<C> ciphertexts;
        for ( auto & p : plaintexts[i] )
            ciphertexts.push_back( C(p) );
        while ( id != idx );
        fout << ciphertexts[0];
        for ( size_t j=1; j<ciphertexts.size(); j++ ) fout << delimiter << ciphertexts[j];
        fout << '\n';
        locker.lock();
        idx = (idx + 1) % nthreads;
        locker.unlock();
    }
}

template <class C> void
encrypt_write(const std::vector<std::vector<long long>> & a, const std::string & filename, char delimiter, size_t nthreads)
{
    auto slots = C::slots();
    auto plaintexts = encode(a, slots);
    auto size = plaintexts.size();
    std::atomic<size_t> idx = 0;
    std::mutex locker;
    std::ofstream fout(filename);
    std::vector<std::thread> threads(nthreads);
    for ( size_t id=0; id<nthreads; id++ )
        threads[id] = std::thread( encrypt_write_core<C>, std::ref(plaintexts), std::ref(fout), delimiter, nthreads, id, std::ref(idx), std::ref(locker) );
    for ( size_t id=0; id<nthreads; id++ )
        threads[id].join();
}

template <class C> std::vector<C>
loadCiphertext(const std::string & filename)
{
    std::vector<C> ciphertexts;
    std::ifstream fin(filename);
    std::string line;
    while ( std::getline(fin, line) )
    {
        auto vs = e3::util::split(line, ' ');
        ciphertexts.push_back( C(vs) );
    }
    return ciphertexts;
}

template <class C> std::vector<std::vector<C>>
loadCiphertext(const std::string & filename, char delimiter)
{
    std::vector<std::vector<C>> ciphertexts;
    std::ifstream fin(filename);
    std::string line;
    while ( std::getline(fin, line) )
    {
        std::vector<C> tmp;
        auto vline = e3::util::split(line, delimiter);
        vector<string> vs;
        for ( size_t i=0; i < vline.size(); )
        {
            vs.push_back( vline[i] );
            if ( !( ++i % C::types.size() ) )
            {
                tmp.push_back( C(vs) );
                vs.clear();
            }
        }
        ciphertexts.push_back(tmp);
    }
    return ciphertexts;
}

template <class C> void
write(const std::vector<std::vector<C>> & a, const std::string & filename, char delimiter)
{
    auto slots = C::slots();
    std::ofstream fout(filename);
    for ( auto & v : a )
    {
        fout << v[0];
        for ( size_t i=1; i<v.size(); i++ ) fout << delimiter << v[i];
        fout << '\n';
    }
}

} // crt
