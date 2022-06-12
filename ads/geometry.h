#pragma once
#include <type_traits>
#include <algorithm>
#include <numeric>
#include <cstring>

namespace ads
{
    namespace mathematics
    {
        namespace geometry
        {
            template<typename T = float, size_t size = 2, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
            class matrix
            {
            public:

            private:
                T data[size][size];
            };

            template<typename T, size_t size, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
            class vector
            {
            public:
                template <typename... Scalars,typename = std::enable_if_t<sizeof...(Scalars) <= size && std::is_arithmetic<typename templatesUtils::tuple<Scalars...>::value_type>::value>>
                vector(Scalars... coords) :data{ static_cast<T>(coords)... }
                {
                }

                template <typename type, std::enable_if_t<std::is_arithmetic_v<type>,bool> = true >
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

                template<typename type = float,class = typename std::enable_if_t<std::is_arithmetic_v<type>>>
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

                inline T* ptr() { return data; }

            private:

                T data[size]{ T() };
            };

                //cross product 
                template <typename T = float,class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
                vector<T, 3> cross(const vector<T, 3>& vec1,const vector<T, 3>& vec2)
                {
                    //statis_assert(std::enable_if<static_cast<bool>(3 == size)::value,"Don't use cross product!");
                    return vector<T, 3>(vec2[1] * vec1[2] - vec2[2] * vec1[1],
                        vec2[2] * vec1[0] - vec2[0] * vec1[2],
                        vec2[0] * vec1[1] - vec2[1] * vec1[0]);
                }

        }
    }
}
