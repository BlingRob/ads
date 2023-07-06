/// @file plane.hpp
/// @brief define plane class

#pragma once
#ifndef __PLANE_HPP__
#define __PLANE_HPP__

#include "vector.hpp"

namespace ads
{
    namespace mathematics
    {
        namespace geometry
        {
            template<typename T>
            class Plane
            {
                public:

                    Plane(T x, T y, T z, T h) : equation_(x,y,z,h){}

                    Plane(const Vector<4, T>& plane): equation_(plane){}

                    Vector<3, T> Norm()
                    {
                        return equation_.Slice<0,3>();
                    }
                    
                    /// @brief projection vector on plane
                    /// @return projection vector vec on plane
                    Vector<3, T> Proj(const Vector<3, T>& vec)
                    {
                        Vector<3, T> norm = Norm().Norm();
                        
                        return vec - (vec * norm) * norm;
                    }

                private:

                    Vector<4, T> equation_;
            };
        } // namespace geometry
    } // namespace mathematics
} // namespace ads

#endif // __PLANE_HPP__