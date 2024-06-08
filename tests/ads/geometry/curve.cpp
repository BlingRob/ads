/// @file curve.cpp
/// @brief tests for geometry module - curve
#include <mathematics/geometry/curve.hpp>

#include <gtest/gtest.h>

using retT = double;

using namespace ads::mathematics;
using namespace geometry;

retT X(retT x)
{
    return x;
}

retT Y(retT x)
{
    return x * x;
}

retT Z(retT x)
{
    return x * x * x * x * x;
}

TEST(GeometryCurve, StandartOps)
{
    Curve<3, double> cur(X, Y);
    Vector<3, double> tan = cur.Tangent(0.5);
    double c = cur.Curvature(0.5);
    Vector<3, double> normal = cur.Norm(0);
    Vector<3, double> binormal = cur.Binorm(0);
    double rad = cur.CurvatureRadius(0);
    double tor = cur.Torsion(0);
}

TEST(GeometryCurve, Derivative1)
{
    double accuracy = 0.001;
    size_t n = 1;
    Curve<3,  double> a(X, Y, Z);
    Vector<3, double> der = a.Derivative(1.0, n, accuracy);
    Vector<3, double> answer(.1f, 2.f, 5.f);

    std::cout << der[0] << " " << der[1] << " " << der[2] << std::endl;
    std::cout << answer[0] << " " << answer[1] << " " << answer[2] << std::endl; 

    ASSERT_TRUE(isEqual(der, answer, accuracy));
}

TEST(GeometryCurve, Derivative2)
{
    double accuracy = 0.001;
    size_t n = 2;
    Curve<3,  double> a(X, Y, Z);
    Vector<3, double> der = a.Derivative(1.0, n, accuracy);
    Vector<3, double> answer(0.f, 2.f, 20.f);

    std::cout << der[0] << " " << der[1] << " " << der[2] << std::endl;
    std::cout << answer[0] << " " << answer[1] << " " << answer[2] << std::endl; 


    ASSERT_TRUE(isEqual(der, answer, accuracy));
}

TEST(GeometryCurve, Derivative3)
{
    double accuracy = 0.001;
    size_t n = 3;
    Curve<3,  double> a(X, Y, Z);
    Vector<3, double> der = a.Derivative(1.0, n, accuracy);
    Vector<3, double> answer(0.f, 0.f, 60.f);

    std::cout << der[0] << " " << der[1] << " " << der[2] << std::endl;
    std::cout << answer[0] << " " << answer[1] << " " << answer[2] << std::endl; 

    ASSERT_TRUE(isEqual(der, answer, accuracy));
}