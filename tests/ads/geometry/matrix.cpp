/// @file matrix.cpp
/// @brief tests for geometry module - matrix
#include <geometry/matrix.hpp>

#include <gtest/gtest.h>


using namespace ads::mathematics;
using namespace geometry;



TEST(GeometryMatrix, Diag)
{
    auto mat = Diag(1,2,3);

    ASSERT_EQ(mat[0][0], 1);
    ASSERT_EQ(mat[0][1], 0);
    ASSERT_EQ(mat[0][2], 0);

    ASSERT_EQ(mat[1][0], 0);
    ASSERT_EQ(mat[1][1], 2);
    ASSERT_EQ(mat[1][2], 0);

    ASSERT_EQ(mat[2][0], 0);
    ASSERT_EQ(mat[2][1], 0);
    ASSERT_EQ(mat[2][2], 3);

}