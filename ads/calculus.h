#pragma once
#include <algorithm>

namespace ads
{
    namespace mathematics
    {
        namespace calculus
        {
            template<typename f>
            double bisection(f fun, double a, double b, double eps = 1E-3)
            {
                if (fun(a) * fun(b) > 0)
                    return NAN;

                if (a > b)
                    std::swap(a, b);

                while (std::abs(fun((a + b) / 2.0)) > eps)
                {
                    if (fun(a) * fun((a + b) / 2.0) < 0.0)
                        b = (a + b) / 2.0;
                    else if (fun((a + b) / 2.0) * fun(b) < 0.0)
                        a = (a + b) / 2.0;
                    else
                        break;
                }

                return (a + b) / 2.0;
            }

            template<typename f>
            double HordMethod(f fun, double a, double b, double eps = 1E-3)
            {
                if (fun(a) * fun(b) > 0)
                    return NAN;

                if (a > b)
                    std::swap(a, b);

                double x0;
                if (fun(a) > 0)
                {
                    x0 = b;
                    while (std::abs(fun(x0)) > eps)
                        x0 -= fun(x0) * std::abs(x0 - a) / std::abs(fun(x0) - fun(a));
                }
                else if (fun(a) < 0)
                {
                    x0 = a;
                    while (std::abs(fun(x0)) > eps)
                        x0 -= fun(x0) * std::abs(b - x0) / std::abs(fun(b) - fun(x0));
                }
                else
                    x0 = a;

                return x0;
            }

            template<typename f>
            double NewtonMethod(f fun, double a, double b, double eps = 1E-3)
            {
                if (fun(a) * fun(b) > 0)
                    return NAN;

                if (a > b)
                    std::swap(a, b);

                double x0 = a;

                while (std::abs(fun(x0)) > eps)
                    x0 -= fun(x0) * eps / (fun(x0 + eps) - fun(x0));

                return x0;
            }
        }
    }
}