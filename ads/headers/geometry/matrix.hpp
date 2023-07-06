/// @file matrix.hpp 
/// @brief Definition matrix class

#pragma once
#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include "../mathematics.h"
#include "../core.h"
#include "vector.hpp"

#include <type_traits>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <functional>
#include <memory>
#include <iterator>
#include <utility>

namespace ads
{
    namespace mathematics
    {
        namespace geometry
        {
            template<size_t size, typename T>
            class Vector;

            template<size_t size, typename T = float>
            class Matrix
            {
            public:

                /// @brief Default constructor
                Matrix()
                {
                    for (size_t i = 0; i < size; ++i)
                        memset(&data_[i], 0, sizeof(T) * size);
                }

                /// @brief Ones constructor
                /// @tparam Type  
                /// @param num diagonal number
                template<typename Type, typename = std::enable_if_t<std::is_arithmetic_v<Type>>>
                Matrix(Type num = T(0)) : data_{T(0.0)}
                {
                    for (size_t i = 0; i < size; ++i)
                        data_[i][i] = num;
                }

                template<typename Type, typename = std::enable_if_t<std::is_arithmetic_v<Type>>>
                Matrix(std::initializer_list<std::initializer_list<Type>> mat) : data_{T(0.0)}
                {
                    if(mat.size() > size)
                        throw(std::runtime_error("Too large initializer list"));
                    size_t i = 0;
                    for (const auto& vec : mat)
                    {
                        if(vec.size() > size)
                            throw(std::runtime_error("Too large initializer list"));
                        std::copy(vec.begin(), vec.end(), data_[i]);
                        ++i;
                    }
                }

                Matrix<size, T> operator*(const Matrix<size, T>& r)
                {
                    Matrix<size, T> result(static_cast<T>(0.0));
                    for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                            for (size_t k = 0; k < size; ++k)
                                result[i][j] += data_[i][k] * r[k][j];
                    return result;
                }

                Matrix<size, T> operator-(const Matrix<size, T>& r) 
                {
                    Matrix<size, T> result(static_cast<T>(0.0));
                    for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                            result[i][j] = data_[i][j] - r[i][j];
                    return result;
                }

                Matrix<size, T> operator+(const Matrix<size, T>& r)
                {
                    Matrix<size, T> result(static_cast<T>(0.0));
                    for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                            result[i][j] = data_[i][j] + r[i][j];
                    return result;
                }

                const T* operator[](size_t row) const 
                {
                    return data_[row];
                }

                T* operator[](size_t row)
                {
                    return data_[row];
                }

                template<typename Type = float, typename = std::enable_if_t<std::is_arithmetic_v<Type>>>
                Vector<size, Type> operator*(const Vector<size, Type>& vec)
                {
                    Vector<size, Type> res(T(0.0));
                    for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                            res[i] += data_[i][j] * vec[j];
                    return res;
                }

            private:
                T data_[size][size];
            };


            /// @brief Construct diagonal matrix
            /// @return Matrix
            template <typename... Scalars, typename T = typename templatesUtils::tuple<Scalars...>::value_type, typename = std::enable_if_t<(sizeof...(Scalars) > 0)>>
            Matrix<sizeof...(Scalars), T> Diag(Scalars... coords)
            {
                Vector<sizeof...(Scalars), T> vec(static_cast<T>(coords)...); 
                Matrix<sizeof...(Scalars), T> res;
                    
                for(size_t i = 0; i < sizeof...(Scalars); ++i)
                    res[i][i] = vec[i];
                    
                return res;
            }
            
        } // namespace geometry
    } // namespace mathematics
} // namespace ads

#endif // __MATRIX_HPP__