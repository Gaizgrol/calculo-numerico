#include <cmath>
#include <iostream>
#include <vector>

#include "methods.hh"

int main()
{
    using namespace std;


    // f(x) = xlog10(x) − 1

    auto f = [](float128_t x) {
        return x*log10(x) - 1.0L;
    };

    auto df = [](float128_t x) {
        return log10(x) + 1.0L/log(x);
    };

    double err = 10e-7;
    double max_iter = 1000;

    vector<pair<string, method_result>> runs = {
        {
            "Método da bisseção",
            bissection_method( f, 2.0L, 3.0L, err, max_iter )
        },
        {
            "Método de Newton",
            newthons_method( f, df, 2.5L, err, max_iter )
        },
        {
            "Método da secante",
            secant_method( f, 2.0L, 3.0L, err, max_iter )
        },
        {
            "Método da falsa posição",
            false_position_method( f, 2.0L, 3.0L, err, max_iter )
        },
    };

    for ( auto [first, second] : runs )
        cout << "X: " << second.x << " | Y: " << second.y << " | Iterações:  " << second.iterations << " | " << first << endl;

    return 0;
}
