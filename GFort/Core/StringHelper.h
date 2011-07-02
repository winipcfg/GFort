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

#ifndef GFORT_CORE_STRING_HELPER_H_
#define GFORT_CORE_STRING_HELPER_H_

#include <vector>
#include <list>

namespace GFort { namespace Core 
{

/// Helper class for String
class StringHelper
{
public:
    /// Tokenizes a string s into tokens. Blank tokens are omitted.
    /// @param s
    /// @param delimiters
    /// @param tokens
    static void Tokenize(const std::string& s,
                         const std::string& delimiters,
                         std::vector<std::string>& tokens);

    /// Tokenizes a string s into tokens. Blank tokens are omitted.
    /// @param s
    /// @param delimiters
    static std::vector<std::string> Tokenize(const std::string& s,
                                             const std::string& delimiters);

    /// Converts and Returns input object to string   
    /// @param object
    template <typename T>
    static std::string ToString(const T& object);

    /// Converts input object to string s
    /// @param object
    /// @param s
    template <typename T>
    static void ToString(const T& object, std::string & s);
};

inline void StringHelper::Tokenize(
    const std::string& s,
    const std::string& delimiters,
    std::vector<std::string>& tokens)
{
    std::string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    std::string::size_type pos = s.find_first_of(delimiters, lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos) 
    {
        tokens.push_back(s.substr(lastPos, pos - lastPos));
        lastPos = s.find_first_not_of(delimiters, pos);
        pos = s.find_first_of(delimiters, lastPos);
    }
}

inline std::vector<std::string> StringHelper::Tokenize(
    const std::string& s,
    const std::string& delimiters)
{
    std::vector<std::string> tokens;
    Tokenize(s, delimiters, tokens);
    return tokens;
}

template <typename T>
inline std::string StringHelper::ToString(const T& object)
{
    std::string s;
    ToString(object, s);
    return s;
}

template<typename A, typename B, typename C>
std::basic_ostream<A,B>& operator<<(std::basic_ostream<A,B>& _s, const std::list<C>& l) 
{
    std::basic_ostream<A,B>* s = &_s;
    for(typename std::list<C>::const_iterator i = l.begin(); i != l.end(); ++i)
        s = &( *s << *i );
    return *s;
}

template <typename T>
inline void StringHelper::ToString(const T& object, std::string& s)
{
    std::ostringstream os;
    os << object;
    s = os.str();
}

} } //namespace

#endif // GFORT_CORE_STRING_HELPER_H_
