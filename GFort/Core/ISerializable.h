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

#ifndef GFORT_CORE_ISERIALIZABLE_H_
#define GFORT_CORE_ISERIALIZABLE_H_

//#include <cstdarg>
#include <list>
#include <string>
#include <boost/serialization/list.hpp>
//#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>

namespace GFort { namespace Core
{

/// Serializable Interface
template <typename T>
class ISerializable
{
protected:
    friend class boost::serialization::access;

    template<class archive>
    virtual void serialize(archive& ar, const unsigned int version) = 0;
};


} } // namespace

#endif //GFORT_CORE_ISERIALIZABLE_H_
