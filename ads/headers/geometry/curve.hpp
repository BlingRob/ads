
#include "vector.hpp"
#include <iostream>
#pragma once
#ifndef __CURVE_HPP__
#define __CURVE_HPP__

namespace ads
{
    namespace mathematics
    {
        namespace geometry
        {
            /*
            ## Need to change initializer_list to variadic template functions

            template <typename Fun, class = typename std::enable_if_t<std::is_function_v<Fun>>>
            class TupleFunctions 
            {
            public:
                template <typename... Funs, typename = std::enable_if_t<sizeof...(Funs) <= DimRealSpace && std::is_function<typename templatesUtils::tuple<Funs...>::value_type>::value>>
                TupleFunctions(Funs... funs) :data{ static_cast<Fun>(funs)... }
                {
                    Dim = sizeof...(Funs);
                }
            private:
                Fun data[DimRealSpace];
                size_t Dim = 0;
            };
            
            template<typename T>
                class A
                {
                public:
                    using fun_t = T(*)(T);

                    template <T(*...Funs)(T)>//,typename T(*)(T)
                    A(Funs... funs)// : data{ static_cast<fun_t>(funs)... }
                    {
                        //decltype(Funs) a;
                    }
                    // ...
                private:
                    fun_t data[3];
                };*/
           
            template<typename T>
            T defectFunction(T x)
            {
                return T(0);
            }

            template<size_t size, typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size > 0) && (size < 4)>>
            class Curve
            {

            public:
                using fun_t = T(*)(T);

                template <typename Fun>
                Curve(Fun f1, Fun f2 = defectFunction, Fun f3 = defectFunction) : data{f1,f2,f3}
                {           
                }

                Curve(std::function< T(T) > f1, std::function< T(T) > f2 = [](T x) {return 0; }, std::function< T(T) > f3 = [](T x) {return 0; }) : data{ f1,f2,f3 }
                {
                }
                
                Curve(fun_t funs[DimRealSpace]) : data{ funs }
                {
                }

                Vector<size, T> Eval(T t)
                {
                    Vector<size, T> res(T(0.0));    
                    for (size_t i = 0; i < size; ++i)
                        res[i] = data[i](t);
                    return res;
                }

                /*t - point, n - number of der,h - step (error)*/
                Vector<size, T> Derivative(T t, size_t n, T h)
                {
                    Vector<size, T> res(Eval(t));
                    T sign = -1;

                    for (size_t i = 0; i < n; ++i, sign *= -1)
                    {
                        res += sign * static_cast<T>(C(n, i + 1)) * Eval(t + static_cast<T>(i + 1) * h);
                    }
                    sign *= -1;
                    return res * sign / std::pow(h, n);
                }

                Vector<size, T> Tangent(T t)
                {
                    Vector<size, T> res(T(0.0));
                    res = Derivative(t, 1, 0.001);

                    return res / res.Length();
                }

                T Curvature(T t) 
                {
                    Vector<3, T> _1der = Derivative(t, 1, 0.001);
                    return Cross(Derivative(t, 2, 0.001), _1der).Length() / pow(_1der.Length(), 3);
                }

                Vector<size, T> Norm(T t)
                {
                    Vector<size, T> _1der = Derivative(t, 1, 0.001);
                    Vector<size, T> _2der = Derivative(t, 2, 0.001);

                    return _2der / pow(_2der.Length(), 2) - (_1der * _2der / pow(_1der.Length(), 4)) * _1der;
                }

                Vector<3, T> Binorm(T t) 
                {
                    Vector<3, T> _1der = Derivative(t, 1, 0.001);
                    Vector<3, T> _2der = Derivative(t, 2, 0.001);
                    Vector<3, T> cr = Cross(_1der, _2der);
                    
                    return cr / cr.Length();
                }

                T CurvatureRadius(T t) 
                {
                    Vector<3, T> _1der = Derivative(t, 1, 0.001);
                    Vector<3, T> _2der = Derivative(t, 2, 0.001);

                    return pow(_1der.Length(), 3) / Cross(_1der, _2der).Length();
                }
                
                T Torsion(T t) 
                {
                    Vector<3, T> _1der = Derivative(t, 1, 0.001);
                    Vector<3, T> _2der = Derivative(t, 2, 0.001);
                    Vector<3, T> _3der = Derivative(t, 3, 0.001);
                    Vector<3, T> cr = Cross(_1der, _2der);

                    return cr * _3der / pow(cr.Length(), 2);
                }

            private:
                std::function< T(T) > data[DimRealSpace];
                //fun_t data[DimRealSpace];
                //std::initializer_list<fun_t> data{ [](T x) {return T(0); }, [](T x) {return T(0); }, [](T x) {return T(0); } };
            };

            /// @brief projection vector on plane
            /// @return projection vector lvec on plane
            /*template<size_t size, typename T>
            T proj(const Vector<size, T>& lvec, const Curve<size, T>& plane)
            {
                auto norm = plane.  rvec.Norm();
                return (lvec * normRVec) * normRVec;
            }*/

        } // namespace geometry
    } // namespace mathematics
} // namespace ads

#endif // __CURVE_HPP__