#include <iostream>
#include "contact.h"
using namespace std;

int main(){
	// Test Email Class
	Email p1("USC","jdsolomo@usc.edu");
	string p1_info = p1.get_contact("");
	cout << "Person 1's email address is " << p1_info << endl;
	cout << "----------------\n";
	p1.set_contact();
	p1.print();
	cout << "----------------\n";

	// Test Phone Class
	Phone p2("USC", "4126809243");
	string p2_info = p2.get_contact("");
	cout << "Person 2's phone number is " << p2_info << endl;
	cout << "----------------\n";
	p2.set_contact();
	p2.print();

}