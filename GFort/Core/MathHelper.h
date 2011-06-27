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
    template <typename T>
    static T RandomBetween(boost::rand48& gen, const T& min, const T& max);

    /// Generate a variable between [min, max]
    template <typename T>
    static T RandomBetween(const T& min, const T& max);

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
    static T Sign(const T& value)           { return (num < 0) ? -1 : 1; }
};

template <class T>
T MathHelper::RandomBetween(boost::rand48& gen, const T& min, const T& max)
{
    boost::uniform_real<T> mode(min, max);
    boost::variate_generator<
        boost::rand48&, 
        boost::uniform_real<T> 
    > vg(gen, mode);
    return vg();
}

template <class T>
T MathHelper::RandomBetween(const T& min, const T& max)
{
    return min + RandomDouble() * (max - min);
}

template <typename T> 
T MathHelper::Lerp(const T& value1, const T& value2, const float& factor)
{
    return value1 + (value2 - value1) * factor;
}

template <typename T> 
T MathHelper::Clamp(const T& value, const T& lowerBound, const T& upperBound) 
{
	return (value < lowerBound) ? lowerBound : (value > upperBound ? upperBound : value); 
}

} } // namespace

#endif // GFORT_CORE_MATH_HELPER_H_
