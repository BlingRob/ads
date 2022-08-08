#pragma once
#include <type_traits>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <functional>
#include <memory>
#include <iterator>
#include <utility>
#include "mathematics.h"

namespace ads
{
    namespace mathematics
    {
        namespace geometry
        {
            const size_t DimRealSpace = 3;

            template<typename T, size_t size, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
            class vector;

            template<typename T = float, size_t size = 2, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
            class matrix
            {
            public:
                template<typename type, typename = std::enable_if_t<std::is_arithmetic<type>::value>>
                matrix(type num) :data{T(0.0)}
                {
                    for (size_t i = 0; i < size; ++i)
                        data[i][i] = num;
                }

                template<typename type, typename = std::enable_if_t<std::is_arithmetic<type>::value>>
                matrix(std::initializer_list<std::initializer_list<type>> mat)
                {
                    size_t i = 0;
                    for (const auto& vec : mat)
                        std::copy(vec.begin(), vec.end(), data[i]), ++i;
                }

                matrix<T,size> operator*(const matrix<T, size>& r)
                {
                    matrix<T, size> result(static_cast<T>(0.0));
                    for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                            for (size_t k = 0; k < size; ++k)
                                result[i][j] += data[i][k] * r[k][j];
                    return result;
                }

                matrix<T, size> operator-(const matrix<T, size>& r) 
                {
                    matrix<T, size> result(static_cast<T>(0.0));
                    for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                            result[i][j] = data[i][j] - r[i][j];
                    return result;
                }

                matrix<T, size> operator+(const matrix<T, size>& r)
                {
                    matrix<T, size> result(static_cast<T>(0.0));
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

                template<typename type = float, class = typename std::enable_if_t<std::is_arithmetic_v<type>>>
                vector<type, size> operator*(const vector<type, size>& vec)
                {
                    vector<type, size> res(T(0.0));
                    for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                            res[i] += data[i][j] * vec[j];
                    return res;
                }

            private:
                T data[size][size];
            };

            template<typename T, size_t size, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
            class vector
            {
            public:

                template <typename... Scalars,typename = std::enable_if_t<sizeof...(Scalars) <= size && std::is_arithmetic<typename templatesUtils::tuple<Scalars...>::value_type>::value>>
                explicit vector(Scalars... coords):data{ static_cast<T>(coords)... }
                {
                }

                template <typename type, std::enable_if_t<std::is_arithmetic_v<type>,bool> = true>
                vector(type* arr)
                {
                    std::memcpy(data, arr, sizeof(type) * size);
                }

                template <typename type, std::enable_if_t<std::is_arithmetic_v<type>, bool> = true>
                vector()
                {
                    std::memset(data, 0, sizeof(type) * size);
                }

                vector<T, size> operator +(const vector<T, size>& vec)
                {
                    vector<T, size> tmp(T(0.0));
                    for (size_t i = 0; i < size; ++i)
                        tmp[i] = vec[i] + data[i];
                    return tmp;
                }

                vector<T, size> operator -(const vector<T, size>& vec) 
                {
                    vector<T, size> tmp(T(0));
                    for (size_t i = 0; i < size; ++i)
                        tmp[i] = vec[i] - data[i];
                    return tmp;
                }

                //dot product
                T operator *(const vector<T, size>& vec) const
                {
                    T res = T(0);
                    for (size_t i = 0; i < size; ++i)
                        res += data[i] * vec[i];
                    //std::inner_product(data, data + size, vec.ptr(), vec.ptr() + size, res);
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

                template<typename type = float, class = typename std::enable_if_t<std::is_arithmetic_v<type>>>
                vector<T, size> operator/(type num)
                {
                    vector temp(*this);
                    for (size_t i = 0; i < size; ++i)
                        temp[i] /= num;
                    return temp;
                }

                vector<T, size>& operator +=(vector<T, size> vec)
                {
                    for (size_t i = 0; i < size; ++i)
                        data[i] += vec[i];
                    return *this;
                }

                template<size_t size, class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
                friend vector<T, size> operator*(T num, vector<T, size> vec);

                inline T& operator[](std::size_t index)
                {
                    return data[index];
                }

                inline const T& operator[](std::size_t index) const
                {
                    return data[index];
                }

                inline T* ptr() { return data; }
                inline T* ptr() const { return data; }

                template<typename type, class = typename std::enable_if_t<std::is_arithmetic_v<type>>>
                operator vector<type, size>()
                {
                    vector<type, size> res(type(0));
                    for (size_t i = 0; i < size; ++i)
                        res[i] = static_cast<type>(data[i]);
                    return res;
                }

                T length() const 
                {
                    const vector<T, size>& THIS = *this;
                    return std::sqrt(THIS * THIS);
                }

            private:

                T data[size]{ T() };
            };

            //cross product 
            template <typename T = float,class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
            vector<T, DimRealSpace> cross(const vector<T, DimRealSpace>& vec1,const vector<T, DimRealSpace>& vec2)
            {
               
                return vector<T, 3>(vec2[1] * vec1[2] - vec2[2] * vec1[1],
                                    vec2[2] * vec1[0] - vec2[0] * vec1[2],
                                    vec2[0] * vec1[1] - vec2[1] * vec1[0]);
            }

            template<typename T, size_t size, class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
            vector<T, size> operator*(T num, vector<T, size> vec)
            {
                return vec * num;
            }

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

            template<typename T, size_t size, class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size > 0) && (size < 5)>>
            class curve
            {

            public:
                using fun_t = T(*)(T);

                template <typename Fun>
                curve(Fun f1, Fun f2 = defectFunction, Fun f3 = defectFunction):data{f1,f2,f3}
                {           
                }

                curve(std::function< T(T) > f1, std::function< T(T) > f2 = [](T x) {return 0; }, std::function< T(T) > f3 = [](T x) {return 0; }) :data{ f1,f2,f3 }
                {
                }
                
                curve(fun_t funs[DimRealSpace]) : data{ funs }
                {
                }

                vector<T, size + 1> eval(T t)
                {
                    ads::mathematics::geometry::vector<T, size> res(T(0.0));
                    res[0] = t;
                    for (size_t i = 1;i < size;++i)
                        res[i] = data[i](t);
                    return res;
                }

                /*t - point, n - number of der,h - step (error)*/
                vector<T, size + 1> derivative(T t,size_t n,T h)
                {
                    vector<T, size + 1> res(eval(t));
                    T sign = -1;

                    for (size_t i = 1; i <= n; ++i,sign *= -1) 
                        res += sign * static_cast<T>(C(n, i)) * eval(t + static_cast<T>(i) * h);
                    
                    sign *= -1;
                    res *= sign / pow(h, n);
                    res[0] = t;

                    return res;
                }

                vector<T, size> tangent(T t)
                {
                    vector<T, size> res(T(0.0));
                    res = derivative(t, 1, 0.001);
                    return res / res.length();
                }

                T curvature(T t) 
                {
                    vector<T, 3> _1der = derivative(t, 1, 0.001);
                    return cross(derivative(t, 2, 0.001), _1der).length() / pow(_1der.length(), 3);
                }

                vector<T, size> norm(T t)
                {
                    vector<T, 3> _1der = derivative(t, 1, 0.001);
                    vector<T, 3> _2der = derivative(t, 2, 0.001);

                    return _2der / pow(_2der.length(), 2) - (_1der * _2der / pow(_1der.length(),4)) * _1der;
                }

                vector<T, size> binorm(T t) 
                {
                    vector<T, 3> _1der = derivative(t, 1, 0.001);
                    vector<T, 3> _2der = derivative(t, 2, 0.001);
                    vector<T, 3> cr = cross(_1der, _2der);


                    return cr / cr.length();
                }

                T curvatureRadius(T t) 
                {
                    vector<T, 3> _1der = derivative(t, 1, 0.001);
                    vector<T, 3> _2der = derivative(t, 2, 0.001);

                    return pow(_1der.length(), 3) / cross(_1der, _2der).length();
                }
                
                T torsion(T t) 
                {
                    vector<T, 3> _1der = derivative(t, 1, 0.001);
                    vector<T, 3> _2der = derivative(t, 2, 0.001);
                    vector<T, 3> _3der = derivative(t, 3, 0.001);
                    vector<T, 3> cr = cross(_1der, _2der);

                    return cr * _3der / pow(cr.length(), 2);
                }

            private:
                std::function< T(T) > data[DimRealSpace];
                //fun_t data[DimRealSpace];
                //std::initializer_list<fun_t> data{ [](T x) {return T(0); }, [](T x) {return T(0); }, [](T x) {return T(0); } };
            };

            template<typename T,size_t size, class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size == 2 || size == 3)>>
            class ellipse:public curve<T, size>
            {
            public:
                ellipse(T a, T b, vector<T, size> center = vector<T, size>(0)):curve(
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
    
            template<typename T, size_t size, class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size == 2 || size == 3)>>
            class circle :public ellipse<T, size>
            {
            public:
                circle(T radius, vector<T, size> center = vector<T, size>(0)) :ellipse(radius, radius, center) {}
            };

            template<typename T, size_t size, class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size == 2 || size == 3)>>
            class hyperbola:curve<T,size>
            {
            public:
                hyperbola(T a,T b, vector<T, size> center = vector<T, size>(0)):curve([&](T t) {return a * std::cosh(t) + center[0]; }, [&](T t) {return b * std::sinh(t) + center[1]; }, [&](T t) {return center[2]; }){}
            };

            template<typename T, size_t size, class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size == 2 || size == 3)>>
            class parabola:curve<T, size>
            {
            public:
                parabola(T focus, vector<T, size> center = vector<T, size>(0)):curve([&](T t) {return focus * t * t + center[0]; }, [&](T t) {return 2 * focus * t + center[1]; }, [&](T t) {return center[2]; }) {}
            };

            template<typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
            class spiral:curve<T, 3>
            {
            public:
                spiral(T radius,T step, vector<T, 3> center = vector<T, 3>(0)):curve([&](T t) {return radius * std::cos(t) + center[0]; }, [&](T t) {return radius * std::sin(t) + center[1]; }, [&](T t) {return step * t/(2 * Pi) + center[2]; }) {}
            };


            template<typename T, size_t size, class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size > 1) && (size < 4)>>
            class points 
            {
            public:

                points(const std::vector<vector<T, size>>& ps) :data(ps) {}
                points(std::vector<vector<T, size>>&& ps) :data(std::move(ps)) {}
                points(std::initializer_list<vector<T, size>> ps) :data(ps) {}

                void addpoint(vector<T, size> point) 
                {
                    data.push_back(point);
                }

            private:
                std::vector<vector<T, size>> data;
            };

            template<typename T,template <typename... Args> class Container, typename... Types>
            curve<T, 2> LagrangeSplain(const Container<vector<T,2>,Types...>& points)
            {
                return curve<T,2>([](T x) {return x; }, [=](T y)
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
            curve<T, 2> NewtonSplain(const Container<vector<T, 2>, Types...>& points) 
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

               return curve<T, 2>([](T x) {return x; }, [ACoefs = std::move(ACoefs),&points](T y) mutable
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
        

           }
    }
}
