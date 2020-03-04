#include "contact.h"

Email::Email(string type, string email_addr){
    // TODO: Complete me!
    this->type = type;
    this->email_addr = email_addr;
}


void Email::set_contact(){
    // TODO: Do not change the prompts!
	
    cout << "Enter the type of email address: ";
    cin >> type;
    cout << "Enter email address: ";
    cin >> email_addr;
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    // emaple: Email (USC): tommytrojan@usc.edu
    if (style=="full")
	    return "(" + type + ") " + email_addr;
    else 
        return email_addr;
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


Phone::Phone(string type, string num){
    // Method completed, but CHECK THAT phone_num TYPE IS OK

    /* Note: Modify the following code can help you implementing this function
     * This code has a bug, can you understand why?
    long int area_code = atoi(num.substr(0, 3).c_str());
    long int  number = atoi(num.substr(3).c_str()); 
    this->phone_num = area_code*10000000 + number; 
    */

    this->type = type;

    // Account for possibility of a "(" or ")" in the num string
    std::size_t pos = num.find("(");
    if(pos != std::string::npos){
        num.erase(pos);
    }
    pos = num.find(")");
    if(pos != std::string::npos){
        num.erase(pos);
    }

    // Account for the possibility of a "-" in the num string
    pos = num.find("-");
    while(pos != std::string::npos){
        num.erase(pos);
        pos = num.find("-");
    }

    // Check that the number has enough digits
    if(num.length() > 10 || num.length() < 8){
        cout << "INIT FAILED" << endl;
        cout << "Phone number set to default" << endl;
        phone_num = "1234567890";
    }
    else {
        phone_num = num;
    }
}


void Phone::set_contact(){
    // Method Completed
    string type = "", num = "";
	cout <<"Enter the type of phone number: ";
    cin >> type;
	cout << "Enter the phone number: ";
    cin >> num;

    this->type = type;

    // Account for possibility of a "(" or ")" in the num string
    std::size_t pos = num.find("(");
    if(pos != std::string::npos){
        num.erase(pos,1);
    }
    pos = num.find(")");
    if(pos != std::string::npos){
        num.erase(pos,1);
    }

    // Account for the possibility of a "-" in the num string
    pos = num.find("-");
    while(pos != std::string::npos){
        num.erase(pos,1);
        pos = num.find("-");
    }

    // Check that the number has enough digits
    if(num.length() > 10 || num.length() < 8){
        cout << "INIT FAILED" << endl;
        cout << "Phone number set to default" << endl;
        phone_num = "1234567890";
    }
    else {
        phone_num = num;
    }

}


string Phone::get_contact(string style){
    // Method Completed
    // follow the format of this example: Phone (Office): 310-192-2847

    /* Note: Modify the following code can help you implementing this function
     * This code has a bug, can you understand it!
    int x1 = (phone_num/10000000);
	int x2 = ((phone_num)/10000)%1000;
	int x3 = phone_num%10000;
    */ 

    if (style=="full")
        return "(" + type + ") " + phone_num;
    else 
        return phone_num;
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


