#ifndef GFORT_STRING_UTIL_H_
#define GFORT_STRING_UTIL_H_

#include <vector>

namespace GFort
{

/// Utility for string
class StringUtil
{
public:
    // Tokenizes a string s into tokens. Blank tokens are omitted.
    static void Tokenize(const std::string& s,
                         const std::string& delimiters,
                         std::vector<std::string>& tokens);

    // Tokenizes a string s into tokens. Blank tokens are omitted.
    static std::vector<std::string> Tokenize(const std::string& s,
                                             const std::string& delimiters);

    // Converts and Returns input object to string    
    template <typename T>
    static std::string ToString(const T& object);

    // Converts input object to string s
    template <typename T>
    static void ToString(const T& object, std::string & s);
};

class StringUtil;


} //namespace

#endif // GFORT_STRING_UTIL_H_
