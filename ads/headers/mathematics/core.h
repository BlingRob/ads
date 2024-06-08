/// @file core.h 
/// @brief Common using things and structure all project

#pragma once
#ifndef __CORE_H__
#define __CORE_H__

#include <set>

namespace ads
{
    /// <summary>
    /// common library structure
    /// </summary>

    /*
    namespace structures {}

    namespace mathematics
    {
        namespace algebra {}
        namespace calculus {}
        namespace number_theory {}
        namespace geometry {}
        namespace statistics {}
    }
    
    */
    /// <summary>
    /// common useful tools
    /// </summary>

    
    template<class T> T& unmove(T&& t) { return t; }

    template<class iter>
    std::multiset<float> UniqueWithCount(iter start, iter end)
    {
        return std::multiset<float>(start, end);
    }

    template<template<class...> class container, class T, class... Args>
    std::multiset<T> UniqueWithCount(const container<T, Args...>& cont)
    {
        return std::multiset<T>(cont.cbegin(), cont.cend());
    }

    template<typename T>
    void swap(T& a, T& b)
    {
        a ^= (b ^= (a ^= b));
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    T GetBit(T* a, T k)
    {
        return (a[k >> 5] >> (k & 31)) & 1;
    }

    inline int NBit(unsigned int x)
    {
        return x == 0 ? 0 : (x & 1) + NBit(x >> 1);
    }

    namespace templatesUtils 
    {
        template<typename... Args>
        struct tuple;

        template<typename Head, typename... Tail>
        struct tuple<Head, Tail...> : tuple<Tail...>
        {
            tuple(Head h, Tail... tail)
                : tuple<Tail...>(tail...), head_(h)
            {}
            typedef tuple<Tail...> base_type;
            typedef Head           value_type;

            base_type& base = static_cast<base_type&>(*this);
            Head       head_;
        };

        template<>
        struct tuple<>
        {};

    }
}

#endif // __CORE_H__