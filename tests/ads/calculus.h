#pragma once
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