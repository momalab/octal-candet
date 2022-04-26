#include <fstream>
#include <iostream>
#include <vector>
#include "timer.hpp"

#include <NTL/ZZ.h>
#include "FHE.h"

using namespace std;

vector<vector<int64_t>> table = {
    //{ p, phi(m),  m,    d, m1,  m2, m3,   g1,    g2,    g3,ord1,ord2,ord3, c_m}
    {  2, 16384, 21845, 16, 17,   5,257,  8996, 17477, 21591, 16, 4, -16, 200} // m=5*17*(257) :-( m/phim(m)=1.33 C=65 D=4 E=4
    // {  2, 23040, 28679, 24, 17,  7, 241, 15184,  4098, 28204, 16,  6, -10, 1000}, // m=7*17*(241) m/phim(m)=1.24    C=63  D=4 E=3
    // {127, 26112, 30277, 24, 17, 1781, 0, 14249, 10694,    0, 16, 68,   0, 100} // m=(13)*17*{137} m/phim(m)=1.15  C=106 D=2
};

const double maxOps = 3;

void test(vector<int64_t> p, int tries, vector<ofstream> & fout);

void test(int64_t p, int64_t phim, int64_t m, int64_t d, int64_t m1,
          int64_t m2, int64_t m3, int64_t g1, int64_t g2, int64_t g3,
          int64_t ord1, int64_t ord2, int64_t ord3, int64_t c_m,
          int tries, vector<ofstream> & fout);

int main()
{
    int tries = 1;
    vector<string> filenames = { "heli_boot_mul.txt" };
    vector<ofstream> fout;
    for ( auto filename : filenames ) fout.emplace_back( ofstream(filename) );
    for ( auto & params : table )
        test(params, tries, fout);
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
    int64_t c = 4; //3; // number of columns in the key-switching matrices
    int64_t L = 25; //25; // # of levels in the modulus chain
    int64_t B = 16; //23; // # of bits per level
    int64_t N = 0; // lower-bound on phi(m)
    int64_t t = 0; // Hamming weight of recryption secret key
    bool cons = 0; // cons=1 for consevative settings (circuit deeper by 1)
    int64_t w = 64;
    int64_t cacheType = 0; // 0: zzX cache, 1: DCRT cache

    vector<vector<double>> time_mul(maxOps);
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

        context.makeBootstrappable(mvec, 0, cons, cacheType);
        context.zMStar.set_cM(c_m / 100.0);
        FHESecKey secretKey(context);
        FHEPubKey & publicKey = secretKey;
        secretKey.GenSecKey(w);
        addSome1DMatrices(secretKey);
        addFrbMatrices(secretKey);
        secretKey.genRecryptData();

        Ctxt ct(publicKey);

    	// speed mul
        cout << tries << ":" << flush;
        double noiseLimit = -210;
        publicKey.Encrypt(ct, to_ZZX(1));
    	Timer t1;
        for ( size_t nOps=1; nOps<=maxOps; nOps++ )
        {
            //for ( size_t i=0; i<nOps; i++ )
            //{
            ct.multiplyBy(ct);
            // cout << " | " << ct.log_of_ratio() << " | " << flush;
            // if ( ct.log_of_ratio() > noiseLimit )
            // {
            // cout << " AAA " << flush;
                publicKey.reCrypt(ct);
            // }
            double tm = double( t1.get() ) / nOps;
            time_mul[nOps-1].push_back(tm);
            cout << " " << nOps << flush;
        }
        cout << "\n";

        string filename = "ct" + to_string(phim) + "_" + to_string(L) + "_" + to_string(B) + "_" + to_string(seclevel) + ".tmp";
        ofstream of(filename, ios::binary);
        of << ct;
    }

    for ( auto & v : time_mul )
    {
        for ( auto e : v ) fout[0] << "\t" << e;
        fout[0] << "\n";
    }
}
