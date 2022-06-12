#include <iostream>
#include "statistics.h"
#include "numberTheory.h"
#include "core.h"
#include "geometry.h"
#include "algebra.h"
#include "calculus.h"

double f(double x)
{
    return x*x - 2;
}

int main()
{
    ads::mathematics::algebra::polynomial p({ 1,2,3,4 }), p2({1,1});
    std::cout <<  p * p2 << std::endl;
    
    std::cout << ads::mathematics::calculus::NewtonMethod(f, 0.0, 10.0) << std::endl;
    //std::cout << ads::statistics::mean(Arr) << " " << ads::statistics::variance(Arr) << " " << ads::statistics::StdDeviation(ads::statistics::variance(Arr)) << std::endl;
    //std::cout << "median " << ads::statistics::median(Arr);
     
    //auto fun = &f;
    //ads::structures::graphs::graph<false,ads::structures::graphs::adjece_list<false>> g(3);
    //g.add_edge(0, 1, 5);
    //g.add_edge(1, 2, 5);
    //g.print();
    //g.del_vertex(2);
    float arr[3] = { 1,2 };
    float* arr2 = new float(1.0f);
    ads::mathematics::geometry::vector<float, 3> vec3(arr);
    ads::mathematics::geometry::vector<float,4> vec(1,2,3),vec2(1,2,3);
    //vec.ptr();
    //vec.z();
    //ads::mathematics::geometry::vector<float, 3> res = vec2 * 2;
    //std::cout << res.y();
    return 0;
}