#include <iostream>
#include <fstream>
#include <string>

#include "cons.hpp"
#include "dataformat.hpp"
#include "io.hpp"
#include "numpy.hpp"
#include "timer.hpp"

#include "crt.hpp"
#include "plaintext.hpp"
#include "ciphertext.hpp"

using namespace crt;
using namespace dataformat;
using namespace io;
using namespace numpy;
using namespace std;

using ull = unsigned long long;
using  ll =          long long;
using CRT_t = CRT<ull,ll>;
using Type = variant<Secure0, Secure1>;
using Ciphertext_t = Ciphertext<Type>;

int main(int argc, char * argv[])
try
{
    Timer t_total;

    if (argc < 12)
    {
        cout << "Usage: main.exe idfile cnfile varfile cnftfile varftfile ofile ibit nthr\n";
        cout << " idfile   : patient ids file\n";
        cout << " cnfile   : parsed CN file\n";
        cout << " varfile  : parsed variant file\n";
        cout << " cnftfile : CN features file\n";
        cout << " varftfile: variant features file\n";
        cout << " wfile    : weights filename\n";
        cout << " bfile    : biases filename\n";
        cout << " ofile    : output file\n";
        cout << " ibit     : bit precision of input\n";
        cout << " wbit     : bit precision of weights\n";
        cout << " nthr     : # of threads\n";
        return 1;
    }

    auto idfile     = string( argv[ 1] ); // vector
    auto cnfile     = string( argv[ 2] ); // matrix
    auto varfile    = string( argv[ 3] ); // matrix
    auto cnftfile   = string( argv[ 4] ); // vector
    auto varftfile  = string( argv[ 5] ); // vector
    auto wfile      = string( argv[ 6] ); // matrix
    auto bfile      = string( argv[ 7] ); // vector
    auto ofile      = string( argv[ 8] ); // filename
    ll   ibit       = stoull( argv[ 9] ); // integer
    ll   wbit       = stoull( argv[10] ); // integer
    size_t nthreads = stoull( argv[11] ); // integer

    // setting parameters for double CRT and batch encoding
    auto types = vector<Type>{ Secure0() };
    if ( cons::coprimes.size() > 1) types.push_back( Secure1() );
    CRT_t::setCoprimes(cons::coprimes);
    Ciphertext_t::setTypes(types);
    auto slots = Ciphertext_t::slots();
    ll scaler_i = 1 << ibit;
    ll scaler_w = 1 << wbit;
    ll scaler_b = scaler_i + scaler_w;

    // load files
    auto t = Timer();
    auto ids      = loadtxt(idfile);
    auto cn_ft    = loadtxt(cnftfile);
    auto var_ft   = loadtxt(varftfile);
    auto cn       = loadtxt(cnfile , cons::data_delimiter);
    auto var      = loadtxt(varfile, cons::data_delimiter);
    auto w_double = load<double>(wfile, cons::delimiter);
    auto b_double = load<double>(bfile);
    cout << "Time (load): " << (t.get() / cons::us) << " s\n";

    // ENCRYPTION
    // map the data for batch encryption - only data movement
    // scale double to int to use the BFV encryption scheme
    // encrypt
    t = Timer();
    auto x_double = map_data(ids, cn, var, cn_ft, var_ft);
    auto x_int    = scale(x_double, scaler_i);
    auto x        = encrypt<Ciphertext_t>(x_int, nthreads);
    cout << "Time (encryption): " << (t.get() / cons::us) << " s\n";

    // COMPUTATION
    // scale and encode weights and biases
    // homomorphic inference
    t = Timer();
    auto w_ull = scale(w_double, scaler_w);
    auto b_ull = scale(b_double, scaler_b);
    auto w     = encode(w_ull, slots);
    auto b     = encode(b_ull, slots, x.size());
    auto y     = add( dot_compress( x, w, nthreads), b );
    cout << "Time (computation): " << (t.get() / cons::us) << " s\n";

    // DECRYPTION
    t = Timer();
    // decrypt, decode, and append to vector
    vector<ull> vp;
    for ( auto & c : y )
    {
        auto tmp = c.decode(); // decrypt and decode
        vp.insert( vp.end(), tmp.begin(), tmp.end() );
    }
    // write output file
    auto ntypes = cons::cancerTypes.size();
    {
        ofstream fout(ofile);
        for ( size_t i=0; i < ids.size(); i++ )
        {
            fout << ids[i];
            for ( size_t j=0; j < ntypes; j++ )
                fout << cons::data_delimiter << vp[ i * ntypes + j ];
            fout << '\n';
        }
    }
    cout << "Time (decryption): " << (t.get() / cons::us) << " s\n";

    cout << "Time (main): " << (t_total.get() / cons::us) << " s\n";
}
catch (const char * e) { cout << "error: " << e << '\n'; }
catch (const string * e) { cout << "error: " << e << '\n'; }
