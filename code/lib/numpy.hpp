#pragma once

#include <algorithm>
#include <iterator>
#include <thread>
#include <vector>

using std::vector;

namespace numpy
{

size_t sizeCeilPowerOfTwo(size_t n)
{
    size_t counter=0;
    while (n) { counter++; n>>=1; }
    return counter;
}

template <class T>
T add_vector(vector<T> & v)
{
    auto size = v.size();
    for ( auto n = 1<<sizeCeilPowerOfTwo(size); n>1; )
    {
        n >>= 1;
        for ( size_t i=n; i<size; i++ ) v[i-n] += v[i];
        size = n;
    }
    return v[0];
}

template <class T, class U> vector<T>
add(const vector<T> & a, const vector<U> & b)
{
    vector<T> c;
    for ( size_t i=0; i < a.size(); i++ )
        c.push_back( a[i] + b[i] );
    return c;
}

template <class T> void
add_rows_core(vector<vector<T>> & r, const vector<vector<T>> & a, size_t nthreads, size_t id)
{
    auto inc = nthreads << 1;
    for ( size_t i=id<<1; i < a.size(); i+=inc )
        for ( size_t j=0; j < a[i].size(); j++ )
            r[i>>1][j] = a[i][j] + a[i+1][j];
}

template <class T> vector<vector<T>>
add_rows(const vector<vector<T>> & a, size_t nthreads)
{
    auto rows = a.size() >> 1;
    auto cols = a[0].size();
    vector<vector<T>> r( rows, vector<T>(cols) );
    std::vector<std::thread> threads(nthreads);
    for ( size_t id=0; id<nthreads; id++ ) threads[id] = std::thread( add_rows_core<T>, std::ref(r), std::ref(a), nthreads, id );
    for ( size_t id=0; id<nthreads; id++ ) threads[id].join();
    return r;
}

template <class T> vector<size_t>
argmax(const vector<vector<T>> & m)
{
    vector<size_t> v;
    for ( size_t i=0; i<m.size(); i++ )
    {
        size_t idx = 0;
        for ( size_t j=0; j<m[0].size(); j++ )
            if ( m[i][j] > m[i][idx] ) idx = j;
        v.push_back(idx);
    }
    return v;
}

template <class T> size_t
countEqual(const vector<T> & a, const vector<T> & b)
{
    if ( a.size() != b.size() ) throw "Vectors must have the same size";
    size_t count = 0;
    for ( size_t i=0; i<a.size(); i++ ) count += a[i] == b[i];
    return count;
}

template <class T, class U> T
scale(const U & n, const T & scaler)
{
    return T(n * scaler);
}

template <class T, class U> vector<T>
scale(const vector<U> & n, const T & scaler)
{
    vector<T> r;
    for ( const auto & e : n ) r.push_back( scale(e, scaler) );
    return r;
}

template <class T, class U> vector<vector<T>>
scale(const vector<vector<U>> & n, const T & scaler)
{
    vector<vector<T>> r;
    for ( const auto & e : n ) r.push_back( scale(e, scaler) );
    return r;
}

} // numpy
