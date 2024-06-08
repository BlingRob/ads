#include <mathematics/algebra.h>

#include <gtest/gtest.h>

using namespace ads::mathematics::algebra;

TEST(Algebra, PolynomMult)
{
    Polynomial p({ 1, 2, 3, 4 }), 
               p1({1, 1});
    Polynomial res = p * p1;

    ASSERT_EQ(res.Degree(), p.Degree() + p1.Degree());
    ASSERT_TRUE(res == Polynomial({ 1, 3, 5, 7, 4 }));
}

TEST(Algebra, PolynomSum)
{
    Polynomial p({ 1, 2, 3, 4 }), 
               p1({1, 1});
    Polynomial res = p + p1;

    ASSERT_EQ(res.Degree(), std::max(p.Degree(), p1.Degree()));
    ASSERT_TRUE(res == Polynomial({ 1, 2, 4, 5}));
}