/// @file matrix.cpp
/// @brief tests for geometry module - matrix
#include <mathematics/geometry/matrix.hpp>

#include <gtest/gtest.h>


using namespace ads::mathematics;
using namespace geometry;

TEST(GeometryMatrix, Init1)
{
    Matrix<3> mat(1.0);

    ASSERT_EQ(mat[0][0], 1.0);
    ASSERT_EQ(mat[0][1], 0.0);
    ASSERT_EQ(mat[0][2], 0.0);

    ASSERT_EQ(mat[1][0], 0.0);
    ASSERT_EQ(mat[1][1], 1.0);
    ASSERT_EQ(mat[1][2], 0.0);

    ASSERT_EQ(mat[2][0], 0.0);
    ASSERT_EQ(mat[2][1], 0.0);
    ASSERT_EQ(mat[2][2], 1.0);
}

TEST(GeometryMatrix, Init2)
{
    Matrix<3> mat({{1,2,3},{4,5,6},{7,8,9}});

    ASSERT_EQ(mat[0][0], 1);
    ASSERT_EQ(mat[0][1], 2);
    ASSERT_EQ(mat[0][2], 3);

    ASSERT_EQ(mat[1][0], 4);
    ASSERT_EQ(mat[1][1], 5);
    ASSERT_EQ(mat[1][2], 6);

    ASSERT_EQ(mat[2][0], 7);
    ASSERT_EQ(mat[2][1], 8);
    ASSERT_EQ(mat[2][2], 9);
}

TEST(GeometryMatrix, Init3)
{
    Matrix<3> mat;

    ASSERT_EQ(mat[0][0], 0);
    ASSERT_EQ(mat[0][1], 0);
    ASSERT_EQ(mat[0][2], 0);

    ASSERT_EQ(mat[1][0], 0);
    ASSERT_EQ(mat[1][1], 0);
    ASSERT_EQ(mat[1][2], 0);

    ASSERT_EQ(mat[2][0], 0);
    ASSERT_EQ(mat[2][1], 0);
    ASSERT_EQ(mat[2][2], 0);
}

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

TEST(GeometryMatrix, Equality)
{
    auto mat1 = Diag(1,2,3);
    Matrix<3, int> mat2({{1,0,0},{0,2,0},{0,0,3}});
    Matrix<3, int> mat3(1.0);

    ASSERT_TRUE(mat1 == mat2);

    ASSERT_FALSE(mat2 == mat3);

    ASSERT_TRUE(mat1 != mat3);
}