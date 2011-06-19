#ifndef GFORT_UTILS_H_
#define GFORT_UTILS_H_

#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <ostream>

namespace GFort
{


template<typename T>
std::string ToString(T val) 
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

template<typename A, typename B, typename C>
std::basic_ostream<A,B>& operator<<(std::basic_ostream<A,B>& _s, const std::list<C>& l) {
	std::basic_ostream<A,B>* s = &_s;
	for(typename std::list<C>::const_iterator i = l.begin(); i != l.end(); ++i)
		s = &( *s << *i );
	return *s;
}

template <typename T> 
T CLAMP(const T& num, const T& lowerBound, const T& upperBound) 
{
	return (num < lowerBound) ? lowerBound : (num > upperBound ? upperBound : num); 
}

template <typename T> 
T SIGN(const T& num) 
{ 
    return (num < 0) ? -1 : 1; 
}

template <typename T> 
T LERP(const T& value1, const T& value2, const float& factor)
{
    return value1 + (value2 - value1) * factor;
}

} // namespace

#endif // GFORT_UTILS_H_
