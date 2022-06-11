#pragma once
#include <tuple>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

namespace ads
{
    namespace mathematics
    {
        namespace algebra
        {
            class polynomial
            {
            public:
                using ValDegree = std::pair<double, int32_t>;
                struct Comparer {
                    bool operator()(const ValDegree& lhs,
                        const ValDegree& rhs) const
                    {
                        return lhs.second > rhs.second;
                    }
                };

                polynomial() {}

                template<typename type>
                polynomial(std::initializer_list<type> coefs)
                {
                    uint32_t degree = coefs.size() - 1;
                    for (const auto& coef : coefs)
                        cofs.insert({ static_cast<double>(coef), degree-- });

                }

                template<typename type>
                polynomial(std::initializer_list<std::pair<type, int32_t>> coefs)
                {
                    for (const auto& coef : coefs)
                        cofs.insert(coef);
                }

                polynomial(std::set<ValDegree, Comparer>&& coefs) :cofs(coefs) {}
                //polynomial(std::size_t size) : cofs(size) {}
                //Operations with fractions
                polynomial operator +(const polynomial& rgh) const
                {
                    auto cmp = [](const ValDegree& lhs,
                        const ValDegree& rhs)
                    {
                        return lhs.second > rhs.second;
                    };

                    std::set<ValDegree, Comparer> Res;
                    std::vector<ValDegree> comDegree, diffDegree;

                    std::set_symmetric_difference(this->cofs.cbegin(), this->cofs.cend(),
                        rgh.cofs.cbegin(), rgh.cofs.cend(), std::back_inserter(diffDegree), cmp);

                    std::set_intersection(this->cofs.cbegin(), this->cofs.cend(),
                        rgh.cofs.cbegin(), rgh.cofs.cend(), std::back_inserter(comDegree), cmp);

                    for (const auto& mon : comDegree)
                        Res.insert({ mon.first + rgh.cofs.find({0,mon.second})->first,mon.second });

                    for (const auto& mon : diffDegree)
                        Res.insert(mon);

                    return Res;
                }

                polynomial operator -(const polynomial& rgh) const
                {
                    std::set<ValDegree, Comparer> copy;

                    for (const auto& mon : rgh.cofs)
                        copy.insert({ (-1) * mon.first, mon.second });

                    return *this + polynomial(std::move(copy));
                }

                polynomial operator *(const polynomial& rgh) const
                {
                    std::set<ValDegree, Comparer> result;
                    ValDegree monom;
                    decltype(result.begin()) it;

                    for (auto& mon : rgh.cofs)
                        for (auto& mon2 : this->cofs)
                        {
                            monom = ValDegree(mon.first * mon2.first, mon.second + mon2.second);
                            if ((it = result.find({ 0,monom.second })) != result.end())
                            {
                                auto handle = result.extract(it);
                                handle.value().first += monom.first;
                                result.insert(std::move(handle));
                            }
                            else
                                result.insert({ monom.first,monom.second });
                        }
                    return result;
                }

                polynomial operator /(const polynomial& rgh) const
                {

                }

                template<typename T, typename = std::is_integral<T> >
                double value(T x)
                {
                    double res = 0.0;
                    for (const auto& mon : cofs)
                        res += mon.first * std::pow(x, mon.second);
                    return res;
                }

                //IO operations
                friend std::ostream& operator<<(std::ostream& out, const polynomial& p);
            private:

                std::set<ValDegree, Comparer> cofs;
            };

            std::ostream& operator<<(std::ostream& out, const polynomial& p)
            {
                for (auto it = p.cofs.cbegin(); it != p.cofs.cend(); ++it)
                {
                    if (it->first == 1.0)
                        out << "x^(" << std::noshowpos << it->second << ")";
                    else if (it->first == 0.0)
                        continue;
                    else if (it->second == 0)
                        out << std::showpos << it->first;
                    else if (it->second == 1)
                        out << std::showpos << it->first << "x";
                    else
                        out << std::showpos << it->first << "x^(" << std::noshowpos << it->second << ")";
                }
                return out;
            }
        }
    }
}