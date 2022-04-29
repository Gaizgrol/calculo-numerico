#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

typedef struct method_result
{
    double root;
    double result;
    size_t iterations;
} method_result;

method_result bissection_method( std::function<double(double)> f, double a, double b, double max_err, size_t max_iter )
{
    for ( size_t i = 0; i < max_iter; i++ )
    {
        double result = ( a + b ) / 2;
        double root_candidate = f(result);
        if ( root_candidate == 0.0 || (b-a)/2 <= max_err )
            return { root_candidate, result, i };
        if ( root_candidate < 0.0 )
            a = result;
        else
            b = result;
    }
    return { NAN, NAN, max_iter };
}

method_result newthons_method( std::function<double(double)> f, std::function<double(double)> df, double guess, double max_err, size_t max_iter, double almost_zero )
{
    return { NAN, NAN, 0 };
}

method_result secant_method( std::function<double(double)> f, std::function<double(double)> df, double guess, double max_err, size_t max_iter, double almost_zero )
{
    return { NAN, NAN, 0 };
}

int main()
{
    using namespace std;

    // f(x) => 4sen(x) - e^x
    // f'(x) => 4cos(x) - e^x
    // Raiz >= 0 && Raiz <= 1
    // Erro => 10e-5
    double n = -0.5;
    double p = 1.0;
    double err = 10e-5;
    double max_iter = 100;

    vector<pair<string, method_result>> runs = {
        {
            "Método da bisseção",
            bissection_method( [](double x) {
                return 4*sin(x)-exp(x);
            }, n, p, err, max_iter )
        },
        {
            "Método de Newton",
            newthons_method( [](double x) {
                return 4*sin(x)-exp(x);
            }, [](double x) {
                return 4*cos(x)-exp(x);
            }, p, err, max_iter, 10e-10 )
        },
        {
            "Método da secante",
            secant_method( [](double x) {
                return 4*sin(x)-exp(x);
            }, [](double x) {
                return 4*cos(x)-exp(x);
            }, p, err, max_iter, 10e-10 )
        }
    };

    for ( auto [first, second] : runs )
        cout << "[" << first << "] Raiz: " << second.root << " | Resultado: " << second.result << " | Convergiu em " << second.iterations << " iterações" << endl;

    return 0;
}