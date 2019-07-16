/* 
 * File:   DBentry.cpp
 * Author: Sebastian Wardzinski
 * 
 * Created on November 19, 2018, 2:47 PM
 */

#include "DBentry.h"

#include <string>
#include <iostream>

using namespace std;

//Default constructor for DBentry
DBentry::DBentry() {
    name = "0/";
    IPaddress = 0;
    active = false;
}

//Constructor for DBentry that takes 3 arguments
DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active) {
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
    
}

//The destructor for DBentry
DBentry::~DBentry() {}

//Mutator functions
void DBentry::setName(string _name) { name = _name; }
void DBentry::setIPaddress(unsigned int _IPaddress) { IPaddress = _IPaddress; }
void DBentry::setActive(bool _active) { active = _active; }

//Accessor functions
string DBentry::getName() const { return (name); }
unsigned int DBentry::getIPaddress() const { return (IPaddress); }
bool DBentry::getActive() const { return (active); }

//Print function
ostream& operator<< (ostream& out, const DBentry& rhs){
    string act;
    
    if(rhs.getActive()) act = "active";
    else if(!rhs.getActive()) act = "inactive";
    
    out << rhs.name << " : " << rhs.IPaddress << " : " << act ;
    
    return out;
}
