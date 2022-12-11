// \\\ file statistics.h

#pragma once
#include "core.h"
#include <type_traits>
#include <algorithm>
#include <numeric>
#include <math.h>

namespace ads
{
    namespace mathematics 
	{
        namespace statistics
        {
            template<class iter>
            float mean(iter it1, iter it2)
            {
                if constexpr (std::is_pointer<iter>())
                    ++it2;
                return static_cast<float>(std::accumulate(it1, it2, 0.0f)) / std::distance(it1, it2);
            }

            template<class iter>
            float variance(iter it1, iter it2, float m = 0)
            {
                m = mean(it1, it2);
                if constexpr (std::is_pointer<iter>())
                    ++it2;
                return static_cast<float>(std::accumulate(it1, it2, 0.0f, [&m](float acc, float x) {return acc + pow(x - m, 2); })) / (std::distance(it1, it2) - 1);
            }

            template<template<class...> class container, class T, class... Args>
            float mean(const container<T, Args...>& cont)
            {
                return mean(cont.cbegin(), cont.cend());
            }

            template<template<class...> class container, class T, class... Args>
            float variance(const container<T, Args...>& cont, float m = 0.0f)
            {
                return variance(cont.cbegin(), cont.cend(), (m == 0.0f) ? mean(cont) : m);
            }

            inline float StdDeviation(float var)
            {
                return std::sqrt(std::abs(var));
            }

            template<class iter>
            inline float mode(iter it1, iter it2)
            {
                std::pair<float, uint32_t> num_count = std::make_pair<float, uint32_t>(0.0f, 0);

                if constexpr (std::is_pointer<iter>())
                    ++it2;

                size_t count;
                for (; it1 != it2; ++it1)
                {
                    count = std::count(it1, it2, *it1);
                    if (count > num_count.second)
                        num_count.first = *it1, num_count.second = count;
                }
                return num_count.first;
            }

            template<template<class...> class container, class T, class... Args>
            float mode(const container<T, Args...>& cont)
            {
                return mode(cont.cbegin(), cont.cend());
            }

            template<class iter>
            inline float range(iter it1, iter it2)
            {
                std::pair<float, float> elems = std::minmax_element(it1, it2);

                return elems.second - elems.first;
            }

            template<template<class...> class container, class T, class... Args>
            float range(const container<T, Args...>& cont)
            {
                return range(cont.cbegin(), cont.cend());
            }

            template<class iter>
            inline float median(iter it1, iter it2)
            {
                if (std::is_sorted(it1, it2))
                    return *(it1 + (it2 - it1) / 2);

                std::set<float> Set(it1, it2);

                return *std::next(Set.begin(), std::distance(Set.begin(), Set.end()) / 2);
            }

            template<template<class...> class container, class T, class... Args>
            float median(const container<T, Args...>& cont)
            {
                return median(cont.cbegin(), cont.cend());
            }
        }
    }
}