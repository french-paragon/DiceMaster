#include <iostream>
#include <string>
#include <boost/regex.hpp>

#include "dice.h"
#include "diceset.h"
#include "string_utility.h"

using namespace std;

const string exit_cmd("exit");
const boost::regex exit_regex("( )*exit\\(\\)( )*");


bool isExit(string cmd){
    return boost::regex_match(cmd.c_str(), exit_regex);
}

string execute(string cmd){

    if(isExit(cmd))
        exit(0);
    else if(boost::regex_match(cmd.c_str(), dice::single_dice_regex)){
        dice d(cmd.c_str());
        return to_string(d.Getnb()) + "d" + to_string(d.Getfaces()) + " : " + to_string(d.Getresult());
    }
    else if(boost::regex_match(cmd.c_str(), diceset::diceset_regex)){
        diceset d(cmd);

        return d.represent();
    }

    return "Votre commande n'a pas été reconnue!";

}

int main()
{
    srand(time(nullptr));

    string cmd;
    string prompt = "";

    while(1){

        cout << prompt << ">> ";
        getline(cin, cmd);

        cout << execute(cmd) << endl;

    }
}
