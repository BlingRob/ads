// \\\ file calculus.h 
// \\\ Standart calculus things.
// \\\ Now there is solver of function's root
#pragma once
#include <algorithm>
#include <cmath>
#include "core.h"

namespace ads
{
    namespace mathematics
    {
        namespace calculus
        {
            template<typename f,typename T>
            double bisection(f fun, T a, T b, T eps = 1E-3)
            {
                if (fun(a) * fun(b) > 0)
                    return NAN;

                if (a > b)
                    std::swap(a, b);

                T half = (a + b) / 2.0;
                while (std::abs(fun(half)) > eps)
                {
                    half = (a + b) / 2.0;
                    if (fun(a) * fun(half) <= 0.0)
                        b = half;
                    else if (fun(half) * fun(b) < 0.0)
                        a = half;
                    else
                        break;
                }

                return half;
            }

            template<typename f,typename T>
            double HordMethod(f fun, T a, T b, T eps = 1E-3)
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

            template<typename f,typename T>
            double NewtonMethod(f fun, T a, T b, T eps = 1E-3)
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