#include <cmath>
#include <iostream>
#include <vector>

#include "methods.hh"

int main()
{
    using namespace std;

    auto f = [](float128_t x) {
        return 4*sin(x)-exp(x);
    };

    auto df = [](float128_t x) {
        return 4*cos(x)-exp(x);
    };

    double err = 10e-10;
    double max_iter = 1000;

    vector<pair<string, method_result>> runs = {
        {
            "Método da bisseção",
            bissection_method( f, -0.5L, 1.0L, err, max_iter )
        },
        {
            "Método de Newton",
            newthons_method( f, df, 0.7L, err, max_iter )
        },
        {
            "Método da secante",
            secant_method( f, -0.5L, 1.0L, err, max_iter )
        },
        {
            "Método da falsa posição",
            false_position_method( f, -0.5L, 1.0L, err, max_iter )
        },
    };

    for ( auto [first, second] : runs )
        cout << "X: " << second.x << " | Y: " << second.y << " | Iterações:  " << second.iterations << " | " << first << endl;

    return 0;
}
