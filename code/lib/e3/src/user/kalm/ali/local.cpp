#include <fstream>
#include <string>

#include "e3int.h"
#include "e3key.h" // alice

using namespace std;
using Secure = SecureInt<8>;

uint64_t shift = 10; // bits -- to emulate fixed-point arithmetic on integers
uint64_t scale = 1 << shift;

int main()
{
    ifstream fin("cloud.data");
    ofstream fout("decrypted.data");

    fout << "filtered data\n";
    string ciphertext;
    while ( getline(fin, ciphertext) )
    {
        auto plaintext = std::stoll( e3::decrypt( Secure(ciphertext) ) );
        auto result = float(plaintext) / scale;
        fout << result << "\n";
    }
}
