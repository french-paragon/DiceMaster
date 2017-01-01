#ifndef DICEOBJECT_H
#define DICEOBJECT_H

#include <string>
#include <vector>

typedef unsigned int diceResultFormat;

class diceObject
{
    public:
        diceObject();
        virtual ~diceObject();

		virtual std::string represent() const {return " ";}
		virtual std::string represent_wnr() const {return " ";}
		virtual void retrow() { }
		virtual diceResultFormat Getresult() const {return 0;};
		virtual std::vector<diceResultFormat> GetAllresult() const {return {};}
		virtual std::string GetDetailledResult() const {return " ";}

        void setSign(int sgn){
            sign = (sgn < 1) ? -1 : 1;
        }

        int getSign() const{ return (int) sign;}

    protected:
    private:

    char sign;
};

#endif // DICEOBJECT_H
