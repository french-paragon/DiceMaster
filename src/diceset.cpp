#include<sstream>
#include<climits>
#include<vector>

#include "diceset.h"
#include "string_utility.h"
#include "vector_utility.h"

using namespace std;

const std::string diceset::functions_names("max|min|mean");
const boost::regex diceset::diceset_regex("^(( )*(" + functions_names + ")\\()?(( )*(([0-9]+d[0-9]+)|[a-z]*\\(?[ 0-9a-zA-Z+()]*\\)?)( )* [+])*( )*(([0-9]+d[0-9]+)|[a-z]*\\(?[ 0-9a-zA-Z+()]*\\)?)( )*(\\))?( )*$");
const boost::regex diceset::functions_regex("^(" + functions_names + ")$");
const boost::regex diceset::has_function_regex("^( )*(" + functions_names + ")\\([ 0-9a-zA-Z+()]*\\)( )*$");

diceset::diceset(string arg_v)
{

    string arg = arg_v;

    if(boost::regex_match(arg.c_str(), has_function_regex)){

        bool ffplace = true;
        bool oPar = true;
        unsigned int spos = 0;

        for(unsigned int i = 0; i<arg.size(); i++){
            if(arg[i] != ' ' && ffplace){
                spos = i;
                ffplace = false;
            }else if(arg[i] == '(' && oPar){
                funct = arg.substr(spos, i-spos);
                oPar = false;
                spos = i+1;
                break;
            }
        }

        for(unsigned int i = arg.size()-1; i > spos; i--){
            if(arg[i] == ')'){
                arg = arg.substr(spos, i-spos);

                break;
            }
        }

    }

    dices = vector<diceObject*>(0);

    unsigned int openPar = 0;
    unsigned int lastId = 0;

    for(unsigned int i = 0; i<arg.size(); i++){

        if(arg[i] == '(')
            openPar++;
        else if (arg[i] == ')')
            openPar--;
        else if (arg[i] == '+' && !openPar){

            //cout << lastId << ' ' << i << endl;

            std::string s = arg.substr(lastId, i-lastId);
            lastId = i+1;

            if(boost::regex_match(s.c_str(), dice::single_dice_regex)){

                dices.push_back(new dice (s.c_str()));

            } else if(boost::regex_match(s.c_str(), diceset::diceset_regex)){

                dices.push_back(new diceset(s));
            }

        }
    }

    std::string s = arg.substr(lastId, s.npos);

    if(boost::regex_match(s.c_str(), dice::single_dice_regex)){

        dices.push_back(new dice(s.c_str()));

    } else if(boost::regex_match(s.c_str(), diceset::diceset_regex)){
        dices.push_back(new diceset(s));
    }

    /*for(unsigned int i = 0; i<dices.size(); i++)
        cout << dices[i]->represent_wnr() << " ";

    cout << endl << endl;*/
}

diceset::~diceset(){
    for(unsigned int i; i<dices.size(); i++)
        delete dices[i];
}

string diceset::represent_wnr() const{

    ostringstream out;
    bool fct = false;

    if(boost::regex_match(funct.c_str(), functions_regex))
        fct = true;

    if(fct)
        out << funct << '(';

    //std::cout << "error" << dices.size() << std::endl;

    for(unsigned int i = 0; i<dices.size(); i++){
        out << dices[i]->represent_wnr();

        if(i != dices.size()-1) out << " + ";
    }


    if(fct)
        out << ")";

    return out.str();
}

string diceset::GetDetailledResult() const{

    ostringstream out;
    bool fct = false;

    if(boost::regex_match(funct.c_str(), functions_regex))
        fct = true;

    if(fct)
        out << funct << '(';

    for(unsigned int i = 0; i<dices.size(); i++){
        out << dices[i]->GetDetailledResult();

        if(i != dices.size()-1) out << " + ";
    }


    if(fct)
        out << ")";

    return out.str();

}

string diceset::represent() const{

    ostringstream out;
    bool fct = false;

    out << represent_wnr();

    out << " = ";

    if(boost::regex_match(funct.c_str(), functions_regex))
        fct = true;

    if(fct)
        out << funct << '(';

    for(unsigned int i = 0; i<dices.size(); i++){
        out << dices[i]->GetDetailledResult();

        if(i != dices.size()-1) out << " + ";
    }

    if(fct)
        out << ")";

    out << " = ";
    out << Getresult();

    return out.str();
}

unsigned int diceset::Getresult() const{

        //std::cout << endl << funct << endl << endl;

        if(funct == "max"){
            unsigned int m = 0;

            for(vector<diceObject*>::const_iterator it = dices.begin(); it != dices.end(); ++it){
                vector<unsigned int> r = (*it)->GetAllresult();
                for(unsigned int i = 0; i<r.size(); i++)
                    if(r[i] > m) m = r[i];
            }

            return m;
        } else if(funct == "min"){
            unsigned int m = UINT_MAX;

            for(vector<diceObject*>::const_iterator it = dices.begin(); it != dices.end(); ++it){
                vector<unsigned int> r = (*it)->GetAllresult();
                for(unsigned int i = 0; i<r.size(); i++)
                    if(r[i] < m) m = r[i];
            }

            return m;
        }else if(funct == "mean"){
            unsigned int m = 0;
            unsigned int s = 0;

            for(vector<diceObject*>::const_iterator it = dices.begin(); it != dices.end(); ++it){
                vector<unsigned int> r = (*it)->GetAllresult();
                for(unsigned int i = 0; i<r.size(); i++)
                    m += r[i];
                s += r.size();
            }

            return m/s;
        }else{
            unsigned int m = 0;

            for(vector<diceObject*>::const_iterator it = dices.begin(); it != dices.end(); ++it){
                vector<unsigned int> r = (*it)->GetAllresult();
                for(unsigned int i = 0; i<r.size(); i++)
                    m += r[i];
            }

            return m;
        }


        return 124556765432;


}

vector<unsigned int> diceset::GetAllresult() const{

        vector<unsigned int> results;

        if(funct == "max"){
            unsigned int m = 0;

            for(vector<diceObject*>::const_iterator it = dices.begin(); it != dices.end(); ++it){
                vector<unsigned int> r = (*it)->GetAllresult();
                for(unsigned int i = 0; i<r.size(); i++)
                    if(r[i] > m) m = r[i];
            }

            results.push_back(m);

            return results;
        } else if(funct == "min"){
            unsigned int m = UINT_MAX;

            for(vector<diceObject*>::const_iterator it = dices.begin(); it != dices.end(); ++it){
                vector<unsigned int> r = (*it)->GetAllresult();
                for(unsigned int i = 0; i<r.size(); i++)
                    if(r[i] < m) m = r[i];
            }

            results.push_back(m);

            return results;
        }else if(funct == "mean"){
            unsigned int m = 0;
            unsigned int s = 0;

            for(vector<diceObject*>::const_iterator it = dices.begin(); it != dices.end(); ++it){
                vector<unsigned int> r = (*it)->GetAllresult();
                for(unsigned int i = 0; i<r.size(); i++)
                    m += r[i];
                s += r.size();
            }

            results.push_back(m/s);

            return results;
        }else{
            unsigned int m = 0;

            for(vector<diceObject*>::const_iterator it = dices.begin(); it != dices.end(); ++it){
                vector<unsigned int> r = (*it)->GetAllresult();
                for(unsigned int i = 0; i<r.size(); i++)
                    results.push_back(r[i]);
            }

            return results;
        }

        return results;

}

ostream& operator<<(ostream& out, diceset const& ds){
    return out << ds.represent();
}

void diceset::retrow() {

    for(unsigned int i = 0; i < dices.size(); i++)
        dices[i]->retrow();

}
