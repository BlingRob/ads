#pragma once
#include <type_traits>

namespace ads
{
	namespace mathematics 
	{
		template<typename T>
		struct AdditiveGroup
		{
			virtual T operator+(const T&) {} override;
			virtual T operator-(const T&) {} override;
		};

		template<typename T>
		struct MultiplicativeGroup
		{
			virtual T operator*(const T&) {} override;
			virtual T operator/(const T&) {} override;
		};

		template<typename T>
		struct Ring:public AdditiveGroup,public MultiplicativeGroup
		{
		};

		template<typename T,typename deg,typename = std::enable_if_t<std::is_arithmetic_v<T> && std::is_integral_v<deg>>>
		int pow(T a, deg n)
		{
			return (!n) ? 1 : a * pow(a, n - 1);
		}

		template<typename T, typename deg, typename = std::enable_if_t<std::is_arithmetic_v<T>&& std::is_integral_v<deg>>>
		int powInd(T a, deg n)
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
		int pow2(int n)
		{
			return 1 << n;
		}

		template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
		T MaxDivPow2(T n)
		{
			return n & -n;
		}

		template<typename T>
		int cmp(const T& a, const T& b) {
			return (a < b ? -1 : a > b);
		}

	}
}