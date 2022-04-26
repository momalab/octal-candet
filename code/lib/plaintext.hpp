#pragma once

#include <vector>

namespace crt
{

template <class T> class Ciphertext;

class Plaintext
{
    private:
        std::vector<std::vector<unsigned long long>> vp;

    public:
        Plaintext(){}
        Plaintext(const std::vector<long long> &);
        Plaintext(const std::vector<std::vector<unsigned long long>> &);
        Plaintext(const Plaintext & a) : Plaintext(a.vp){}

        std::vector<unsigned long long> decode() const;
        static std::vector<unsigned long long> decode(const Plaintext &);
        static Plaintext encode(const std::vector<long long> &);
        void encodeAt(size_t, long long);

        template <class T> friend class Ciphertext;
};

std::vector<std::vector<Plaintext>>
encode(const std::vector<std::vector<long long>> &, size_t);

std::vector<Plaintext>
encode(const std::vector<long long> &, size_t, size_t);

} // crt
