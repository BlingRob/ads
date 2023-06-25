/// @file vector.hpp 
/// @brief Definition vector class

#pragma once
#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <type_traits>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <functional>
#include <memory>
#include <math.h>
#include "../mathematics.h"
#include "matrix.hpp"

namespace ads
{
    namespace mathematics
    {
        namespace geometry
        {
            const size_t DimRealSpace = 3;

            /// @brief For operation with matrix
            template<size_t size, typename T>
            class Matrix;

            /// @brief Class definition
            /// @tparam T type of elements
            /// @tparam size length
            template<size_t size, typename T>
            class Vector
            {
            public:
                /// @brief Constructor
                /// @tparam ...Scalars types of elements 
                /// @tparam  condition 
                /// @param ...coords value of elemnts
                template <typename... Scalars, typename = std::enable_if_t<(sizeof...(Scalars) > 0) && (sizeof...(Scalars) <= size)>>
                Vector(Scalars... coords) : data_{ static_cast<T>(coords)... }
                {
                }

                Vector()
                {
                    std::memset(data_, 0, sizeof(T) * size);
                }

                template <size_t rsize, typename Type, typename = std::enable_if_t<std::is_arithmetic_v<Type> && rsize <= size>>
                Vector(const Vector<rsize, Type>& rvec)
                {
                    std::memcpy(data_, rvec.ptr(), sizeof(Type) * rsize);
                }

                template <typename Type, std::enable_if_t<std::is_arithmetic_v<Type>, bool> = true>
                Vector(Type* arr)
                {
                    std::memcpy(data_, arr, sizeof(Type) * size);
                }

                Vector<size, T> operator +(const Vector<size, T>& vec) const
                {
                    Vector<size, T> tmp(*this);

                    for (size_t i = 0; i < size; ++i)
                        tmp[i] += vec[i];
                    return tmp;
                }

                Vector<size, T> operator -(const Vector<size, T>& vec) const
                {
                    Vector<size, T> tmp(*this);

                    for (size_t i = 0; i < size; ++i)
                        tmp[i] -= vec[i];
                    return tmp;
                }

                //dot product
                T operator *(const Vector<size, T>& vec) const
                {
                    return std::inner_product(data_, data_ + size, vec.ptr(), T(0));
                }

                template<typename Type = float, class = typename std::enable_if_t<std::is_arithmetic_v<Type>>>
                Vector<size, T> operator *(Type num) const
                {
                    Vector temp(*this);
                    std::for_each(temp.data_, temp.data_ + size, [&num](T &x) { x *= num; });
                    return temp;
                }

                template<typename Type = float, class = typename std::enable_if_t<std::is_arithmetic_v<Type>>>
                Vector<size, T> operator /(Type num) const
                {
                    Vector temp(*this);
                    std::for_each(temp.data_, temp.data_ + size, [&num](T &x) { x /= num; });
                    return temp;
                }

                template<typename Type = float, class = typename std::enable_if_t<std::is_arithmetic_v<Type>>>
                Vector<size, T>& operator /=(Type num)
                {
                    std::for_each(data_, data_ + size, [&num](T &x) { x /= num; });
                    return *this;
                }

                template<typename Type = float, class = typename std::enable_if_t<std::is_arithmetic_v<Type>>>
                Vector<size, T>& operator *=(Type num)
                {
                    std::for_each(data_, data_ + size, [&num](T &x) { x *= num; });
                    return *this;
                }

                Vector<size, T>& operator +=(const Vector<size, T>& vec)
                {
                    for (size_t i = 0; i < size; ++i)
                        data_[i] += vec[i];
                    return *this;
                }

                Vector<size, T>& operator *=(const Vector<size, T>& vec)
                {
                    for (size_t i = 0; i < size; ++i)
                        data_[i] *= vec[i];
                    return *this;
                }

                Vector<size, T>& operator =(const Vector<size, T>& vec)
                {
                    for (size_t i = 0; i < size; ++i)
                        data_[i] = vec[i];
                    return *this;
                }

                template<size_t s, typename Type>
                friend Vector<s, Type> operator *(Type num, const Vector<s, Type>& vec);

                inline T& operator [](std::size_t index)
                {
                    return data_[index];
                }

                inline const T& operator [](std::size_t index) const
                {
                    return data_[index];
                }

                bool operator ==(const Vector<size, T>& vec) const
                {
                    for (size_t i = 0; i < size; ++i)
                        if(data_[i] != vec[i])
                            return false;
                    return true;
                }

                template<int32_t first, int32_t last, class = typename std::enable_if_t<(first < last) && (first < size) && (last < size + 1)>>
                Vector<last - first, T> Slice() const
                {
                    Vector<last - first, T> res(T(0));
                    for (int32_t i = first, k = 0; i < last; ++i, ++k)
                        res[k] = data_[i];

                    return res;
                }

                inline T* ptr() { return &data_[0]; }
                inline const T* ptr() const { return &data_[0]; }

                template<typename Type, typename = std::enable_if_t<std::is_arithmetic_v<Type>>>
                operator Vector<size, Type>() const
                {
                    Vector<size, Type> res(Type(0));
                    for (size_t i = 0; i < size; ++i)
                        res[i] = static_cast<Type>(data_[i]);
                    return res;
                }

                T Length() const 
                {
                    const Vector<size, T>& THIS = *this;
                    return std::sqrt(THIS * THIS);
                }

                /// @brief normalizing vector
                /// @return normalized vector
                Vector<size, T> Norm() const
                {
                    return *this / Length();
                }

            private:

                T data_[size]{ T() };
            };

            /// @brief cross product 
            template <typename T = float, class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
            Vector<DimRealSpace, T> Cross(const Vector<DimRealSpace, T>& vec1, const Vector<DimRealSpace, T>& vec2)
            {
               
                return Vector<3, T>(vec2[2] * vec1[1] - vec2[1] * vec1[2],
                                    vec1[2] * vec2[0] - vec1[0] * vec2[2],
                                    vec2[1] * vec1[0] - vec2[0] * vec1[1]);
            }

            template<size_t size, typename T>
            Vector<size, T> operator *(T num, const Vector<size, T>& vec)
            {
                return vec * num;
            }

            /// @brief Equlity two vectors
            template<size_t size, typename T>
            bool isEqual(const Vector<size, T>& lvec, const Vector<size, T>& rvec, T accuracy)
            {
                Vector<size, T> res = lvec - rvec;
                //uint64_t multiplier = static_cast<uint64_t>(1.0 / accuracy);
                //res *=  multiplier;

                return abs(res[0]) <= accuracy && abs(res[1]) <= accuracy && abs(res[2]) <= accuracy;
            }

            /// @brief cos between two vectors
            template<size_t size, typename T>
            T Cos(const Vector<size, T>& lvec, const Vector<size, T>& rvec)
            {
                return (lvec * rvec) / (lvec.Length() * rvec.Length());
            }

            /// @brief check two vectors is orthogonal
            template<size_t size, typename T>
            bool IsOrth(const Vector<size, T>& lvec, const Vector<size, T>& rvec, T accuracy = T(0.001))
            {
                return (lvec * rvec) < accuracy;
            }

            /// @brief check two vectors parallel
            /// @return 1 if parallel, -1 if antiparallel
            template<size_t size, typename T>
            int16_t IsParallel(const Vector<size, T>& lvec, const Vector<size, T>& rvec)
            {
                return Cos(lvec, rvec);
            }

            /// @brief projection one vector to another
            /// @return projection vector lvec on rvec
            template<size_t size, typename T>
            T Proj(const Vector<size, T>& lvec, const Vector<size, T>& rvec)
            {
                auto normRVec = rvec.Norm();
                return (lvec * normRVec) * normRVec;
            }

        } // namespace geometry
    } // namespace mathematics
} // namespace ads

#endif // __VECTOR_HPP__