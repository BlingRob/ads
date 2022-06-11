#pragma once
#include <type_traits>
#include <algorithm>
#include <numeric>

namespace ads
{
    namespace mathematics
    {
        namespace geometry
        {
            template<size_t var1, size_t var2>
            struct equal
            {
                static const bool value = var1 == var2;
            };

            template<size_t var1, size_t var2>
            struct equal_or_less
            {
                static const bool value = var1 <= var2;
            };

            template<typename T = float, size_t size = 2, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
            class matrix
            {
            public:

            private:
                T data[size][size];
            };

            template<typename T = float, size_t size = 2, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
            class vector
            {
            public:
                template <typename... Scalars, typename = std::enable_if_t<sizeof...(Scalars) <= size && std::is_arithmetic_v<typename templatesUtils::tuple<Scalars...>::value_type>>>
                vector(Scalars... coords) :data{ static_cast<T>(coords)... }
                {
                }

                template <typename type, typename = std::enable_if_t<std::is_arithmetic_v<type>> >
                vector(type* arr)
                {
                    std::memcpy(data, arr, sizeof(type) * size);
                }

                /*template <typename type, size_t N, typename = std::enable_if_t<std::is_arithmetic_v<type> && N != 0> >
                explicit vector(type(&arr)[N])
                {
                    std::memcpy(data, arr, sizeof(type) * size);
                }*/

                vector<T, size> operator +(const vector<T, size>& vec)
                {
                    vector<T, size> tmp;
                    for (size_t i = 0; i < size; ++i)
                        ptr[i] = vec[i] + (*this)[i];
                    return tmp;
                }

                vector<T, size> operator -(const vector<T, size>& vec) 
                {

                }
                //dot product
                T operator *(const vector<T, size>& vec) 
                {
                    T res = T();
                    std::inner_product(data, data + size, vec.ptr(), vec.ptr() + size, res);
                    return res;
                }
                //cross product 
                template <typename = std::enable_if_t<equal<size, 3>::value> >
                vector<T, size> operator ^(const vector<T, size>& vec)
                {
                    return vector<T, size>(data[1] * vec.data[2] - data[2] * vec.data[1],
                        data[2] * vec.data[0] - data[0] * vec.data[2],
                        data[0] * vec.data[1] - data[1] * vec.data[0]);
                }

                template<typename type = float, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
                vector<T, size> operator*(type num)
                {
                    vector temp(*this);
                    for (size_t i = 0; i < size; ++i)
                        temp[i] *= num;
                    return temp;
                }

                inline T& operator[](std::size_t index)
                {
                    return data[index];
                }

                inline T& x() { return data[0]; }
                template <typename = std::enable_if_t<static_cast<bool>(2 <= size)>>
                inline T& y() { return data[1]; }
                template <typename = std::enable_if_t<static_cast<bool>(3 <= size)>>
                inline T& z() { return data[2]; }
                template <typename = std::enable_if_t<static_cast<bool>(4 <= size)>>
                inline T& w() { return data[3]; }

                inline T* ptr() { return data; }

            private:

                T data[size]{ T() };
            };

            namespace calculus
            {

            }
        }
    }
}
