#include <iostream>
#include "statistics.h"
#include "numberTheory.h"
#include "core.h"
#include "geometry.h"
#include "algebra.h"
#include "calculus.h"

using retT = double;

retT f(retT x)
{
    return x;
}

retT f1(retT x)
{
    return x * x;
}

retT f2(retT x)
{
    return x * x * x * x * x;
}


struct PointCmp {
    bool operator()(const ads::mathematics::geometry::vector<double, 2>& lhs, const ads::mathematics::geometry::vector<double, 2>& rhs) const {
        return lhs[0] < rhs[0];
    }
};

int main()
{
   // ads::mathematics::algebra::polynomial p({ 1,2,3,4 }), p2({1,1});
   // std::cout <<  p * p2 << std::endl;
    
   // std::cout << ads::mathematics::calculus::NewtonMethod(f, 0.0, 10.0) << std::endl;
    //std::cout << ads::statistics::mean(Arr) << " " << ads::statistics::variance(Arr) << " " << ads::statistics::StdDeviation(ads::statistics::variance(Arr)) << std::endl;
    //std::cout << "median " << ads::statistics::median(Arr);
     
    //auto fun = &f;
    //ads::structures::graphs::graph<false,ads::structures::graphs::adjece_list<false>> g(3);
    //g.add_edge(0, 1, 5);
    //g.add_edge(1, 2, 5);
    //g.print();
    //g.del_vertex(2);
    /*float arr[3] = {1,2};
    float* arr2 = new float(1.0f);
    ads::mathematics::geometry::vector<float, 3> vec3(arr);
    ads::mathematics::geometry::vector<float,3> vec(1,2,3),vec2(1,2,3);
    ads::mathematics::geometry::matrix<float, 3> mat1(1.0f), mat2({ { 1,2,3 }, {1,2,3},{1,2,3} });
    ads::mathematics::geometry::matrix<float, 3> mat3 = mat2 * mat1;
    ads::mathematics::geometry::vector<float, 3> vec4 = mat2 * vec;*/
    //vec.ptr();
    //vec.z();
    //ads::mathematics::geometry::vector<float, 3> res = vec2 * 2;
    //std::cout << res.y();
    /*ads::mathematics::geometry::curve<double, 3> a(f, f1, f2);
    ads::mathematics::geometry::vector<float, 3> t = static_cast<ads::mathematics::geometry::vector<float, 3>>(a.derivative(1.0,2,.001));

    ads::mathematics::geometry::curve<double, 3> cur(f,f1);
    ads::mathematics::geometry::vector<double, 3> tan = cur.tangent(0.5);
    double c = cur.curvature(0.5);
    ads::mathematics::geometry::vector<double, 3> normal = cur.norm(0);
    ads::mathematics::geometry::vector<double, 3> binormal = cur.binorm(0);
    double rad = cur.curvatureRadius(0);
    double tor = cur.torsion(0);
    ads::mathematics::geometry::ellipse<double, 3> el(2, 2);*/
    std::set<ads::mathematics::geometry::vector<double, 2>, PointCmp> points;
    ads::mathematics::geometry::circle<double, 2> cir(2.0);
    //ads::mathematics::geometry::curve c({ f,f1,f2 });
    //for (double t = -ads::mathematics::Pi; t < ads::mathematics::Pi; t += 0.1)
    //    points.insert({ t,cir.eval(t) });
    points.insert(ads::mathematics::geometry::vector < double, 2>(321,2.50651));
    points.insert(ads::mathematics::geometry::vector < double, 2>(322.8,2.50893 ));
    points.insert(ads::mathematics::geometry::vector < double, 2>(324.2,2.51081 ));
    points.insert(ads::mathematics::geometry::vector < double, 2>(325,2.51188 ));
    ads::mathematics::geometry::curve<double, 2> splain = LagrangeSplain(points);
    ads::mathematics::geometry::curve<double, 2> splain2 = NewtonSplain(points);
    double res = splain.eval(323.5)[1];//2.50987
    double res2 = splain2.eval(323.5)[1];//2.50987
    return 0;
}