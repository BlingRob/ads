#pragma once
#include "core.h"
#include <numeric>
#include <limits>
#include <iostream>
#include <vector>

namespace ads
{
    namespace mathematics
    {
        namespace number_theory
        {
            uint64_t gcd(uint64_t m, uint64_t n)
            {
                while (m)
                {
                    swap(m, n);
                    m %= n;
                }
                return n;
            }

            uint64_t lcm(uint64_t m, uint64_t n)
            {
                return (m * n) / gcd(m, n);
            }

            class fraction
            {
            public:
                fraction(int64_t num, int64_t den = 1)
                {
                    int64_t _gcd = gcd(std::abs(num), std::abs(den));
                    numer = (den / std::abs(den)) * num / _gcd;
                    denum = std::abs(den) / _gcd;
                }
                double toDouble() const
                {
                    return static_cast<double>(*this);
                }

                operator double() const
                {
                    return (denum == 0) ? std::numeric_limits<double>::infinity() : static_cast<double>(numer) / denum;
                }

                constexpr int64_t num() const { return numer; }
                constexpr int64_t den() const { return denum; }

                //Operations with fractions
                fraction operator +(const fraction& rgh) const
                {
                    int64_t _lcm = lcm(rgh.denum, denum);
                    return fraction(this->numer * (_lcm / this->denum) + rgh.numer * (_lcm / rgh.denum), _lcm);
                }

                fraction operator -(const fraction& rgh) const
                {
                    int64_t _lcm = lcm(rgh.denum, denum);
                    return fraction(this->numer * (_lcm / this->denum) - rgh.numer * (_lcm / rgh.denum), _lcm);
                }

                fraction operator *(const fraction& rgh) const
                {
                    return fraction(this->numer * rgh.numer, this->denum * rgh.denum);
                }

                fraction operator /(const fraction& rgh) const
                {
                    return fraction(this->numer * rgh.denum, this->denum * rgh.numer);
                }

                //Operations with numbers
                fraction operator *(int64_t num)
                {
                    return fraction(this->numer * num, this->denum);
                }

                fraction operator +(int64_t num) const
                {
                    return *this + unmove(fraction(num, 1));
                }

                fraction& operator *=(int64_t num)
                {
                    this->numer *= num;
                    normalize();
                    return *this;
                }

                fraction& operator /=(int64_t num)
                {
                    this->denum *= num;
                    normalize();
                    return *this;
                }

                fraction& operator +=(int64_t num)
                {
                    this->numer += num * denum;
                    normalize();
                    return *this;
                }

                fraction& operator -=(int64_t num)
                {
                    this->numer -= num * denum;
                    normalize();
                    return *this;
                }

                friend fraction operator *(int64_t num, const fraction& rgh);
                friend fraction operator /(int64_t num, const fraction& rgh);
                friend fraction operator +(int64_t num, const fraction& rgh);
                friend fraction operator -(int64_t num, const fraction& rgh);

                //Comparers
                friend bool operator <(const fraction& left, const fraction& right);
                friend bool operator ==(const fraction& left, const fraction& right);
                friend bool operator !=(const fraction& left, const fraction& right);
                friend bool operator >(const fraction& left, const fraction& right);

                //IO operations
                friend std::ostream& operator<<(std::ostream& out, const fraction& f);
            private:
                int64_t numer;
                int64_t denum;

                void normalize()
                {
                    int64_t _gcd = gcd(std::abs(this->numer), std::abs(this->denum));
                    this->numer /= _gcd;
                    this->denum /= _gcd;
                }
            };

            //Comparers
            bool operator <(const fraction& left, const fraction& right)
            {
                return (left - right).num() < 0;
            }

            bool operator ==(const fraction& left, const fraction& right) 
            {
                return (left - right).num() == 0;
            }

            bool operator !=(const fraction& left, const fraction& right)
            {
                return !(left == right);
            }

            bool operator >(const fraction& left, const fraction& right) 
            {
                return (left - right).num() > 0;
            }

            std::ostream& operator<<(std::ostream& out, const fraction& f)
            {
                return out << f.numer << '/' << f.denum;
            }

            fraction operator *(int64_t num, const fraction& rgh)
            {
                return fraction(rgh.numer * num, rgh.denum);
            }

            fraction operator /(int64_t num, const fraction& rgh)
            {
                return fraction(num * rgh.denum, rgh.numer);
            }

            fraction operator +(int64_t num, const fraction& rgh)
            {
                return fraction(rgh.numer + num * rgh.denum, rgh.denum);
            }

            fraction operator -(int64_t num, const fraction& rgh)
            {
                return fraction(num * rgh.denum - rgh.numer, rgh.denum);
            }

            fraction FromContFractionToSimpleFraction(const std::vector<fraction>& ContinuedFraction)
            {
                fraction res(*ContinuedFraction.crbegin());
                for (auto it{ ++ContinuedFraction.crbegin() }; it != --ContinuedFraction.crend(); ++it)
                {
                    res += it->den();
                    res = it->num() / res;
                }
                return res + *(--ContinuedFraction.crend());
            }

            std::vector<fraction> ToContFration(const fraction& frac, uint32_t iterations = 10)
            {
                std::vector<fraction> res;
                res.push_back({ frac.num() / frac.den() });

                int64_t r_n = frac.num() % frac.den(),
                    r_n_1 = frac.den();

                uint32_t i = 0;
                while (r_n != 0)// && i < iterations
                {
                    res.push_back({ 1, r_n_1 / r_n });
                    std::swap(r_n_1 %= r_n, r_n);
                    ++i;
                }

                return res;
            }

            std::vector<fraction> ToContFration(double num)
            {
                return ToContFration(fraction(static_cast<int64_t>(num * 10E10), static_cast<int64_t>(10E10)));
            }

            std::vector<fraction> RatioApprox(const std::vector<fraction>& ContFration)
            {
                std::vector<fraction> res;
                int64_t Pk_1 = 1, Qk_1 = 0, Pk = ContFration.cbegin()->num(), Qk = 1;
                for (auto it = ++ContFration.cbegin(); it != ContFration.cend(); ++it)
                {
                    res.push_back({ Pk,Qk });
                    Pk_1 = it->den() * Pk + it->num() * Pk_1;
                    Qk_1 = it->den() * Qk + it->num() * Qk_1;
                    std::swap(Pk_1, Pk);
                    std::swap(Qk_1, Qk);
                }
                return res;
            }
        }

    }

}