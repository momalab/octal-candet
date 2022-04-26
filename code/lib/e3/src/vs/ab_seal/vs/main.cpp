#include <iostream>
#include <string>
#include "functions.hpp"

using namespace std;

const size_t SZ = 8;
const string db = "../tests/user/neural_network/python/";
const unsigned shift = 5; // bits

#define D { cout<< (__LINE__) << "# " << flush; }

int main()
try
{
    auto plain_xtest = load<double>(db + "Test_MNIST_compact_1.txt", ',');
    auto ytest = load<double>(db + "Test_MNIST_labels.txt", ',');

    auto plain_w1 = load<double>(db + "W1_compact.txt", ',');
    auto plain_b1 = load<double>(db + "b1.txt");

    auto plain_w2 = load<double>(db + "W2.txt", ',');
    auto plain_b2 = load<double>(db + "b2.txt");

    D cout << plain_xtest.size() << " x " << plain_xtest[0].size() << '\n';
    D cout << plain_w1.size() << " x " << plain_w1[0].size() << '\n';
    D cout << plain_b1.size() << '\n';
    D cout << plain_w2.size() << " x " << plain_w2[0].size() << '\n';
    D cout << plain_b2.size() << '\n';

    D auto encoded_xtest = encode(plain_xtest, shift);
    D auto w1 = encode(plain_w1, shift);
    D auto encoded_b1 = encode(plain_b1, 2*shift);
    D auto w2 = encode(plain_w2, shift);
    D auto encoded_b2 = encode(plain_b2, 3*shift);

    D cout << "---\n";
    D cout << encoded_xtest.size() << " x " << encoded_xtest[0].size() << '\n';
    D cout << encoded_b1.size() << '\n';
    D cout << encoded_b2.size() << '\n';

    SecureMod zero = _0_Ea;
    D auto xtest = encrypt<SecureMod>(encoded_xtest);
    D auto b1 = encrypt<SecureMod>(encoded_b1);
    D auto b2 = encrypt<SecureMod>(encoded_b2);

    D cout << "---\n";
    D cout << xtest.size() << " x " << xtest[0].size() << '\n';
    D cout << b1.size() << '\n';
    D cout << b2.size() << '\n';

    D auto t1 = dot(xtest, w1, zero);
    D cout << t1.size() << " x " << t1[0].size() << '\n';
    D auto h1 = add( dot(xtest, w1, zero), b1 );
    D auto o_ = add( dot(h1, w2, zero), b2 );

    D auto plain_o_ = decrypt(o_);
    D auto ohat = argmax(plain_o_);
    D auto o = argmax(ytest);

    D auto accuracy = double( countEqual(o,ohat) ) / ohat.size();
    D cout << "Accuracy is: " << accuracy << '\n';
}
catch ( const char* & e )
{
    cout << "Error: " << e << '\n';
}
