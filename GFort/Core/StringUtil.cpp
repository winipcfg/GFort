#include "StringUtil.h"

#include <string>
#include <vector>
#include <sstream>


namespace GFort
{

void StringUtil::Tokenize(const std::string& s,
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

// Tokenizes a string s into tokens. Blank tokens are omitted.
std::vector<std::string> StringUtil::Tokenize(const std::string& s,
                                              const std::string& delimiters)
{
    std::vector<std::string> tokens;
    Tokenize(s, delimiters, tokens);
    return tokens;
}

template <typename T>
std::string StringUtil::ToString(const T& object)
{
    std::string s;
    ToString(object, s);
    return s;
}

template <typename T>
void StringUtil::ToString(const T& object, std::string & s)
{
    std::ostringstream os;
    os << object;
    s = os.str();
}

} // namespace
