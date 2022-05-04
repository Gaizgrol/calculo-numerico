#include <cmath>
#include "methods.hh"

method_result bissection_method(
    std::function<float128_t(float128_t)> f,
    float128_t x0,
    float128_t x1,
    float128_t max_err,
    size_t max_iter
) {
    for ( size_t i = 0; i < max_iter; i++ )
    {
        auto x = ( x0 + x1 ) / 2.0;
        auto y = f(x);
        if ( y == 0 || ( x1-x0 ) / 2 <= max_err )
            return { x, y, i+1 };
        if ( y < 0 )
            x0 = x;
        else
            x1 = x;
    }
    return { NAN, NAN, max_iter };
}

method_result newthons_method(
    std::function<float128_t(float128_t)> f,
    std::function<float128_t(float128_t)> df,
    float128_t guess,
    float128_t max_err,
    size_t max_iter
) {
    auto x = guess;
    for ( size_t i = 0; i < max_iter; i++ )
    {
        auto y = f( x );
        auto dy = df( x );
        if ( fabs( y ) < max_err )
            return { x, y, i+1 };
        x = x - y/dy;
    }
    return { NAN, NAN, max_iter };
}

method_result secant_method(
    std::function<float128_t(float128_t)> f,
    float128_t x0,
    float128_t x1,
    float128_t max_err,
    size_t max_iter
) {
    for ( size_t i = 0; i < max_iter; i++ )
    {
        auto x2 = x1 - f(x1) * (x1 - x0) / ( f(x1) - f(x0) );
        auto y = f(x2);
        if ( fabs( y ) < max_err )
            return { x2, y, i+1 };
        x0 = x1;
        x1 = x2;
    }
    return { NAN, NAN, max_iter };
}

method_result false_position_method(
    std::function<float128_t(float128_t)> f,
    float128_t x0,
    float128_t x1,
    float128_t max_err,
    size_t max_iter 
) {
    double x, y;
    int side = 0;
    double fx0 = f(x0);
    double fx1 = f(x1);

    for ( size_t i = 0; i < max_iter; i++ )
    {
        x = (fx0 * x1 - fx1 * x0) / (fx0 - fx1);
        y = f(x);
        
        if ( fabs( y ) < max_err )
            return { x, y, i+1 };

        if (y * fx1 > 0)
        {
            x1 = x; fx1 = y;
            if (side == -1)
                fx0 /= 2;
            side = -1;
        }
        else if (fx0 * y > 0)
        {
            x0 = x; fx0 = y;
            if (side == +1)
                fx1 /= 2;
            side = +1;
        }
        else
            return { x, y, i+1 };
    }

    return { NAN, NAN, max_iter };
}
