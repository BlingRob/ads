/// @file vector.cpp
/// @brief tests for geometry module - vector
#include <mathematics/geometry/vector.hpp>

#include <gtest/gtest.h>


using namespace ads::mathematics::geometry;

TEST(GeometryVector, Sum1)
{
    Vector<1, int32_t> v11(1), v12(1);

    Vector<1, int32_t> res1 = v11 + v12;

    ASSERT_TRUE(res1[0] == 2);

    Vector<1, double> v13(1.0), v14(1.0);

    Vector<1, double> res2 = v13 + v14;

    ASSERT_TRUE(res2[0] == 2.0);
}

TEST(GeometryVector, Sum2)
{
    Vector<2, int32_t> v21(1, 2), v22(1, 2);

    Vector<2, int32_t> res1 = v21 + v22;

    ASSERT_TRUE(res1[0] == 2 && res1[1] == 4);

    Vector<2, double> v23(1.0, 2.0), v24(1.0, 3.0);

    Vector<2, double> res2 = v23 + v24;

    ASSERT_TRUE(res2[0] == 2.0 && res2[1] == 5.0);
}

TEST(GeometryVector, Dif1)
{
    Vector<1, int32_t> v11(1), v12(1);

    Vector<1, int32_t> res1 = v11 - v12;

    ASSERT_TRUE(res1[0] == 0);

    Vector<1, double> v13(1.0), v14(1.0);

    Vector<1, double> res2 = v13 - v14;

    ASSERT_TRUE(res2[0] == 0.0);
}

TEST(GeometryVector, Dif2)
{
    Vector<2, int32_t> v21(1, 2), v22(1, 2);

    Vector<2, int32_t> res1 = v21 - v22;

    ASSERT_TRUE(res1[0] == 0 && res1[1] == 0);

    Vector<2, double> v23(1.0, 2.0), v24(1.0, 3.0);

    Vector<2, double> res2 = v23 - v24;    

    ASSERT_TRUE(res2[0] == 0.0 && res2[1] == -1.0);
}

TEST(GeometryVector, Mul)
{
    Vector<1, int32_t> v11(1);

    Vector<1, int32_t> res1 = 2 * v11;

    ASSERT_TRUE(res1[0] == 2);

    Vector<2, double> v22(1.0, 2.0);

    Vector<2, double> res2 = 3.0 * v22;    

    ASSERT_TRUE(res2[0] == 3.0 && res2[1] == 6.0);

    v22 *= 2.0;

    ASSERT_TRUE(v22[0] == 2.0 && v22[1] == 4.0);
}

TEST(GeometryVector, Div)
{
    Vector<1, int32_t> v11(2);

    Vector<1, int32_t> res1 = v11 / 2;

    ASSERT_TRUE(res1[0] == 1);

    Vector<2, double> v22(1.0, 2.0);

    Vector<2, double> res2 = v22 / 2.0;    

    ASSERT_TRUE(res2[0] == 0.5 && res2[1] == 1.0);

    v22 /= 2.0;

    ASSERT_TRUE(v22[0] == 0.5 && v22[1] == 1.0);
}

TEST(GeometryVector, DotProduct)
{
    Vector<3, double> v23(1.0, 2.0, 3.0), v24(-1.0, -2.0, -3.0);

    double res1 = v23 * v24;   

    ASSERT_TRUE(res1 == -14.0);
}

TEST(GeometryVector, Slice)
{
    Vector<3, double> v13(1.0, 2.0, 3.0);

    Vector<2, double> v21 = v13.Slice<0, 2>();  

    ASSERT_TRUE(v21[0] == 1.0 && v21[1] == 2.0);

    Vector<2, double> v22 = v13.Slice<1, 3>(); 

    ASSERT_TRUE(v22[0] == 2.0 && v22[1] == 3.0); 
}

TEST(GeometryVector, Length)
{
    Vector<2, double> v12(3.0, 4.0);

    ASSERT_TRUE(v12.Length() == 5.0);
}

TEST(GeometryVector, Norm)
{
    Vector<2, double> v12  = Vector<2, double>(3.0, 4.0).Norm();

    ASSERT_TRUE(v12[0] == 0.6 && v12[1] == 0.8);
}

TEST(GeometryVector, Cross)
{
    Vector<3, double> v13(1.0, 2.0, 3.0),
                      v23(4.0, 5.0, 6.0);
    
    Vector<3, double> cross = Cross(v13, v23);

    ASSERT_TRUE(cross[0] == -3.0 && cross[1] == 6.0 && cross[2] == -3.0);
}

TEST(GeometryVector, Cos)
{
    Vector<2, double> v12(1.0, 0.0),
                      v22(0.0, 1.0);
    
    double cos = Cos(v12, v22);

    ASSERT_TRUE(cos == 0.0);

    Vector<2, double> v32(1.0,  0.0),
                      v42(-1.0, 0.0);
    
    double cos2 = Cos(v32, v42);

    ASSERT_TRUE(cos2 == -1.0);
}