#pragma once

#include "e3int.h"

using Secure = SecureInt<8>;

class KalmanFilter
{
    private:
        Secure errMeasure, errEstimate;
        Secure currentEstimate, lastEstimate;
        Secure q, gain, one;
        uint64_t shift;

    public:
        KalmanFilter() { }
        KalmanFilter(const Secure & errMeasure, const Secure & errEstimate, const Secure & q, uint64_t shift);
        Secure update(const Secure & measure);
};
