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
            return { x, y, i+1 };
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
        if ( fabs( y ) < max_err )
            return { x, y, i+1 };
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
        if ( fabs( y ) < max_err )
            return { x2, y, i+1 };
        x0 = x1;
        x1 = x2;
    }
    return { NAN, NAN, max_iter };
}

method_result false_position_method( std::function<double(double)> f, double x0, double x1, double max_err, size_t max_iter )
{
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
    double max_iter = 1000;

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
        },
        {
            "Método da falsa posição",
            false_position_method( f, -0.5, 1.0, err, max_iter )
        },
    };

    for ( auto [first, second] : runs )
        cout << "X: " << second.x << " | Y: " << second.y << " | Iterações:  " << second.iterations << " | " << first << endl;

    return 0;
}
