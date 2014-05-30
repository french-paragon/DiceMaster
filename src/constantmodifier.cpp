#include "constantmodifier.h"
#include "string_utility.h"

#include <sstream>

const std::string constantModifier::shape("( )*[+]?( )*[0-9]+( )*");
const boost::regex constantModifier::regexp ("^" + constantModifier::shape + "$");

constantModifier::constantModifier(std::string dats)
{

    value = std::stoi(dats);

}

constantModifier::~constantModifier()
{
    //dtor
}

std::string constantModifier::represent() const{

    std::ostringstream oss;
    // écrire la valeur dans le flux
    oss << value;
    // renvoyer une string
    return oss.str();

}

std::string constantModifier::represent_wnr() const{

    return represent();

}

std::string constantModifier::GetDetailledResult() const{

    return represent();

}
