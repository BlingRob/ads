// \\\ file geometry.h 
// \\\ It's the most important section,
// \\\ because I am interesting computer graphics, geometry modeling and mechanics. :)
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

            template<size_t size, typename T>
            class Vector;

            template<typename T = float, size_t size = 2, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
            class Matrix
            {
            public:
                template<typename type, typename = std::enable_if_t<std::is_arithmetic<type>::value>>
                Matrix(type num) :data{T(0.0)}
                {
                    for (size_t i = 0; i < size; ++i)
                        data[i][i] = num;
                }

                template<typename type, typename = std::enable_if_t<std::is_arithmetic<type>::value>>
                Matrix(std::initializer_list<std::initializer_list<type>> mat)
                {
                    size_t i = 0;
                    for (const auto& vec : mat)
                        std::copy(vec.begin(), vec.end(), data[i]), ++i;
                }

                Matrix<T,size> operator*(const Matrix<T, size>& r)
                {
                    Matrix<T, size> result(static_cast<T>(0.0));
                    for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                            for (size_t k = 0; k < size; ++k)
                                result[i][j] += data[i][k] * r[k][j];
                    return result;
                }

                Matrix<T, size> operator-(const Matrix<T, size>& r) 
                {
                    Matrix<T, size> result(static_cast<T>(0.0));
                    for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                            result[i][j] = data[i][j] - r[i][j];
                    return result;
                }

                Matrix<T, size> operator+(const Matrix<T, size>& r)
                {
                    Matrix<T, size> result(static_cast<T>(0.0));
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

                template<typename type = float, std::enable_if_t<std::is_arithmetic_v<T>, bool> = true>
                Vector<size, type > operator*(const Vector<size,type>& vec)
                {
                    Vector<size, type> res(T(0.0));
                    for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                            res[i] += data[i][j] * vec[j];
                    return res;
                }

            private:
                T data[size][size];
            };

            template<size_t size, typename T>
            class Vector
            {
            public:

                template <typename... Scalars,typename = std::enable_if_t<sizeof...(Scalars) <= size && std::is_arithmetic<typename templatesUtils::tuple<Scalars...>::value_type>::value>>
                explicit Vector(Scalars... coords):data{ static_cast<T>(coords)... }
                {
                }

                template <typename type, std::enable_if_t<std::is_arithmetic_v<type>, bool> = true>
                Vector(type* arr)
                {
                    std::memcpy(data, arr, sizeof(type) * size);
                }

                template <typename type, std::enable_if_t<std::is_arithmetic_v<type>, bool> = true>
                Vector()
                {
                    std::memset(data, 0, sizeof(type) * size);
                }

                Vector<size, T> operator +(const Vector<size, T>& vec)
                {
                    Vector<size, T> tmp(T(0.0));
                    for (size_t i = 0; i < size; ++i)
                        tmp[i] = vec[i] + data[i];
                    return tmp;
                }

                Vector<size, T> operator -(const Vector<size, T>& vec)
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

                template<typename type = float,class = typename std::enable_if_t<std::is_arithmetic_v<type>>>
                Vector<size, T> operator*(type num) const
                {
                    Vector temp(*this);
                    for (size_t i = 0; i < size; ++i)
                        temp[i] *= num;
                    return temp;
                }

                template<typename type = float, class = typename std::enable_if_t<std::is_arithmetic_v<type>>>
                Vector<size, T> operator/(type num) const
                {
                    Vector temp(*this);
                    for (size_t i = 0; i < size; ++i)
                        temp[i] /= num;
                    return temp;
                }

                template<typename type = float, class = typename std::enable_if_t<std::is_arithmetic_v<type>>>
                Vector<size, T>& operator /=(type num)
                {
                    for (size_t i = 0; i < size; ++i)
                        data[i] /= num;
                    return *this;
                }

                template<typename type = float, class = typename std::enable_if_t<std::is_arithmetic_v<type>>>
                Vector<size, T>& operator *=(type num)
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

                template<size_t s, typename type>
                friend Vector<s, type> operator*(type num, const Vector<s, type>& vec);

                inline T& operator[](std::size_t index)
                {
                    return data[index];
                }

                inline const T& operator[](std::size_t index) const
                {
                    return data[index];
                }

                //inline const vector<T> operator[](std::initializer_list<std::size_t> indexes) const
                //{
                //    return data[index];
               // }

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

                inline T* ptr() { return data; }
                inline T* ptr() const { return data; }

                template<typename type, class = typename std::enable_if_t<std::is_arithmetic_v<type>>>
                operator Vector<size, type>()
                {
                    Vector<size, type> res(type(0));
                    for (size_t i = 0; i < size; ++i)
                        res[i] = static_cast<type>(data[i]);
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
            template <typename T = float,class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
            Vector<DimRealSpace, T> cross(const Vector<DimRealSpace, T>& vec1,const Vector<DimRealSpace, T>& vec2)
            {
               
                return Vector<3, T>(vec2[1] * vec1[2] - vec2[2] * vec1[1],
                                    vec2[2] * vec1[0] - vec2[0] * vec1[2],
                                    vec2[0] * vec1[1] - vec2[1] * vec1[0]);
            }

            template<size_t size, typename T>
            Vector<size, T> operator*(T num, const Vector<size, T>& vec)
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

            template<size_t size, typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size > 0) && (size < 4)>>
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

                Vector<size, T> eval(T t)
                {
                    Vector<size, T> res(T(0.0));    
                    for (size_t i = 0;i < size;++i)
                        res[i] = data[i](t);
                    return res;
                }

                /*t - point, n - number of der,h - step (error)*/
                Vector<size, T> derivative(T t, size_t n, T h)
                {
                    Vector<size, T> res(eval(t));
                    T sign = -1;

                    for (size_t i = 0; i < n; ++i,sign *= -1) 
                        res += sign * static_cast<T>(C(n, i)) * eval(t + static_cast<T>(i) * h);
                    
                    sign *= -1;

                    return res * sign / pow(h, n);
                }

                Vector<size, T> tangent(T t)
                {
                    Vector<size, T> res(T(0.0));
                    res = derivative(t, 1, 0.001);

                    return res / res.length();
                }

                T curvature(T t) 
                {
                    Vector<3, T> _1der = derivative(t, 1, 0.001);
                    return cross(derivative(t, 2, 0.001), _1der).length() / pow(_1der.length(), 3);
                }

                Vector<size, T> norm(T t)
                {
                    Vector<size, T> _1der = derivative(t, 1, 0.001);
                    Vector<size, T> _2der = derivative(t, 2, 0.001);

                    return _2der / pow(_2der.length(), 2) - (_1der * _2der / pow(_1der.length(), 4)) * _1der;
                }

                Vector<3, T> binorm(T t) 
                {
                    Vector<3, T> _1der = derivative(t, 1, 0.001);
                    Vector<3, T> _2der = derivative(t, 2, 0.001);
                    Vector<3, T> cr = cross(_1der, _2der);
                    
                    return cr / cr.length();
                }

                T curvatureRadius(T t) 
                {
                    Vector<3, T> _1der = derivative(t, 1, 0.001);
                    Vector<3, T> _2der = derivative(t, 2, 0.001);

                    return pow(_1der.length(), 3) / cross(_1der, _2der).length();
                }
                
                T torsion(T t) 
                {
                    Vector<3, T> _1der = derivative(t, 1, 0.001);
                    Vector<3, T> _2der = derivative(t, 2, 0.001);
                    Vector<3, T> _3der = derivative(t, 3, 0.001);
                    Vector<3, T> cr = cross(_1der, _2der);

                    return cr * _3der / pow(cr.length(), 2);
                }

            private:
                std::function< T(T) > data[DimRealSpace];
                //fun_t data[DimRealSpace];
                //std::initializer_list<fun_t> data{ [](T x) {return T(0); }, [](T x) {return T(0); }, [](T x) {return T(0); } };
            };

            template<size_t size, typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size == 2 || size == 3)>>
            class ellipse:public curve<size, T>
            {
            public:
                ellipse(T a, T b, Vector<size, T> center = Vector<size, T>(0)):curve<size, T>(
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
            class circle :public ellipse<size, T>
            {
            public:
                circle(T radius, Vector<size, T> center = Vector<size, T>(0)):ellipse<size, T>(radius, radius, center) {}
            };

            template<size_t size, typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size == 2 || size == 3)>>
            class hyperbola:curve<size,T>
            {
            public:
                hyperbola(T a,T b, Vector<size, T> center = Vector<size, T>(0)):curve<size, T>([&](T t) {return a * std::cosh(t) + center[0]; }, [&](T t) {return b * std::sinh(t) + center[1]; }, [&](T t) {return center[2]; }){}
            };

            template<size_t size, typename T,  class = typename std::enable_if_t<std::is_arithmetic_v<T> && (size == 2 || size == 3)>>
            class parabola:curve<size, T>
            {
            public:
                parabola(T focus, Vector<size, T> center = Vector<size, T>(0)):curve<size, T>([&](T t) {return focus * t * t + center[0]; }, [&](T t) {return 2 * focus * t + center[1]; }, [&](T t) {return center[2]; }) {}
            };

            template<typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
            class spiral:curve<3, T>
            {
            public:
                spiral(T radius,T step, Vector<3, T> center = Vector<3, T>(0)):curve<3, T>([&](T t) {return radius * std::cos(t) + center[0]; }, [&](T t) {return radius * std::sin(t) + center[1]; }, [&](T t) {return step * t/(2 * Pi) + center[2]; }) {}
            };

            template<typename T,template <typename... Args> class Container, typename... Types>
            curve<2,T> LagrangeSplain(const Container<Vector<2,T>,Types...>& points)
            {
                return curve<2,T>([](T x) {return x; }, [=](T y)
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
            curve<2,T> NewtonSplain(const Container<Vector<2,T>, Types...>& points) 
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

               return curve<2, T>([](T x) {return x; }, [ACoefs = std::move(ACoefs),points](T y) mutable
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
            curve<2, T> ErmitSplain(const Container<Vector<2, T>, Types...>& points) 
            {
                
            }

            template<typename T, template <typename... Args> class Container, typename... Types>
            curve<2, T> BazieSplain(const Container<Vector<2, T>, Types...>& points)
            {
                std::shared_ptr<T[]> Bi(new T[points.size()]);
                T N = points.size();
                //Newton binom
                Bi[0] = 1;
                for (size_t i = 1; i < points.size(); ++i)
                    Bi[i] = Bi[i - 1] * (N + 1 - i) / i;

                return curve<2, T>([](T x) {return x; }, [Bi = std::move(Bi), points](T y) mutable
                {
                    T res(T(0));

                    size_t i = 0;
                    for (const auto& point : points)
                        res += Bi[i++] * pow(point[0], i) * pow(1 - point[0], points.size() - i) * point[1];

                    return res;
                });
            }

           }
    }
}
