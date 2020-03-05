
#ifndef NETWORK_H
#define NETWORK_H

#include "person.h"
#include "date.h"
// You may need to add more libraries 
#include <dirent.h>
#include <stdlib.h>
#include <vector>
class Network{

    private:
        Person* head;
        Person* tail;
        int count; 
        Person* search(string fname, string lname, string bdate);

    public:
        Network();
        Network(string fileName);
        ~Network();
        void push_front(Person* newEntry);
        void push_back(Person* newEntry);
        bool remove(string fname, string lname, string bdate);
        void saveDB(string filename);
        void loadDB(string filename);
        void printDB();
        void showMenu();
};

#endif
