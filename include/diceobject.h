#ifndef DICEOBJECT_H
#define DICEOBJECT_H

#include <string>
#include <vector>

class diceObject
{
    public:
        diceObject();
        virtual ~diceObject();

        virtual std::string represent() const {return " ";};
        virtual std::string represent_wnr() const {return " ";};
        virtual void retrow() { };
        virtual unsigned int Getresult() const {return 0;};
        virtual std::vector<unsigned int> GetAllresult() const {return {};};
        virtual std::string GetDetailledResult() const {return " ";};

    protected:
    private:
};

#endif // DICEOBJECT_H
