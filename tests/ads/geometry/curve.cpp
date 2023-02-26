/// @file tests for geometry module
#include <geometry/curve.hpp>

#include <gtest/gtest.h>

using retT = double;

using namespace ads::mathematics;

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
    using namespace geometry;

    Curve<3, double> cur(X, Y);
    Vector<3, double> tan = cur.tangent(0.5);
    double c = cur.curvature(0.5);
    Vector<3, double> normal = cur.norm(0);
    Vector<3, double> binormal = cur.binorm(0);
    double rad = cur.curvatureRadius(0);
    double tor = cur.torsion(0);
    
}

TEST(GeometryCurve, Derivative1)
{
    using namespace geometry;
    float accuracy = 0.001f;
    size_t n = 1;
    Curve<3,  double> a(X, Y, Z);
    Vector<3, float> der = a.derivative(1.0, n, accuracy);
    Vector<3, float> answer(.1f, 2.f, 5.f);

    ASSERT_TRUE(isEqual(der, answer, accuracy));
}

TEST(GeometryCurve, Derivative2)
{
    using namespace geometry;
    float accuracy = 0.001f;
    size_t n = 2;
    Curve<3,  double> a(X, Y, Z);
    Vector<3, float> der = a.derivative(1.0, n, accuracy);
    Vector<3, float> answer(0.f, 2.f, 20.f);

    ASSERT_TRUE(isEqual(der, answer, accuracy));
}

TEST(GeometryCurve, Derivative3)
{
    using namespace geometry;
    float accuracy = 0.001f;
    size_t n = 3;
    Curve<3,  double> a(X, Y, Z);
    Vector<3, float> der = a.derivative(1.0, n, accuracy);
    Vector<3, float> answer(0.f, 0.f, 60.f);

    ASSERT_TRUE(isEqual(der, answer, accuracy));
}