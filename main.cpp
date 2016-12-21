#include <iostream>
#include <string>
#include <regex>

#include "dice.h"
#include "diceset.h"
#include "string_utility.h"

using namespace std;

const string exit_cmd("exit");
const regex exit_regex("( )*exit\\(\\)( )*");


bool isExit(string cmd){
	return regex_match(cmd, exit_regex);
}

string execute(string cmd){

    if(isExit(cmd))
        exit(0);
	else if(regex_match(cmd.c_str(), dice::single_dice_regex)){
        dice d(cmd.c_str());
        return d.represent();
    }
	else if(regex_match(cmd.c_str(), diceset::diceset_regex)){
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

        cout << endl << execute(cmd) << endl << endl;

    }
}
