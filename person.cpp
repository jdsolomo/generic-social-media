
#include "person.h"

Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){
    delete birthdate;
    delete email;
    delete phone;
}


Person::Person(string fname, string lname, string bdate, string email, string phone){
    // Method completed
    // phone and email strings are in full version

    f_name = fname;

    l_name = lname;

    birthdate = new Date(bdate);

    size_t start = email.find("("), end = email.find(")");
    string type = email.substr(start + 1, end - start - 1);
    string temp = email.substr(end + 2);
    this->email = new Email(type, temp);

    start = phone.find("("), end = phone.find(")");
    type = phone.substr(start + 1, end - start - 1);
    temp = phone.substr(end + 2);
    this->phone = new Phone(type, temp);
}


Person::Person(string filename){
    set_person(filename);
}


void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // Method completed CHECK FOR SPACES IN PHONE AND EMAIL
    
    string temp;
    string type;

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    std::getline(std::cin,f_name);

	cout << "Last Name: ";
    std::getline(std::cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin,temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    cin >> type;

    cout << "Email address: ";
    cin >> temp;

    email = new Email(type, temp);

    cout << "Type of phone number: ";
    cin >> type;

    cout << "Phone number: ";
    cin >> temp;

    phone = new Phone(type, temp);
}


void Person::set_person(string filename){
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
    // Method completed
    ifstream input_file (filename);

    if(input_file.is_open()){
        string type;
        string temp;
    
        std::getline(input_file, temp);
        f_name = temp;
    
        std::getline(input_file, temp);
        l_name = temp;
    
        std::getline(input_file, temp);
        birthdate = new Date(temp);
    
        input_file >> type;
        size_t start = type.find("("), end = type.find(")");
        type = type.substr(start + 1, end - start - 1);
        input_file >> temp;
        phone = new Phone(type, temp);
    
        input_file >> type;
        start = type.find("(");
        end = type.find(")");
        type = type.substr(start + 1, end - start - 1);
        input_file >> temp;
        email = new Email(type, temp);

        input_file.close();
    }
}


bool Person::operator==(const Person& rhs){
    // Method completed
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)

    if (!(f_name.compare(rhs.f_name)) &&
        !(l_name.compare(rhs.l_name)) &&
        birthdate == rhs.birthdate){
        return true;
    }
    else{
        return false;
    }
}

bool Person::operator!=(const Person& rhs){ 
    // Method completed
    return !(*this == rhs);
}


void Person::print_person(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    email->print();
    phone->print();
}

