// \\\ file mathematics.h
// \\\ maths core defenitions
#pragma once
#include <type_traits>

namespace ads
{
	namespace mathematics 
	{
		const double Pi = 3.1415926535897932384;

		template<typename T,typename deg,typename = std::enable_if_t<std::is_arithmetic_v<T> && std::is_integral_v<deg>>>
		T pow(T a, deg n)
		{
			return (!n) ? 1 : a * pow(a, n - 1);
		}

		template<typename T, typename deg, typename = std::enable_if_t<std::is_arithmetic_v<T>&& std::is_integral_v<deg>>>
		T powInd(T a, deg n)
		{
			return (!n) ? 1 : ((n & 1) ? a : 1) * powInd(a * a, n / 2);
		}

		template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
		T count(T a)
		{
			return (!a) ? 0 : (a % 10 + count(a / 10));
		}

		template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
		T Mersen(T n) 
		{
			return !(n & (n + 1));
		}

		template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
		T pow2(T n)
		{
			return 1 << n;
		}

		template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
		T MaxDivPow2(T n)
		{
			return n & -n;
		}

		template<typename T>
		bool cmp(const T& a, const T& b) {
			return (a < b ? -1 : a > b);
		}

		uint64_t factorial(uint64_t n) 
		{
			uint64_t res = 1;
			
			for (uint64_t i = 1; i <= n; ++i)
				res *= i;
			return res;
		}

		uint64_t C(uint64_t n, uint64_t k) 
		{
			if (n > k)
				return factorial(n) / (factorial(k) * factorial(n - k));
			else
				return 1;
		}
	}
}