#include <vector>
#include <sstream>
#include <string>

#include "string_utility.h"
#include "diceset.h"

template<class T>
std::string to_string( T const& Value ) {
    // utiliser un flux de sortie pour créer la chaîne
    std::ostringstream oss;
    // écrire la valeur dans le flux
    oss << Value;
    // renvoyer une string
    return oss.str();
}

std::vector<std::string> explode (std::string input, std::string separator){

    unsigned int s = separator.length();
    unsigned int next_id = 0;

    unsigned int jump = input.find(separator, next_id);

    std::vector<std::string> r = {input.substr(next_id, jump-next_id)};

    while(jump < input.length()){
        next_id = jump + s;
        jump = input.find(separator, next_id+1);

        r.push_back(input.substr(next_id, jump-next_id));
    }

    return r;

}
