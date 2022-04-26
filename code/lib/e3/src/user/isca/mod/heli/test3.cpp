#include <fstream>
#include <iostream>
#include <vector>
#include "params.hpp"
#include "timer.hpp"

#include <NTL/ZZ.h>
#include "FHE.h"

using namespace std;

const double cutpoint = 100; // bits of security

void test(vector<int64_t> p, int tries, vector<ofstream> & fout);

void test(int64_t p, int64_t phim, int64_t m, int64_t d, int64_t m1,
          int64_t m2, int64_t m3, int64_t g1, int64_t g2, int64_t g3,
          int64_t ord1, int64_t ord2, int64_t ord3, int64_t c_m,
          int tries, vector<ofstream> & fout);

int main()
{
    int tries = 20;
    vector<string> filenames = { "heli_noise.txt", "heli_mul.txt", "heli_add.txt" };
    vector<ofstream> fout;
    for ( auto filename : filenames ) fout.emplace_back( ofstream(filename) );
    for ( auto & params : table )
    {
	if ( params[0] != 127 ) continue;
    	test(params, tries, fout);
    }
}

void test(vector<int64_t> p, int tries, vector<ofstream> & fout)
{
    for ( auto param : p ) cout << param << "\t";
    cout << "\n";
    test(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], tries, fout);
}

void test(int64_t p, int64_t phim, int64_t m, int64_t d, int64_t m1,
          int64_t m2, int64_t m3, int64_t g1, int64_t g2, int64_t g3,
          int64_t ord1, int64_t ord2, int64_t ord3, int64_t c_m,
          int tries, vector<ofstream> & fout)
{
    // p plaintext base
    // p^r is the plaintext-space modulus
    int64_t r = 1; // exponent
    int64_t c = 3; // number of columns in the key-switching matrices
    int64_t L = 25; // # of levels in the modulus chain
    int64_t B = 23; // # of bits per level
    int64_t N = 0; // lower-bound on phi(m)
    int64_t t = 0; // Hamming weight of recryption secret key
    bool cons = 0; // cons=1 for consevative settings (circuit deeper by 1)
    int64_t w = 64;
    int64_t cacheType = 0; // 0: zzX cache, 1: DCRT cache

    while (tries--)
    {
        Vec<int64_t> mvec;
        append(mvec, m1);
        if (m2) append(mvec, m2);
        if (m3) append(mvec, m3);
        vector<int64_t> gens(1, g1);
        if (g2) gens.push_back(g2);
        if (g3) gens.push_back(g3);
        vector<int64_t> ords(1, ord1);
        if (ord2) ords.push_back(ord2);
        if (ord3) ords.push_back(ord3);

        FHEcontext context(m, p, r, gens, ords);
        context.bitsPerLevel = B;
        buildModChain(context, L, c, 7);

        double seclevel = context.securityLevel();
        cout << "secure level: " << seclevel << "\n";
        // if ( seclevel < cutpoint ) return;

        context.makeBootstrappable(mvec, 0, cons, cacheType);
        context.zMStar.set_cM(c_m / 100.0);
        FHESecKey secretKey(context);
        FHEPubKey & publicKey = secretKey;
        secretKey.GenSecKey(w);
        addSome1DMatrices(secretKey);
        addFrbMatrices(secretKey);
        secretKey.genRecryptData();

        Ctxt ct(publicKey);

        // noise
        publicKey.Encrypt(ct, to_ZZX(1));
        size_t counter = 0;
        while ( ct.getNoiseVar() > 0 )
        {
            ct *= ct;
            counter++;
        }
        fout[0] << "\t" << (counter+1) << flush;

        // speed mul
        publicKey.Encrypt(ct, to_ZZX(1));
        size_t nMuls = counter;
        Timer t1;
        for ( size_t i=0; i<counter; i++ )
        {
            ct *= ct;
        }
        double tm = double( t1.get() ) / nMuls;
        fout[1] << "\t" << tm << flush;

        // speed add
        publicKey.Encrypt(ct, to_ZZX(1));
        size_t nAdds = 100;
        Timer t2;
        for ( size_t i=0; i<nAdds; i++ )
        {
            ct += ct;
        }
        tm = double( t2.get() ) / nAdds;
        fout[2] << "\t" << tm << flush;
    }
    for ( auto & f : fout ) f << "\n";
}
