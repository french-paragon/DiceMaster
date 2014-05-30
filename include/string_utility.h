#ifndef STRING_UTILITY_H_INCLUDED
#define STRING_UTILITY_H_INCLUDED

#include<string>

#include "diceset.h"

template<typename T>
std::string to_string( T const& Value ) ;

std::vector<std::string> explode (std::string input, std::string separator);

#endif // STRING_UTILITY_H_INCLUDED
