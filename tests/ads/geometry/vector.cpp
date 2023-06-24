/// @file vector.cpp
/// @brief tests for geometry module - vector
#include <geometry/vector.hpp>

#include <gtest/gtest.h>


using namespace ads::mathematics::geometry;

TEST(GeometryVector, Sum)
{
    Vector<1, int32_t> v11(1), v12(1);

    Vector<1, int32_t> res1 = v11 + v12;

    ASSERT_TRUE(res1[0] == 2);

    Vector<1, double> v13(1.0), v14(1.0);

    Vector<1, double> res2 = v13 + v14;

    ASSERT_TRUE(res2[0] == 2.0);
}