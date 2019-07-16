/* 
 * File:   main.cpp
 * Author: Sebastian Wardzinski
 *
 * Created on November 19, 2018, 2:44 PM
 */

#include <iostream>
#include <sstream>
#include <string>

#include "TreeDB.h"

using namespace std;

//I kept the comments sparce in this section since it isn't the main focus of the lab
//Also since its essentially identical to lab 3
int main(){
    
    string line;
    string command, name, active;
    
    bool bactive;
    unsigned int IPaddress;
    
    DBentry* entryPtr;
    
    TreeDB Tree;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input
    
    //Continue asking the user of inputs until eof
    while (!cin.eof()) {
        stringstream  lineStream(line);
        
        lineStream >> command;
        
        if(command == "insert"){
            lineStream >> name;
            
            entryPtr = Tree.find(name);
            if(entryPtr != NULL) cout << "Error: entry already exists" << endl;
            
            //if name doesn't already exist, go ahead and insert
            else {
                lineStream >> IPaddress;
                lineStream >> active;
                
                if(active == "active") bactive = 1;
                else if(active == "inactive") bactive = 0;
                
                entryPtr = new DBentry(name, IPaddress, bactive);
                Tree.insert(entryPtr);
                
                cout << "Success" << endl;
            }
        }
        
        else if(command == "find"){
            lineStream >> name;
            
            entryPtr = Tree.find(name);
            if(entryPtr == NULL) cout << "Error: entry does not exist" << endl;
            
            //if name found, print its details
            else{
                IPaddress = entryPtr->getIPaddress();
                bactive = entryPtr->getActive();
                
                if(bactive) active = "active";
                else active = "inactive";
                
                cout << name << " : " << IPaddress << " : " << active << endl;
            } 
        }
        
        else if(command == "remove"){
            lineStream >> name;
            
            //Remove removes the function and returns true of name exists
            //Otherwise it returns false
            if(Tree.remove(name)) cout << "Success" << endl;
            else{
                cout << "Error: entry does not exist" << endl;
            }
        }
        
        else if(command == "printall"){
            cout << Tree;
        }
        
        else if(command == "printprobes"){
            lineStream >> name;
            
            entryPtr = Tree.find(name);
            if(entryPtr == NULL) cout << "Error: entry does not exist" << endl;
            else Tree.printProbes();
        }
        
        else if(command == "removeall"){
            Tree.clear();
            cout << "Success" << endl;
        }
            
        else if(command == "countactive"){
            Tree.countActive();
        }
        
        else if(command == "updatestatus"){
            lineStream >> name;
            
            entryPtr = Tree.find(name);
            if(entryPtr == NULL) cout << "Error: entry does not exist" << endl;
            
            //if name exists
            else{
                lineStream >> active;
                
                //active member in function is stored as boolean, so I need to convert it
                if(active == "active") bactive = 1;
                else if(active == "inactive") bactive = 0;
                
                entryPtr->setActive(bactive);
                cout << "Success" << endl;
            }
        }
        
        //Ask user for next input
        cout << "> ";
        getline(cin, line);
    }
    
    return 0;
}


