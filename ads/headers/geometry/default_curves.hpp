/// @file default_curves.hpp
/// @brief define default parametric curves

#pragma once
#ifndef __DEFAULT_CURVES_HPP__
#define __DEFAULT_CURVES_HPP__

#include "vector.hpp"
#include "curve.hpp"
#include <type_traits>

namespace ads
{
    namespace mathematics
    {
        namespace geometry
        {
            template<size_t size, typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size == 2 || size == 3)>>
            class Ellipse : public Curve<size, T>
            {
            public:
                Ellipse(T a, T b, Vector<size, T> center = Vector<size, T>(0)) : Curve<size, T>(
                    [=](T t) 
                    {
                        return a * std::cos(t) + center[0]; 
                    }, 
                    [=](T t) 
                    {
                        return b * std::sin(t) + center[1]; 
                    },
                    [=](T t) {return center[2]; }) {}
            };
    
            template<size_t size, typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size == 2 || size == 3)>>
            class Circle : public Ellipse<size, T>
            {
            public:
                Circle(T radius, Vector<size, T> center = Vector<size, T>(0)) : Ellipse<size, T>(radius, radius, center) {}
            };

            template<size_t size, typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size == 2 || size == 3)>>
            class Hyperbola : Curve<size, T>
            {
            public:
                Hyperbola(T a,T b, Vector<size, T> center = Vector<size, T>(0)) : Curve<size, T>(
                    [&](T t) 
                    {
                        return a * std::cosh(t) + center[0]; 
                    }, 
                    [&](T t) 
                    {
                        return b * std::sinh(t) + center[1]; 
                    }, 
                    [&](T t) 
                    {
                        return center[2];
                    }){}
            };

            template<size_t size, typename T,  class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size == 2 || size == 3)>>
            class Parabola : Curve<size, T>
            {
            public:
                Parabola(T focus, Vector<size, T> center = Vector<size, T>(0)) : Curve<size, T>(
                    [&](T t) 
                    {
                        return focus * t * t + center[0];
                    }, 
                    [&](T t) 
                    {
                        return 2 * focus * t + center[1]; 
                    },
                    [&](T t) 
                    {
                        return center[2];
                    }) {}
            };

            template<typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
            class Spiral : Curve<3, T>
            {
            public:
                Spiral(T radius, T step, Vector<3, T> center = Vector<3, T>(0)) : Curve<3, T>(
                        [&](T t) 
                            {
                                return radius * std::cos(t) + center[0]; 
                            }, 
                        [&](T t)
                            {
                                return radius * std::sin(t) + center[1];
                            },
                        [&](T t) 
                            {
                                return step * t/(2.0 * Pi) + center[2]; 
                            }) {}
            };
        } // namespace geometry
    } // namespace mathematics
} // namespace ads

#endif // __DEFAULT_CURVES_HPP__