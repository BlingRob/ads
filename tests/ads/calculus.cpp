#include <calculus.h>

#include <gtest/gtest.h>

using retT = double;

retT f(retT x)
{
    return x;
}

TEST(Calculus, NewtonMethod1)
{
    ASSERT_EQ(ads::mathematics::calculus::NewtonMethod(f, 0.0, 10.0), 0);
}

TEST(Calculus, bisection1)
{
    double eps = 0.001;
    ASSERT_TRUE(std::abs(ads::mathematics::calculus::bisection(f, 0.0, 10.0) - 0) <= eps);
}

TEST(Calculus, HordMethod1)
{
    ASSERT_EQ(ads::mathematics::calculus::HordMethod(f, 0.0, 10.0), 0);
}