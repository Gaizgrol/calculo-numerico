#ifndef METHODS_HH
#define METHODS_HH

#include <functional>
#include "floats.h"

typedef struct method_result
{
    float128_t x;
    float128_t y;
    size_t iterations;
} method_result;

method_result bissection_method(
    std::function<float128_t(float128_t)> f,
    float128_t x0,
    float128_t x1,
    float128_t max_err,
    size_t max_iter
);

method_result newthons_method(
    std::function<float128_t(float128_t)> f,
    std::function<float128_t(float128_t)> df,
    float128_t guess,
    float128_t max_err,
    size_t max_iter
);

method_result secant_method(
    std::function<float128_t(float128_t)> f,
    float128_t x0,
    float128_t x1,
    float128_t max_err,
    size_t max_iter
);

method_result false_position_method(
    std::function<float128_t(float128_t)> f,
    float128_t x0,
    float128_t x1,
    float128_t max_err,
    size_t max_iter 
);

#endif