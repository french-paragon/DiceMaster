#include <iostream>
#include <string>
#include<sstream>

#include "dice.h"
#include "diceset.h"
#include "string_utility.h"

const std::string dice::shape("( )*[+-]?( )*([0-9]+d[0-9]+)( )*");
const std::regex dice::single_dice_regex("^" + dice::shape + "$");

dice::dice(unsigned int nb_f, unsigned int nbd): nb(nbd), faces(nb_f)
{
    //ctor
    result = 0;
    detailed_results = std::vector<unsigned int>(0);
    for(unsigned int i = 0; i<nb; i++){
        unsigned int r = (rand()%faces) + 1;
        detailed_results.push_back(r);
        result += r;
    }
}

dice::dice(const char* d_m)
{

    char* p = nullptr;

    nb = strtol(d_m, &p, 10);
    faces = strtol(p+1, nullptr, 10);
    result = 0;

    for(unsigned int i = 0; i<nb; i++){
        unsigned int r = (rand()%faces) + 1;
        detailed_results.push_back(r);
        result += r;
    }

}

dice::dice(std::string d_m) : dice(d_m.c_str()){

}

dice::dice(const dice& other): nb(other.Getnb()), faces(other.Getfaces()), result(other.Getresult())
{
    //copy ctor
}

std::string dice::represent() const{
    std::ostringstream out;

    out << nb << 'd' << faces << " = " << GetDetailledResult() << " = " << result;

    return out.str();
}

std::string dice::represent_wnr() const{
    std::ostringstream out;

    out << nb << 'd' << faces;

    return out.str();
}

std::string dice::GetDetailledResult() const{

    std::ostringstream out;

    for(unsigned int i = 0; i<detailed_results.size(); i++){
        out << detailed_results[i];

        if(i != detailed_results.size()-1) out << " + ";
    }

    return out.str();
}

void dice::retrow() {

    result = 0;
    detailed_results.clear();
    for(unsigned int i = 0; i<nb; i++){
        unsigned int r = (rand()%faces) + 1;
        detailed_results.push_back(r);
        result += r;
    }

}
