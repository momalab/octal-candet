#include <iostream>
#include "e3int.h"
#include "e3key.h"

using namespace std;

using SecureMint = Mint;


int main()
{
  SecureMint a = _2_ep;
  SecureMint b = _3_en;

  std::cout << e3::decrypt(a) << ' ' << e3::decrypt(b) << ' ' <<  e3::decrypt(a*b) << '\n';

  SecureMint c = _1_ep;
  SecureMint d = _1_en;

  std::cout << e3::decrypt(c) << ' ' << e3::decrypt(d) << ' ' <<  e3::decrypt(c*d) << '\n';
}
