#ifndef DICE_H
#define DICE_H


#include <string>
#include <vector>
#include <boost/regex.hpp>

#include "diceobject.h"
#include "string_utility.h"

class dice :  virtual public  diceObject
{
    public:

        static const std::string shape;
        static const boost::regex single_dice_regex;

        dice(unsigned int nb_f = 6, unsigned int nbd = 1);
        dice(const char* d_m);
        dice(std::string d_m);
        dice(const dice& other);
        unsigned int Getfaces() const{ return faces; }
        void Setfaces(unsigned int val) { faces = val; }

        virtual diceResultFormat Getresult() const{ return result; }
        virtual std::vector<diceResultFormat> GetAllresult() const{ return detailed_results;}
        virtual std::string GetDetailledResult() const;

        unsigned int Getnb() const{ return nb; }

        virtual std::string represent() const;
        virtual std::string represent_wnr() const;
        virtual void retrow();

    protected:

    private:
        unsigned int nb;
        unsigned int faces;
        diceResultFormat result;

        std::vector<diceResultFormat> detailed_results;
};

#endif // DICE_H
