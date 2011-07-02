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

#ifndef GFORT_CORE_MATH_HELPER_H_
#define GFORT_CORE_MATH_HELPER_H_

#include <boost/math/constants/constants.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <cmath>

namespace GFort { namespace Core 
{

/// Helper class for Math
class MathHelper
{
public:
    //=====================================================================
    // Random
    //=====================================================================

    /// Generate a random double between [0, 1]
    static double RandomDouble()            { return rand() / (double)RAND_MAX; }

    /// Generate a variable between [min, max]
    /// @param gen
    /// @param min
    /// @param max
    template <typename T>
    static T RandomBetween(boost::rand48& gen, const T& min, const T& max);

    /// Generate a variable between [min, max]
    /// @param min
    /// @param max
    template <typename T>
    static T RandomBetween(const T& min, const T& max);

    /// Generate a random point in concentric 2d circle
    /// @param gen
    /// @param innerRadius
    /// @param outerRadius
    /// @param outX
    /// @param outY
    template <typename T>
    static void RandomPointInConcentricCircle(
        boost::rand48& gen,
        const T& innerRadius, 
        const T& outerRadius,
        T& outX,
        T& outY);

    /// Generate a random point on 2d circle
    /// @param gen
    /// @param radius
    /// @param outX
    /// @param outY
    template <typename T>
    static void RandomPointOnCircle(
        boost::rand48& gen,
        const T& radius,
        T& outX,
        T& outY);

    //=====================================================================
    // Linear
    //=====================================================================

    /// Returns linear interpolation value of 2 values.
    /// @param value1
    /// @param value2
    /// @param factor
    template <typename T> 
    static T Lerp(const T& value1, const T& value2, const float& factor);

    /// Returns bounded value.
    /// @param value Input data
    /// @param lowerBound
    /// @param upperBound
    template <typename T> 
    static T Clamp(const T& value, const T& lowerBound, const T& upperBound);

    //=====================================================================
    // General
    //=====================================================================

    /// Returns -1 if it is negative value. Else returns 1.
    /// @param value
    template <typename T> 
    static T Sign(const T& value)           { return (value < 0) ? -1 : 1; }
};

template <typename T>
inline T MathHelper::RandomBetween(boost::rand48& gen, const T& min, const T& max)
{
    boost::uniform_real<T> mode(min, max);
    boost::variate_generator<
        boost::rand48&, 
        boost::uniform_real<T> 
    > vg(gen, mode);
    return vg();
}

template <typename T>
inline T MathHelper::RandomBetween(const T& min, const T& max)
{
    return min + RandomDouble() * (max - min);
}

template <typename T>
inline void MathHelper::RandomPointInConcentricCircle(
    boost::rand48& gen,
    const T& innerRadius, 
    const T& outerRadius,
    T& outX,
    T& outY)
{
    // Find the random distance to the center
    T distance = GFort::Core::MathHelper::RandomBetween(gen, innerRadius, outerRadius);

    // Find the random angle in radian
    float angle = GFort::Core::MathHelper::RandomBetween(gen, 1.0f, 2.0f * boost::math::constants::pi<float>());

    outX = static_cast<T>(cos(angle) * distance);
    outY = static_cast<T>(sin(angle) * distance);
}

template <typename T>
inline void MathHelper::RandomPointOnCircle(
    boost::rand48& gen,
    const T& radius, 
    T& outX,
    T& outY)
{
    return RandomPointInConcentricCircle(gen, radius, radius, outX, outY);
}

template <typename T> 
inline T MathHelper::Lerp(const T& value1, const T& value2, const float& factor)
{
    return value1 + (value2 - value1) * factor;
}

template <typename T> 
inline T MathHelper::Clamp(const T& value, const T& lowerBound, const T& upperBound) 
{
	return (value < lowerBound) ? lowerBound : (value > upperBound ? upperBound : value); 
}

} } // namespace

#endif // GFORT_CORE_MATH_HELPER_H_
