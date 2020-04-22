
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // Method completed
    // Implement it in one single line!
    // You may need to implement the load method before this!
    loadDB(fileName);
}

Network::~Network(){
    // Method completed
    // Destructure delete all the Person
    Person* temp = head;
    while(temp != NULL){
        temp = temp->next;
        delete head;
        head = temp;
    }
}


void Network::push_front(Person* newEntry){
    // Adds a new Person (newEntry) to the front of LL
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Person* newEntry){
    // Method Completed
    // Adds a new Person (newEntry) to the back of LL
    newEntry->prev = tail;
    newEntry->next = NULL;
    if(head != NULL)
        tail->next = newEntry;
    else
        head = newEntry;
    tail = newEntry;
    count++;
}


void Network::printDB(){
    // Don't change this method
    // Note: Notice that we don't need to update this even after adding to Person attributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of persons: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::saveDB(string filename){
    // Method completed
    // Saves the netwrok in file <filename>
    // Note: The format of the output file is very abstract, just raw data
    // Look at studentDB.txt as a template
    // Note: notice the intentional flaw in this code, as compared to the note mentioned in printDB, 
    // now the one who is responsible for implementing Network should be aware of implementation of Person, not good! You will fix this in PA2. 

    ofstream save_file (filename.c_str());
    Person *temp = head;

    if(save_file.is_open()){
        while(temp != NULL){
            temp->save_person(save_file);
            temp = temp->next;
        }
        save_file.close();
        cout << "Network saved in " << filename << endl;
    }
    else{
        cout << "File couldn't be opened!" << endl;
    }
}


void Network::loadDB(string filename){
    // Method completed
    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them
    // You need to use the following constructor of the Person class, Person::Person(fname, lname, bdate, email, phone)
    
    Person* ptr = head;
    while(head != NULL){
        ptr = head->next;
        delete head;
        head = ptr;
        count--;
    }
    head = NULL;
    tail = NULL;
    ifstream infile;
    infile.open(filename.c_str());
    string buff, fname, lname, bdate, type, temp, email, phone, id;
    size_t start, end;
    vector<string> ids;
    vector< vector<string> > friend_ids;
    
    // TODO: Decalre other vairiable if needed

    while(getline(infile, buff)){
        lname = buff.substr(0, buff.find(','));
        fname = buff.substr(buff.find(',')+2);
        getline(infile, bdate);
        
        // Read in the email info
        getline(infile, email);

        // Read in the phone info
        getline(infile, phone);

        // Read friends into vector of id's
        getline(infile, id);
        while(id[0] != 45 && !infile.eof()){
            ids.push_back(id);
            getline(infile,id);
        }
        friend_ids.push_back(ids);
        ids.clear();

        Person* newEntry = new Person(fname, lname, bdate, email, phone);
        
        this->push_back(newEntry);
    }

    // Add friends
    Person* tmp = head, *f;
    vector< vector<string> >::iterator it = friend_ids.begin();
    vector<string>::iterator iter;
    while(tmp != NULL){
        for(iter = it->begin(); iter != it->end(); iter++){
            f = search(*iter);
            if(f != NULL){
                tmp->addFriend(f);
            }
            else{
                cout << *iter << " could not be found." << endl;
            }
        }
        tmp = tmp->next;
        it++;
    }

    infile.close();
}

Person* Network::search(string fname, string lname, string bdate){
    // Method completed
    // Search the Network for the given fname, lname, bdate
    // You may create a new person, say searchEntry, with fname, lname and bdate. Think about what Person constructor will be helpful with these arguments.
    // And use == overloaded operator between two persons
    // if found, returns a pointer to it, else returns NULL
    // Don't forget to delete allocated memory.

    Person *searchEntry = new Person(fname, lname, bdate, "", "");
    Person *temp = head;

    while(temp != NULL){
        if(*temp == *searchEntry){
            delete searchEntry;
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

Person* Network::search(string queryid){
    Person* temp = head;

    while(temp != NULL){
        if(IDName(temp->f_name, temp->l_name) == queryid) break;
        temp = temp->next;
    }

    return temp;
}

bool Network::remove(string fname, string lname, string bdate){
    // Method completed
    // Create a new person with the the give arguments as you do in search
    // Search if this person exists using search method. If it does not exist just return false! Else, remove the person from LL, make the other connections connected
    // Don't forget to delete allocated memory, change count and returning values!
    Person* toDelete = search(fname, lname, bdate);
    if(toDelete != NULL){
        if(toDelete->prev != NULL){
            toDelete->prev->next = toDelete->next;
        }
        else{
            head = toDelete->next;
        }
        if(toDelete->next != NULL){
            toDelete->next->prev = toDelete->prev;
        }
        else{
            tail = toDelete->prev;
        }
        delete toDelete;
        count--;
        return true;
    }
    else{
        return false;
    }

}

void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Load network database \n";
        cout << "2. Save network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Search \n";
        cout << "5. Remove a person \n";
        cout << "6. Print database \n";
        cout << "7. Add Friends \n";
        cout << "8. Get Friend Recommendations \n";
        
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        vector<string> dbFiles;
        bool exists = false;
        cout << "\033[2J\033[1;1H";

        // Load DB
        if (opt==1){
            cout << "Loading network database \n";
            // Printing all the files in directory with .db
            DIR *dir;
            struct dirent *ent;
            char targetFolderAddr[] = "./";
            if((dir = opendir(targetFolderAddr)) != NULL){
                string temp = "", target = "db";
                size_t pos;
                while((ent = readdir(dir)) != NULL){
                    temp = ent->d_name;
                    pos = temp.find(".");
                    if(temp.substr(pos + 1, 2).compare(target.c_str()) == 0){
                        cout << temp << endl;
                        dbFiles.push_back(temp);
                    }
                }
                closedir(dir);
            }
            else{
                perror("No Directory!");
                return;
            }
            cout << "Enter the name of the load file: ";  
            cin >> fileName;
            for(std::vector<string>::iterator i = dbFiles.begin(); i != dbFiles.end(); ++i){
                if(!(fileName.compare(*i))){
                    exists = true;
                    break;
                }
            }
            // If file with name FILENAME does not exist:
            if(!exists){
                cout << "File FILENAME does not exist!" << endl;
            }
            else{
                // If file is loaded successfully, also print the count of persons in it: 
                loadDB(fileName);
                cout << "Network loaded from " << fileName << " with " << count << " persons \n";
            }
        }
        // Save DB
        else if (opt==2){
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            cin >> fileName;
            saveDB(fileName);
        }
        // Add a person
        else if (opt == 3){
            // Person added at front of list
            // Add a new person ONLY if it does not exists!
            cout << "Adding a new person \n";
            Person* newPerson = new Person();
            fname = newPerson->f_name;
            lname = newPerson->l_name;
            bdate = newPerson->birthdate->get_date();

            if(search(fname, lname, bdate) == NULL){
                push_front(newPerson);
                cout << newPerson->f_name << " " << newPerson->l_name << " has been added.\n";
            }
            else{
                cout << "Person already exists" << endl;
            }
        }
        // Search for a person
        else if (opt == 4){
            cout << "Searching: \n";
            cout << "First Name: ";
            std::getline(std::cin, fname);
            cout << "Last Name: ";
            std::getline(std::cin, lname);
            cout << "Birthdate (M/D/YYYY): ";
            cin >> bdate;
            // if found: print person's firstname, lastname, bdate, email, phone using print_person()
            // if not, cout << "Not found! \n";

            Person* searchedPerson = search(fname, lname, bdate);

            if(searchedPerson != NULL){
                searchedPerson->print_person();
            }
            else{
                cout << "Not found! \n";
            }
        }
        // Remove a person
        else if (opt==5){
            cout << "Removing a person \n";
            cout << "First name: ";
            std::getline(std::cin, fname);
            cout << "Last name: ";
            std::getline(std::cin, lname);
            cout << "Birthdate (M/D/YYYY): ";
            cin >> bdate;
            // if found, cout << "Remove Successful! \n";
            // if not found: cout << "Person not found! \n";

            if(remove(fname, lname, bdate)){
                cout << "Remove Successful! \n";
            }
            else{
                cout << "Person not found! \n";
            }
        }
        // Print DB
        else if (opt==6){
            cout << "Network Database: \n";
            printDB();
        }
        // Add a friend connections
        else if (opt==7){
            cout << "Add friends: " << endl;

            string f1, f2;
            Person* p1, *p2;
            bool check = true;
            cout << "Person 1 ID: ";
            cin >> f1;
            p1 = search(f1);
            // Check if people already exist
            if(p1 != NULL){
                cout << "Person 2 ID: ";
                cin >> f2;
                p2 = search(f2);
                if(p2 == NULL) cout << "Person Not Found" << endl;
                else{
                    // Check if people are already friends
                    vector< Person* >::iterator it;
                    for(it = p1->friends.begin(); it != p1->friends.end(); it++){
                        if(*it == p2){
                            check = false;
                            break;
                        }
                    }
                    if(check){
                        p1->addFriend(p2);
                        p2->addFriend(p1);
                        cout << p1->f_name << " and " << p2->f_name << " are now friends!" << endl;
                    }
                    else{
                        cout << p1->f_name << " and " << p2->f_name << " are already friends." << endl;
                    }
                }
            }
            else cout << "Person Not Found" << endl;
        }
        // Friend Recommendations
        else if (opt==8){
            int k;
            cout << "Input the distance k: " << endl;
            cin >> k;
            if(k > 1){
                friends_recommendation(k);
            }
            else{
                cout << "Please enter a number greater than 1!" << endl;
            }
        }
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}

// Recommend friends for every person in network
void Network::friends_recommendation(int k){

    Person* temp = head;
    vector< Person* >::iterator it;
    vector< Person* > visited;
    vector< string >::iterator it2, it3;
    vector< string > to_recommend, to_recommend_temp;
    bool check = true;
    string cur_id;

    while(temp != NULL){
        // Get friends of current person
        for(it = temp->friends.begin(); it != temp->friends.end(); it++){
            visited.push_back(*it);
        }

        // Recursively get the recommendations from the k nearest neighbors
        to_recommend_temp = recursive_recommendation(k, temp, visited);

        cur_id = IDName(temp->f_name, temp->l_name);
        for(it2 = to_recommend_temp.begin(); it2 != to_recommend_temp.end(); it2++){
            if(*it2 == cur_id) check = false;
            for(it3 = to_recommend.begin(); it3 != to_recommend.end(); it3++){
                if(*it2 == *it3){
                    check = false;
                    break;
                }
            }
            if(check){
                to_recommend.push_back(*it2);
            }
            check = true;
        }

        // Output the recommendations to the user
        cout << temp->f_name << " " << temp->l_name << endl;
        for(it2 = to_recommend.begin(); it2 != to_recommend.end(); it2++){
            cout << *it2 << endl;
        }
        cout << "------------------------------" << endl;

        temp = temp->next;
        visited.clear();
        to_recommend.clear();
        to_recommend_temp.clear();
    }
}

// Recursively find friend recommendations within a distance k in the network
vector< string > Network::recursive_recommendation(int k, Person* temp, vector< Person* > v){
    if(k == 2){
        vector< Person* >::iterator it, iter, iter2;
        vector< Person* > visited;
        vector< string > to_recommend;
        bool rec = true;
        string id_temp;

        for(it = temp->friends.begin(); it != temp->friends.end(); it++){
            visited.push_back(*it);
        }

        // Check if friends of friends are in the current person's friend group
        for(it = visited.begin(); it != visited.end(); it++){
            for(iter = (*it)->friends.begin(); iter != (*it)->friends.end(); iter++){
                id_temp = IDName((*iter)->f_name, (*iter)->l_name);
                for(iter2 = v.begin(); iter2 != v.end(); iter2++){
                    if(id_temp == IDName((*iter2)->f_name, (*iter2)->l_name)){
                        rec = false;
                        break;
                    }
                }
                // Recommend person if they are not already friends with current person
                if(rec) to_recommend.push_back(id_temp);
                rec = true;
            }
        }

        return to_recommend;
    }
    else{
        vector< Person* >::iterator it;
        vector< string > recs, recs_combined;
        recs_combined = recursive_recommendation(2, temp, v);
        // Go through the current person's friends and get their freinds until the k distance is reached
        for(it = temp->friends.begin(); it != temp->friends.end(); it++){
            recs = recursive_recommendation(k - 1, *it, v);
            recs_combined = combine_vecs(recs, recs_combined);
            recs.clear();
        }
        return recs_combined;
    }
}

// Helper function to combine vectors with only the elements that are unique to each vector
vector< string > Network::combine_vecs(vector< string >& v1, vector< string >& v2){
    vector< string >::iterator it, it2;
    bool check = true;
    vector< string > combined;
    for(it = v1.begin(); it != v1.end(); it++){
        combined.push_back(*it);
    }
    for(it = v2.begin(); it != v2.end(); it++){
        for(it2 = v1.begin(); it2 != v1.end(); it2++){
            if(*it == *it2){
                check = false;
                break;
            }
        }
        if(check){
            combined.push_back(*it);
        }
        check = true;
    }

    return combined;
}