/// @file matrix.hpp 
/// @brief Definition matrix class

#pragma once
#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <type_traits>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <functional>
#include <memory>
#include <iterator>
#include <utility>
#include "../mathematics.h"
#include "vector.hpp"

namespace ads
{
    namespace mathematics
    {
        namespace geometry
        {
            template<size_t size, typename T>
            class Vector;

            template<size_t size, typename T>
            class Matrix
            {
            public:
                /// @brief Ones constructor
                /// @tparam Type  
                /// @param num diagonal number
                template<typename Type, typename = std::enable_if_t<std::is_arithmetic_v<Type>>>
                Matrix(Type num = T(1)) : data{T(0.0)}
                {
                    for (size_t i = 0; i < size; ++i)
                        data[i][i] = num;
                }

                template<typename Type, typename = std::enable_if_t<std::is_arithmetic_v<Type>>>
                Matrix(std::initializer_list<std::initializer_list<Type>> mat) : data{T(0.0)}
                {
                    if(mat.size() > size)
                        throw(std::runtime_error("Too large initializer list"));
                    size_t i = 0;
                    for (const auto& vec : mat)
                    {
                        if(vec.size() > size)
                            throw(std::runtime_error("Too large initializer list"));
                        std::copy(vec.begin(), vec.end(), data[i]);
                        ++i;
                    }
                }

                Matrix<size, T> operator*(const Matrix<size, T>& r)
                {
                    Matrix<size, T> result(static_cast<T>(0.0));
                    for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                            for (size_t k = 0; k < size; ++k)
                                result[i][j] += data[i][k] * r[k][j];
                    return result;
                }

                Matrix<size, T> operator-(const Matrix<size, T>& r) 
                {
                    Matrix<size, T> result(static_cast<T>(0.0));
                    for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                            result[i][j] = data[i][j] - r[i][j];
                    return result;
                }

                Matrix<size, T> operator+(const Matrix<size, T>& r)
                {
                    Matrix<size, T> result(static_cast<T>(0.0));
                    for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                            result[i][j] = data[i][j] + r[i][j];
                    return result;
                }

                const T* operator[](size_t row) const 
                {
                    return data[row];
                }

                T* operator[](size_t row)
                {
                    return data[row];
                }

                template<typename Type = float, typename = std::enable_if_t<std::is_arithmetic_v<Type>>>
                Vector<size, Type> operator*(const Vector<size, Type>& vec)
                {
                    Vector<size, Type> res(T(0.0));
                    for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                            res[i] += data[i][j] * vec[j];
                    return res;
                }

            private:
                T data[size][size];
            };
        } // namespace geometry
    } // namespace mathematics
} // namespace ads

#endif // __MATRIX_HPP__