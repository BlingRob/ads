// \\\ file graphs.h
// \\\ It's file for testing opportunities
#include <iostream>
#include "statistics.h"
#include "numberTheory.h"
#include "core.h"
#include "geometry.h"
#include "algebra.h"


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


//struct PointCmp {
//    bool operator()(const ads::mathematics::geometry::vector<2, double>& lhs, const ads::mathematics::geometry::vector<2,double>& rhs) const {
//        return lhs[0] < rhs[0];
//    }
//};

// TODO
// Separet on tests case
int main()
{

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

    /*ads::mathematics::geometry::curve<3, double> cur(f,f1);
    ads::mathematics::geometry::vector<3, double> tan = cur.tangent(0.5);
    double c = cur.curvature(0.5);
    ads::mathematics::geometry::vector<3, double> normal = cur.norm(0);
    ads::mathematics::geometry::vector<3, double> binormal = cur.binorm(0);
    double rad = cur.curvatureRadius(0);
    double tor = cur.torsion(0);
    ads::mathematics::geometry::ellipse<3, double> el(2, 2);
    std::set<ads::mathematics::geometry::vector<2,double>, PointCmp> points;
    ads::mathematics::geometry::circle<2,double> cir(2.0);
    //ads::mathematics::geometry::curve c({ f,f1,f2 });
    //for (double t = -ads::mathematics::Pi; t < ads::mathematics::Pi; t += 0.1)
    //    points.insert({ t,cir.eval(t) });
    points.insert(ads::mathematics::geometry::vector < 2,double>(321,2.50651));
    points.insert(ads::mathematics::geometry::vector < 2,double>(322.8,2.50893 ));
    points.insert(ads::mathematics::geometry::vector < 2,double>(324.2,2.51081 ));
    points.insert(ads::mathematics::geometry::vector < 2,double>(325,2.51188 ));
    ads::mathematics::geometry::curve<2,double> splain = LagrangeSplain(points);
    ads::mathematics::geometry::curve<2,double> splain2 = NewtonSplain(points);
    ads::mathematics::geometry::curve<2, double> splain3 = BazieSplain(points);
    double res = splain.eval(323.5)[1];//2.50987
    double res2 = splain2.eval(323.5)[1];//2.50987
    double res3 = splain3.eval(323.5)[1];*/

    return 0;
}