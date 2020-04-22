
#include "misc.h"

void printMe(string type){
    if (type == "banner"){
        char banner[] = \
"   ######## ########   #######        ##    ###    ##    ##         ########   #######   #######  ##    ## \n \
     ##    ##     ## ##     ##       ##   ## ##   ###   ##         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ## ##     ##       ##  ##   ##  ####  ##         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ########  ##     ##       ## ##     ## ## ## ## ####### ########  ##     ## ##     ## ##### \n \
     ##    ##   ##   ##     ## ##    ## ######### ##  ####         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ##    ##  ##     ## ##    ## ##     ## ##   ###         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ##  #######   ######  ##     ## ##    ##         ########   #######   #######  ##    ##\n";
        cout << endl << banner << endl << endl;
    }
}

string IDName(string str1, string str2){
    string id = str2 + str1;
    id = removeSpaces(id);
    id = toLower(id);
    return id;
}

string removeSpaces(string str){
    int len = str.length();
    string s = "";
    char c;
    for(int i = 0; i < len; i++){
        c = str[i];
        if(c != 32) s += c;
    }
    return s;
}

string toLower(string str){
    int len = str.length();
    string s = "";
    char c;
    for(int i = 0; i < len; i++){
        if(str[i] == 45) s += "-";
        else if(str[i] < 97){
            c = str[i] + 32;
            s += c;
        }
        else{
            c = str[i];
            s += c;
        }
    }
    return s;
}