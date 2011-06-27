//Copyright (C) 2011 by Gavin Fong
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.

#ifndef GFORT_CORE_STRUCTS_H_
#define GFORT_CORE_STRUCTS_H_

#include <cmath>

#include <Eigen/Dense>
#include <Eigen/Geometry>
//#include <boost/numeric/ublas/vector.hpp>

namespace GFort { namespace Core
{

/// Vector class in 2 dimensions
template <typename T>
class Vector2
{
    typedef Eigen::Matrix<T, 2, 1, 0, 2, 1> Point;
    //typedef boost::numeric::ublas::vector<T> Point;

public:
    /// Constructor
    Vector2() {}

    /// Constructor
    /// @param x
    /// @param y
    Vector2(const T& x, const T& y)
    {
        this->point_[0] = x;
        this->point_[1] = y;
    }
    
    /// Copy Constructor
    /// @param p
    Vector2& operator= (const Vector2& p)
    {
        this->point_ = p.point_;
        return *this;
    }
    
    /// Gets the position.
    T X() const                         { return point_.x(); }

    /// Gets the position.
    T Y() const                         { return point_.y(); }

    /// Gets squared distance of a point p to the object. 
    /// @param p
    T Distance(const Vector2& p) const  { return std::sqrt(DistanceSquared(p)); }

    /// Gets squared distance of a point p to the object. 
    /// @param p
    T DistanceSquared(const Vector2& p) const
    { 
        return std::pow((p.point_.x() - this->point_.x()), 2)
            + std::pow((p.point_.y() - this->point_.y()), 2);
    }

public:
    Point point_;
};


/// Rectangle
template <typename T>
struct Rectangle
{
    /// Constructor
    Rectangle() {}

    /// Constructor
    /// @param x
    /// @param y
    /// @param width
    /// @param height
    Rectangle(const T& x, const T& y, const T& width, const T& height) 
    {
        position_ = Vector2<T>(x, y);
        size_ = Vector2<T>(width, height);
    }

    /// Gets the position of the rectangle.
    T X() const             { return position_.x(); }

    /// Gets the position of the rectangle.
    T Y() const             { return position_.y(); }

    /// Gets the width of the rectangle.
    T Width() const         { return size_.x(); }

    /// Gets the height of the rectangle.
    T Height() const        { return size_.y(); }

private:
    Vector2<T>   	position_;
    Vector2<T>      size_;
};

/// Line
template <typename T>
struct Line
{
    typedef Eigen::ParametrizedLine<T, 2> LineType;

public:
    /// Constructor
    Line()
    {
        line_ = LineType::Through(start_.point_, end_.point_);
    }

    /// Constructor
    Line(const Vector2<T>& p0, const Vector2<T>& p1)
    {
        start_ = p0;
        end_ = p1;
        line_ = LineType::Through(p0.point_, p1.point_);
    }

    /// Gets the starting point of the line.
    Vector2<T> StartPoint() const                   { return start_; }

    /// Gets the ending point of the line.
    Vector2<T> EndPoint() const                     { return end_; }

    /// Gets the length of the line.
    T Length() const                                { return std::sqrt(LengthSquared()); } 

    /// Gets the squared length of the line.
    T LengthSquared() const                         { return end_.DistanceSquared(start_); } 

    /// Gets distance of a point p to its projection onto the line. 
    /// @param p
    T Distance (const Vector2<T>& p) const          { return line_.distance(p); }

    /// Gets squared distance of a point p to its projection onto the line. 
    /// @param p
    T DistanceSquared (const Vector2<T>& p) const   { return line_.squaredDistance(p); }

private:
    // Stores the line
    LineType        line_;

    // Stores the start/end point of the line
    Vector2<T>      start_;
    Vector2<T>      end_;
};

} } // namespace

#endif // GFORT_CORE_STRUCTS_H_
