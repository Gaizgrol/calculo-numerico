#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

typedef struct method_result
{
    double x;
    double y;
    size_t iterations;
} method_result;

method_result bissection_method( std::function<double(double)> f, double x0, double x1, double max_err, size_t max_iter )
{
    for ( size_t i = 0; i < max_iter; i++ )
    {
        auto x = ( x0 + x1 ) / 2.0;
        auto y = f(x);
        if ( y == 0 || ( x1-x0 ) / 2 <= max_err )
            return { x, y, i };
        if ( y < 0 )
            x0 = x;
        else
            x1 = x;
    }
    return { NAN, NAN, max_iter };
}

method_result newthons_method( std::function<double(double)> f, std::function<double(double)> df, double guess, double max_err, size_t max_iter )
{
    auto x = guess;
    for ( size_t i = 0; i < max_iter; i++ )
    {
        auto y = f( x );
        auto dy = df( x );
        if ( fabs( y ) <= max_err )
            return { x, y, i };
        x = x - y/dy;
    }
    return { NAN, NAN, max_iter };
}

method_result secant_method( std::function<double(double)> f, double x0, double x1, double max_err, size_t max_iter )
{
    for ( size_t i = 0; i < max_iter; i++ )
    {
        auto x2 = x1 - f(x1) * (x1 - x0) / ( f(x1) - f(x0) );
        auto y = f(x2);
        if ( fabs( y ) <= max_err )
            return { x2, y, i };
        x0 = x1;
        x1 = x2;
    }
    return { NAN, NAN, max_iter };
}

int main()
{
    using namespace std;

    auto f = [](double x) {
        return 4*sin(x)-exp(x);
    };

    auto df = [](double x) {
        return 4*cos(x)-exp(x);
    };

    double err = 10e-10;
    double max_iter = 100;

    vector<pair<string, method_result>> runs = {
        {
            "Método da bisseção",
            bissection_method( f, -0.5, 1.0, err, max_iter )
        },
        {
            "Método de Newton",
            newthons_method( f, df, 0.7, err, max_iter )
        },
        {
            "Método da secante",
            secant_method( f, -0.5, 1.0, err, max_iter )
        }
    };

    for ( auto [first, second] : runs )
        cout << "[" << first << "]\tX: " << second.x << "\t| Y: " << second.y << " |\tConvergiu em " << second.iterations << " iterações" << endl;

    return 0;
}
