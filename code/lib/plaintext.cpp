#include "plaintext.hpp"

#include "crt.hpp"

using namespace std;
using ull = unsigned long long;
using  ll =          long long;

namespace crt
{

using CRT_t = CRT<ull,ll>;

Plaintext::Plaintext(const vector<ll> & a)
{
    *this = encode(a);
}

Plaintext::Plaintext(const vector<vector<ull>> & a)
{
    vp.clear();
    for ( auto & v : a )
    {
        vp.push_back( vector<ull>() );
        for ( auto e : v ) vp.back().push_back(e);
    }
}

vector<ull> Plaintext::decode() const
{
    vector<ull> v;
    if ( !vp.empty() )
    {
        for ( size_t j=0; j < vp[0].size(); j++ )
        {
            vector<ull> tmp;
            for ( size_t i=0; i < vp.size(); i++ ) tmp.push_back( vp[i][j] );
            v.push_back( CRT_t(tmp).decode() );
        }
    }
    return v;
}

vector<ull> Plaintext::decode(const Plaintext & a)
{
    return a.decode();
}

Plaintext Plaintext::encode(const vector<ll> & a)
{
    vector<vector<ull>> vp( CRT_t::size(), vector<ull>() );
    for ( auto e : a )
    {
        auto v = CRT_t::encode(e).get();
        for ( size_t i=0; i < v.size(); i++ )
            vp[i].push_back( v[i] );
    }
    return Plaintext(vp);
}

void Plaintext::encodeAt(size_t idx, ll value)
{
    auto v = CRT_t::encode(value).get();
    for ( size_t i=0; i < v.size(); i++ )
        vp[i][idx] = v[i];
}

vector<vector<Plaintext>> encode(const vector<vector<ll>> & a, size_t slots)
{
    vector<vector<Plaintext>> plaintexts;
    for ( auto & v : a )
    {
        vector<Plaintext> vp;
        vector<ll> vull;
        for ( size_t i=0; i < v.size(); )
        {
            vull.push_back( v[i] );
            if ( !( ++i % slots ) )
            {
                vp.push_back( Plaintext(vull) );
                vull.clear();
            }
        }
        if ( !vull.empty() ) vp.push_back( Plaintext(vull) );
        plaintexts.push_back(vp);
    }
    return plaintexts;
}

vector<Plaintext> encode(const vector<ll> & a, size_t slots, size_t repeat)
{
    vector<ll> v;
    for ( size_t i=0; i < repeat; i++ )
        v.insert( v.end(), a.begin(), a.end() );

    vector<Plaintext> plaintexts;
    vector<ll> vull;
    for ( size_t i=0; i < v.size(); )
    {
        vull.push_back( v[i] );
        if ( !( ++i % slots ) )
        {
            plaintexts.push_back( Plaintext(vull) );
            vull.clear();
        }
    }
    if ( !vull.empty() ) plaintexts.push_back( Plaintext(vull) );
    return plaintexts;
}

} // crt
