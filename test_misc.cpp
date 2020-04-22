#include <iostream>
#include <string>
#include "misc.h"
using namespace std;

int main(){
	string first_name = "Alexander John Smith    ";
	string last_name = "    Boden-Alvarez Thomas ";
	string id = IDName(first_name, last_name);
	cout << id << endl;
}