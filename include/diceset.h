#ifndef DICESET_H
#define DICESET_H

#include <iostream>
#include <vector>
#include <string>
#include <boost/regex.hpp>

#include "dice.h"
#include "diceobject.h"
#include "string_utility.h"

class diceset : virtual public diceObject
{
    public:

        static const std::string functions_names;
        static const boost::regex diceset_regex;
        static const boost::regex functions_regex;
        static const boost::regex has_function_regex;

        diceset(std::string arg);
        ~diceset();

        virtual std::string represent() const;
        virtual std::string represent_wnr() const;
        virtual unsigned int Getresult() const;
        virtual std::vector<unsigned int> GetAllresult() const;
        virtual std::string GetDetailledResult() const;

        virtual void retrow();

    protected:

        std::string funct;
        std::vector<diceObject*> dices;
};

std::ostream& operator<<(std::ostream& out, diceset ds);

#endif // DICESET_H
