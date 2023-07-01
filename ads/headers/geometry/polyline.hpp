/// @file plane.hpp
/// @brief define curve class

#pragma once
#ifndef __POLYLINE_HPP__
#define __POLYLINE_HPP__

#include "vector.hpp"
#include <list>

namespace ads
{
    namespace mathematics
    {
        namespace geometry
        {
            template<typename T>
            class Polyline
            {
                public:
                    
                    Polyline(const std::initializer_list<Vector<3, T>>& listOfPoints) : points_(listOfPoints){}

                    void addPoint(const Vector<3, T>& point)
                    {
                        points_.push_back(point);
                    }

                private:

                    /// @brief List of points
                    std::list<Vector<3, T>> points_;
            };
        } // namespace geometry
    } // namespace mathematics
} // namespace ads

#endif // __POLYLINE_HPP__