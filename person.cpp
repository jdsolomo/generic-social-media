
#include "person.h"

// Person Constructor
Person::Person(){
    set_person();
}

// Person Destructor
Person::~Person(){
    delete birthdate;
    delete email;
    delete phone;
}

// Person Contructor with params
Person::Person(string fname, string lname, string bdate, string email, string phone){
    // phone and email strings are in full version

    f_name = fname;

    l_name = lname;

    birthdate = new Date(bdate);

    string type = "Deafult", temp = "1234567890";

    size_t start = email.find("("), end = email.find(")");
    if(start != std::string::npos && end != std::string::npos){
        type = email.substr(start + 1, end - start - 1);
        temp = email.substr(end + 2);
    }
    this->email = new Email(type, temp);

    start = phone.find("("), end = phone.find(")");
    if(start != std::string::npos && end != std::string::npos){
        type = phone.substr(start + 1, end - start - 1);
        temp = phone.substr(end + 2);
    }
    this->phone = new Phone(type, temp);
}

// Person Constructor with file
Person::Person(string filename){
    set_person(filename);
}

// Prompts user for info to create new Person
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

// Gathers info from file to create new Person
void Person::set_person(string filename){
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
    ifstream input_file(filename.c_str());


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

// Determines if two people are equal independent of case
bool Person::operator==(const Person& rhs){
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)
    string f1 = toLower(f_name), l1 = toLower(l_name);
    string f2 = toLower(rhs.f_name), l2 = toLower(rhs.l_name);

    if (!(f1.compare(f2)) &&
        !(l1.compare(l2)) &&
        *birthdate == *(rhs.birthdate)){
        return true;
    }
    else{
        return false;
    }
}

// Determines if two people are not equal independent of case
bool Person::operator!=(const Person& rhs){ 
    return !(*this == rhs);
}

// Prints a Person object
void Person::print_person(){
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    email->print();
    phone->print();
    vector<Person*>::iterator it;
    for(it = friends.begin(); it != friends.end(); it++){
        cout << IDName((*it)->f_name, (*it)->l_name) << endl;
    }
}

// Adds a friend to the Person's friends vector
void Person::addFriend(Person* newFriend){
    friends.push_back(newFriend);
}

// Saves a Person's info to a file
void Person::save_person(ofstream &outfile){
    outfile << l_name << ", " << f_name << "\n";
    outfile << birthdate->get_date() << "\n";
    outfile << email->get_contact() << "\n";
    outfile << phone->get_contact() << "\n";
    vector<Person*>::iterator it;
    for(it = friends.begin(); it != friends.end(); it++){
        outfile << IDName((*it)->f_name, (*it)->l_name) << "\n";
    }
    outfile << "------------------------\n";
}