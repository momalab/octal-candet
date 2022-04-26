#include <fstream>
#include <iostream>
#include <vector>
#include "seal/seal.h"
#include "timer.hpp"

using namespace seal;
using namespace std;

void test(uint64_t polyDegree, uint64_t plainMod, bool isBatch, int tries, vector<ofstream> & fout);

int main()
{
    const uint64_t polyI = 12, polyF = 15;
    const uint64_t plainI = 1, plainF = 16;
    int tries = 20;

    vector<string> filenames = { "seal_noise.txt", "seal_mul.txt", "seal_add.txt" };
    vector<ofstream> fout;
    for ( auto filename : filenames ) fout.emplace_back( ofstream(filename) );

    // cout << "PolyDegree PlainMod #Squares\n";
    // cout << "IntegerEncoder\n";
    for ( size_t i=polyI; i<=polyF; i++ )
        for ( size_t j=plainI; j<=plainF; j++ ) test(1<<i, 1<<j, false, tries, fout);

    // cout << "BatchEncoder\n";
    // for ( size_t i=polyI; i<=polyF; i++ ) test(1<<i, plain[1], true, tries);
}

void test(uint64_t polyDegree, uint64_t plainMod, bool isBatch, int tries, vector<ofstream> & fout)
{
    for ( auto & f : fout) f << polyDegree << "\t" << plainMod;
    while(tries--)
    {
        EncryptionParameters parms(scheme_type::BFV);
        parms.set_poly_modulus_degree(polyDegree);
        parms.set_coeff_modulus(CoeffModulus::BFVDefault(polyDegree));
        parms.set_plain_modulus(plainMod);
        auto context = SEALContext::Create(parms);
        auto qualifiers = context->first_context_data()->qualifiers();

        KeyGenerator keygen(context);
        PublicKey public_key = keygen.public_key();
        SecretKey secret_key = keygen.secret_key();
        RelinKeys relin_keys = keygen.relin_keys();
        Encryptor encryptor(context, public_key);
        Evaluator evaluator(context);
        Decryptor decryptor(context, secret_key);

        Plaintext p;
        if ( isBatch )
        {
            BatchEncoder encoder(context);
            size_t slots = encoder.slot_count();
            vector<uint64_t> intplain;
            for ( size_t i=0; i<slots; i++ ) intplain.push_back(i);
            encoder.encode(intplain, p);
        }
        else
        {
            IntegerEncoder encoder(context);
            encoder.encode(1, p);
        }

        // noise
        Ciphertext c;
        encryptor.encrypt(p, c);
        size_t counter=0;
        while ( decryptor.invariant_noise_budget(c) > 0 )
        {
            evaluator.square_inplace(c);
            evaluator.relinearize_inplace(c, relin_keys);
            counter++;
        }
        fout[0] << "\t" << counter << flush;

        // speed mul
        encryptor.encrypt(p, c);
        size_t nMuls = counter-1;
        Timer t1;
        for ( size_t i=0; i<counter; i++ )
        {
            evaluator.multiply_inplace(c,c);
            evaluator.relinearize_inplace(c, relin_keys);
        }
        double t = double( t1.get() ) / nMuls;
        fout[1] << "\t" << t << flush;

        // speed add
        encryptor.encrypt(p, c);
        size_t nAdds = 100;
        Timer t2;
        for ( size_t i=0; i<nAdds; i++ )
        {
            evaluator.add_inplace(c,c);
        }
        t = double( t2.get() ) / nAdds;
        fout[2] << "\t" << t << flush;
    }
    for ( auto & f : fout ) f << "\n";
}
