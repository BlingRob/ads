/// @file algebra.h 
/// @brief Some algebraic staff

#pragma once
#ifndef __ALGEBRA_H__
#define __ALGEBRA_H__

#include <tuple>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>

namespace ads
{
    namespace mathematics
    {
        namespace algebra
        {
            template<typename T>
            struct AdditiveGroup
            {
                virtual T operator+(const T&) = 0;
                virtual T operator-(const T&) = 0;
            };

            template<typename T>
            struct MultiplicativeGroup
            {
                virtual T operator*(const T&)  = 0;
                virtual T operator/(const T&)  = 0;
            };

            template<typename T>
            struct Ring : AdditiveGroup<T>, MultiplicativeGroup<T>
            {
            };

            class Polynomial
            {
            public:
                //template<typename type = double>
                using ValDegree = std::pair<double, size_t>;
                struct Comparer 
                {
                    bool operator()(const ValDegree& lhs,
                        const ValDegree& rhs) const
                    {
                        return lhs.second > rhs.second;
                    }
                };

                Polynomial() {}

                template<typename type>
                Polynomial(std::initializer_list<type> coefs)
                {
                    std::size_t degree = coefs.size() - 1;
                    for (const auto& coef : coefs)
                        cofs.insert({ static_cast<double>(coef), degree-- });
                }

                template<typename type>
                Polynomial(std::initializer_list<ValDegree> coefs)
                {
                    for (const auto& coef : coefs)
                        cofs.insert(coef);
                }

                Polynomial(std::set<ValDegree, Comparer>&& coefs) :cofs(coefs) {}
                //Polynomial(std::size_t size) : cofs(size) {}
                //Operations with fractions
                Polynomial operator +(const Polynomial& rgh) const
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

                Polynomial operator -(const Polynomial& rgh) const
                {
                    std::set<ValDegree, Comparer> copy;

                    for (const auto& mon : rgh.cofs)
                        copy.insert({ (-1) * mon.first, mon.second });

                    return *this + Polynomial(std::move(copy));
                }

                Polynomial operator *(const Polynomial& rgh) const
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

                //TODO
                Polynomial operator /(const Polynomial& rgh) const
                {
                    return *this;
                }

                bool operator ==(const Polynomial& rgh) const
                {
                    if((this->Degree() != rgh.Degree()) || (this->cofs.size() != rgh.cofs.size()))
                        return false;
                    
                    for(auto it1 = this->cofs.cbegin(),it2 = rgh.cofs.cbegin();it1 != this->cofs.cend();++it1,++it2)
                        if((it1->first != it2->first) && (it1->second != it2->second))
                            return false;
                    return true;
                    
                } 

                template<typename T, typename = std::is_integral<T> >
                double value(T x) const
                {
                    double res = 0.0;
                    for (const auto& mon : cofs)
                        res += mon.first * pow(x, mon.second);
                    return res;
                }

                size_t Degree() const
                {
                    if(cofs.empty())
                        return 0;
                    else
                        return cofs.cbegin()->second;
                }

                //IO operations
                friend std::ostream& operator<<(std::ostream& out, const Polynomial& p);
            private:

                std::set<ValDegree, Comparer> cofs;
            };

            std::ostream& operator<<(std::ostream& out, const Polynomial& p)
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

#endif // __ALGEBRA_H__