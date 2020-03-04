#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>
// TODO: You may need to add other libraries here!
using namespace std;


class Contact {
    // Made protected to allow derived classes to access type
protected:	
	string type;
public:
    // the following functions are pure virtual functions
	virtual void print() = 0;
    virtual string get_contact(string style="full") = 0;
	virtual void set_contact() = 0;
};


class Email: public Contact{
private:
    string email_addr;
public:
    Email(string type, string email_addr);
    // Implementations of base class
    void print();
    string get_contact(string style="full");
    void set_contact();
};


class Phone: public Contact{
private:
    // switched data type to string (might switch to long) 
	string phone_num; 
public:
    Phone(string type, string phone_number);
    // Implementation of base class
    void print();
    string get_contact(string style="full");
    void set_contact();
};

#endif
