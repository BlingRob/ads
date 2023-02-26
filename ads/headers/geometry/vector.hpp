// \\\ file geometry.h 
// \\\ It's the most important section,
// \\\ because I am interesting computer graphics, geometry modeling and mechanics. :)
#pragma once
#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <type_traits>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <functional>
#include <memory>
#include "../mathematics.h"
#include "matrix.hpp"

namespace ads
{
    namespace mathematics
    {
        namespace geometry
        {
            const size_t DimRealSpace = 3;

            template<size_t size, typename T>
            class Matrix;

            template<size_t size, typename T>
            class Vector
            {
            public:

                template <typename... Scalars, typename = std::enable_if_t<sizeof...(Scalars) != 0 && sizeof...(Scalars) <= size>>
                Vector(Scalars... coords) : data{ static_cast<T>(coords)... }
                {
                }

                Vector()
                {
                    std::memset(data, 0, sizeof(T) * size);
                }

                template <size_t rsize, typename Type, typename = std::enable_if_t<std::is_arithmetic_v<Type> && rsize <= size>>
                Vector(const Vector<rsize, Type>& rvec)
                {
                    for (size_t i = 0; i < rsize; ++i)
                       data[i] = rvec[i];
                }

                template <typename Type, std::enable_if_t<std::is_arithmetic_v<Type>, bool> = true>
                Vector(Type* arr)
                {
                    std::memcpy(data, arr, sizeof(Type) * size);
                }

                Vector<size, T> operator +(const Vector<size, T>& vec) const
                {
                    Vector<size, T> tmp(T(0.0));
                    for (size_t i = 0; i < size; ++i)
                        tmp[i] = vec[i] + data[i];
                    return tmp;
                }

                Vector<size, T> operator -(const Vector<size, T>& vec) const
                {
                    Vector<size, T> tmp(T(0));
                    for (size_t i = 0; i < size; ++i)
                        tmp[i] = vec[i] - data[i];
                    return tmp;
                }

                //dot product
                T operator *(const Vector<size, T>& vec) const
                {
                    T res = T(0);
                    for (size_t i = 0; i < size; ++i)
                        res += data[i] * vec[i];
                    //std::inner_product(data, data + size, vec.ptr(), vec.ptr() + size, res);
                    return res;
                }

                template<typename Type = float,class = typename std::enable_if_t<std::is_arithmetic_v<Type>>>
                Vector<size, T> operator *(Type num) const
                {
                    Vector temp(*this);
                    for (size_t i = 0; i < size; ++i)
                        temp[i] *= num;
                    return temp;
                }

                template<typename Type = float, class = typename std::enable_if_t<std::is_arithmetic_v<Type>>>
                Vector<size, T> operator /(Type num) const
                {
                    Vector temp(*this);
                    for (size_t i = 0; i < size; ++i)
                        temp[i] /= num;
                    return temp;
                }

                template<typename Type = float, class = typename std::enable_if_t<std::is_arithmetic_v<Type>>>
                Vector<size, T>& operator /=(Type num)
                {
                    for (size_t i = 0; i < size; ++i)
                        data[i] /= num;
                    return *this;
                }

                template<typename Type = float, class = typename std::enable_if_t<std::is_arithmetic_v<Type>>>
                Vector<size, T>& operator *=(Type num)
                {
                    for (size_t i = 0; i < size; ++i)
                        data[i] *= num;
                    return *this;
                }

                Vector<size, T>& operator +=(const Vector<size, T>& vec)
                {
                    for (size_t i = 0; i < size; ++i)
                        data[i] += vec[i];
                    return *this;
                }

                Vector<size, T>& operator *=(const Vector<size, T>& vec)
                {
                    for (size_t i = 0; i < size; ++i)
                        data[i] *= vec[i];
                    return *this;
                }

                Vector<size, T>& operator =(const Vector<size, T>& vec)
                {
                    for (size_t i = 0; i < size; ++i)
                        data[i] = vec[i];
                    return *this;
                }

                template<size_t s, typename Type>
                friend Vector<s, Type> operator *(Type num, const Vector<s, Type>& vec);

                inline T& operator [](std::size_t index)
                {
                    return data[index];
                }

                inline const T& operator [](std::size_t index) const
                {
                    return data[index];
                }

                bool operator ==(const Vector<size, T>& vec) const
                {
                    for (size_t i = 0; i < size; ++i)
                        if(data[i] != vec[i])
                            return false;
                    return true;
                }

                Vector<size, T> slice(int32_t first, int32_t last)
                {
                    if (first > size || last > size || std::abs(first - last) > size)
                        throw(std::range_error("bad vector slice"));
                    else 
                    {
                        if (first < 0)
                            first += size;
                        if (last < 0)
                            last += size;

                        int32_t differenc = 1;
                        if (first > last)
                            differenc = -1;

                        Vector<size, T> res(T(0));
                        int32_t k = 0;
                        for (int32_t i = first; i != last; i += differenc)
                            res[k++] = data[i];
                        res[k] = data[last];

                        return res;
                    }
                }

                inline T* ptr() { return &data[0]; }
                inline const T* ptr() const { return &data[0]; }

                template<typename Type, typename = std::enable_if_t<std::is_arithmetic_v<Type>>>
                operator Vector<size, Type>()
                {
                    Vector<size, Type> res(Type(0));
                    for (size_t i = 0; i < size; ++i)
                        res[i] = static_cast<Type>(data[i]);
                    return res;
                }

                T length() const 
                {
                    const Vector<size, T>& THIS = *this;
                    return std::sqrt(THIS * THIS);
                }

            private:

                T data[size]{ T() };
            };

            //cross product 
            template <typename T = float, class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
            Vector<DimRealSpace, T> cross(const Vector<DimRealSpace, T>& vec1, const Vector<DimRealSpace, T>& vec2)
            {
               
                return Vector<3, T>(vec2[1] * vec1[2] - vec2[2] * vec1[1],
                                    vec2[2] * vec1[0] - vec2[0] * vec1[2],
                                    vec2[0] * vec1[1] - vec2[1] * vec1[0]);
            }

            template<size_t size, typename T>
            Vector<size, T> operator *(T num, const Vector<size, T>& vec)
            {
                return vec * num;
            }

            template<size_t size, typename T>
            bool isEqual(const Vector<size, T>& lvec, const Vector<size, T>& rvec, T accuracy)
            {
                Vector<size, T> res = lvec - rvec;
                uint64_t multiplier = static_cast<uint64_t>(1.0 / accuracy);
                res *=  multiplier;

                return abs(res[0]) <= multiplier && abs(res[1]) <= multiplier && abs(res[2]) <= multiplier;
            }

        } // namespace geometry
    } // namespace mathematics
} // namespace ads

#endif // __VECTOR_HPP__