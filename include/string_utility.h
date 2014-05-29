#ifndef STRING_UTILITY_H_INCLUDED
#define STRING_UTILITY_H_INCLUDED

#include "diceset.h"

template<typename Ty>
std::string to_string( Ty const& Value ) ;

std::vector<std::string> explode (std::string input, std::string separator);

#endif // STRING_UTILITY_H_INCLUDED
