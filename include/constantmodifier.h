#ifndef CONSTANTMODIFIER_H
#define CONSTANTMODIFIER_H

#include <string>
#include <boost/regex.hpp>

#include "diceobject.h"


class constantModifier : virtual public diceObject
{
    public:

        static const std::string shape;
        static const boost::regex regexp;

        constantModifier(std::string dats);
        virtual ~constantModifier();

        virtual std::string represent() const;
        virtual std::string represent_wnr() const;
        virtual void retrow() { };
        virtual diceResultFormat Getresult() const {return value;};
        virtual std::vector<diceResultFormat> GetAllresult() const {return {value};};
        virtual std::string GetDetailledResult() const;

    protected:
    private:

    diceResultFormat value;
    bool sgn;
};

#endif // CONSTANTMODIFIER_H
