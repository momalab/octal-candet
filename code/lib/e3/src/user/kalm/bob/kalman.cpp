#include "kalman.hpp"

KalmanFilter::KalmanFilter(const Secure & errMeasure, const Secure & errEstimate, const Secure & q, uint64_t shift)
{
    this->errMeasure = errMeasure;
    this->errEstimate = errEstimate;
    this->q = q;
    this->shift = shift;
    one = Secure(_1_Ep) << shift;
    lastEstimate = _0_Ep;
}

Secure KalmanFilter::update(const Secure & measure)
{
    gain = (errEstimate << shift) / (errEstimate + errMeasure);
    currentEstimate = lastEstimate + gain * (measure - (lastEstimate >> shift));
    errEstimate = (one - gain) * errEstimate + abs(lastEstimate - currentEstimate) * q;
    errEstimate >>= shift;
    lastEstimate = currentEstimate;
    return Secure(currentEstimate);
}
