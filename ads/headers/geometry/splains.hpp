
#pragma once
#ifndef __SPLAINS_HPP__
#define __SPLAINS_HPP__

#include "vector.hpp"
#include "curve.hpp"

namespace ads
{
    namespace mathematics
    {
        namespace geometry
        {
            template<typename T,template <typename... Args> class Container, typename... Types>
            Curve<2, T> LagrangeSplain(const Container<Vector<2, T>,Types...>& points)
            {
                return Curve<2,T>([](T x) {return x; }, [=](T y)
                    {
                        T res = T(0);
                        for (const auto& p : points) 
                        {
                            T tmp = T(p[1]);
                            for (const auto& p2 : points)
                                if(p[0] != p2[0])
                                    tmp *= (y - p2[0]) / (p[0] - p2[0]);
                            res += tmp;
                        }
                        return res;
                    });
            }

            template<typename T, template <typename... Args> class Container, typename... Types>
            Curve<2, T> NewtonSplain(const Container<Vector<2, T>, Types...>& points) 
            {
               std::shared_ptr<T[]> ACoefs(new T[points.size()]);

               size_t i = 0, j = 0;
               for (const auto& point1 : points)
               {
                   ACoefs[i] = point1[1];
                   T acc = T(1);
                   for (const auto& point2 : points)
                   {
                       if (i <= j)
                           break;

                       ACoefs[i] -= ACoefs[j] * acc;
                       acc *= point1[0] - point2[0];

                       ++j;
                   }

                   ACoefs[i] /= acc;

                   ++i;
                   j = 0;
               }

               return Curve<2, T>([](T x) {return x; }, [ACoefs = std::move(ACoefs), points](T y) mutable
                   {
                       T res = T(ACoefs[0]);
                       
                       T acc = T(1);
                       for (size_t i = 1; i < points.size(); ++i) 
                       {
                           acc *= y - (*std::next(std::begin(points),i - 1))[0];
                           res += ACoefs[i] * acc;
                       }

                       return res;
                   });
            }
        
            template<typename T, template <typename... Args> class Container, typename... Types>
            Curve<2, T> ErmitSplain(const Container<Vector<2, T>, Types...>& points) 
            {
                
            }

            template<typename T, template <typename... Args> class Container, typename... Types>
            Curve<2, T> BazieSplain(const Container<Vector<2, T>, Types...>& points)
            {
                std::shared_ptr<T[]> Bi(new T[points.size()]);
                T N = points.size();
                //Newton binom
                Bi[0] = 1;
                for (size_t i = 1; i < points.size(); ++i)
                    Bi[i] = Bi[i - 1] * (N + 1 - i) / i;

                return Curve<2, T>([](T x) {return x; }, [Bi = std::move(Bi), points](T y) mutable
                {
                    T res(T(0));

                    size_t i = 0;
                    for (const auto& point : points)
                        res += Bi[i++] * pow(point[0], i) * pow(1 - point[0], points.size() - i) * point[1];

                    return res;
                });
            }
        } // namespace geometry
    } // namespace mathematics
} // namespace ads

#endif // __SPLAINS_HPP__