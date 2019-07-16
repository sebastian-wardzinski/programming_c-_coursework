//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented 
// everytime a shape is successfully created
int shapeCount = 0;


// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

int main() {

    string line;
    string command;
    
    string name, type, firstprompt; 
    int locx, locy, sizex, sizey, angle, objNum, anInt;
    bool nameExists, invalidName, validType, oneArg;    //these are all flags
    
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input
    
    stringstream firstInput (line);
    firstInput >> command;
    firstInput >> max_shapes;
    
    shapesArray = new shape*[max_shapes];       //dynamically creates an array of the size inputted
    
    cout << "New database: max shapes is " << max_shapes << endl;
    
    cout << "> ";          // Prompt for input
    getline(cin, line);   // Get the command line
    
    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;
        
        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        if(command == "create"){
            
            //resets flags
            nameExists = false;
            invalidName = false; 
            oneArg = false;
                    
            if(lineStream.peek(), lineStream.eof()) oneArg = true;  //checks if there's one argument
            
            lineStream >> name;
            
            for(int i = 0; i<7; i++) if(name == keyWordsList[i]) invalidName = true;
            for(int i = 0; i<3; i++) if(name == shapeTypesList[i]) invalidName = true;
            for(int i = 0; i<shapeCount; i++){
                if((shapesArray[i]!= NULL) && (name == shapesArray[i]->getName())) nameExists = true;
            }
            
            //checks all the errors one by one in the right order
            if(lineStream.fail() && !(lineStream.eof())) cout << "Error: invalid argument" << endl;
            else if(invalidName) cout << "Error: invalid shape name" << endl;
            else if(nameExists && !oneArg) cout << "Error: shape name exists" << endl;    //if there's one argument you want to avoid the variables based on previous name
            else if(lineStream.peek(), lineStream.eof()) cout << "Error: too few arguments" << endl;
            else if(shapeCount == max_shapes) cout << "Error: shape array is full" << endl;
            
            // if all the errors are avoided move onto the next argument
            else{
                validType  = false;
                
                lineStream >> type;
                
                for(int i = 0; i<3; i++) if(type == shapeTypesList[i]) validType = true;
                
                //checks all the necessary errors in the right order
                if(lineStream.fail()&& !(lineStream.eof())) cout << "Error: invalid argument" << endl; 
                else if(!validType) cout << "Error: invalid shape type" << endl;
                else if(lineStream.peek(), lineStream.eof()) cout << "Error: too few arguments" << endl;
                
                //next argument, etc.
                else{
                    lineStream >> locx;
                    
                    if(lineStream.fail()&& !(lineStream.eof())) cout << "Error: invalid argument" << endl;
                    else if(locx < 0) cout << "Error: invalid value" << endl;
                    else if(lineStream.peek(), lineStream.eof()) cout << "Error: too few arguments" << endl;
                    
                    else{
                        lineStream >> locy;
                        
                        if(lineStream.fail()&& !(lineStream.eof())) cout << "Error: invalid argument" << endl;
                        else if(locy < 0) cout << "Error: invalid value" << endl;
                        else if(lineStream.peek(), lineStream.eof()) cout << "Error: too few arguments" << endl;
                        
                        else{
                            lineStream >> sizex;

                            if(lineStream.fail()&& !(lineStream.eof())) cout << "Error: invalid argument" << endl;
                            else if(sizex < 0) cout << "Error: invalid value" << endl;
                            else if(lineStream.peek(), lineStream.eof()) cout << "Error: too few arguments" << endl;
                            
                            else{
                                lineStream >> sizey;

                                if(lineStream.fail()&& !(lineStream.eof())) cout << "Error: invalid argument" << endl;
                                else if(sizey < 0) cout << "Error: invalid value" << endl;
                                else if (!lineStream.peek(), !lineStream.eof()) cout << "Error: too many arguments" << endl;
                                
                                else{
                                    shapesArray[shapeCount] = new shape(name, type, locx, locy, sizex, sizey);  //call the constructor with all of the variables you've collected
                                    shapeCount ++;      //keeps track of all of the shapes that were created
                                    cout << "Created " << name << ": " << type << " " << locx << " " << locy << " " << sizex << " " << sizey << endl;                                
                                }
                            }
                        }
                    }
                }
            } 
        }
        
        else if(command == "move"){
            
            //reset flags
            nameExists = false;
            invalidName = false;
            oneArg = false;
                    
            if(lineStream.peek(), lineStream.eof()) oneArg = true;
            
            lineStream >> name;
            
            for(int i = 0; i<7; i++) if(name == keyWordsList[i]) invalidName = true;
            for(int i = 0; i<3; i++) if(name == shapeTypesList[i]) invalidName = true;
            for(int i = 0; i<shapeCount; i++){
                if((shapesArray[i]!= NULL) && (name == shapesArray[i]->getName()) && (nameExists == false)){
                    objNum = i;     //finds the index number for the object of interest
                    nameExists = true;     //lets us know that the object was found
               }
            }
            
            if(lineStream.fail()&& !(lineStream.eof())) cout << "Error: invalid argument" << endl;
            else if(invalidName) cout << "Error: invalid shape name" << endl;
            else if(!nameExists && !oneArg) cout << "Error: shape " << name << " not found" << endl;    //if there's one argument you want to avoid the variables based on previous name
            else if(lineStream.peek(), lineStream.eof()) cout << "Error: too few arguments" << endl;
            
            else{
                lineStream >> locx;
                    
                if(lineStream.fail()&& !(lineStream.eof())) cout << "Error: invalid argument" << endl;
                else if(locx < 0) cout << "Error: invalid value" << endl;
                else if(lineStream.peek(), lineStream.eof()) cout << "Error: too few arguments" << endl;
                
                else{
                    lineStream >> locy;
                        
                    if(lineStream.fail()&& !(lineStream.eof())) cout << "Error: invalid argument" << endl;
                    else if(locy < 0) cout << "Error: invalid value" << endl;
                    else if(!lineStream.peek(), !lineStream.eof()) cout << "Error: too many arguments" << endl;
                    
                    else{
                        shapesArray[objNum]->setXlocation(locx);    //if everything is good, change the values
                        shapesArray[objNum]->setYlocation(locy);
                        cout << "Moved " << name << " to " << locx << " " << locy << endl;
                    }
                }               
            }
        }
        
        else if(command == "rotate"){
            
            nameExists = false;
            invalidName = false;
            oneArg = false;
                    
            if(lineStream.peek(), lineStream.eof()) oneArg = true;
            
            lineStream >> name;
            
            for(int i = 0; i<7; i++) if(name == keyWordsList[i]) invalidName = true;
            for(int i = 0; i<3; i++) if(name == shapeTypesList[i]) invalidName = true;
            for(int i = 0; i<shapeCount; i++){
                if((shapesArray[i]!= NULL) && (name == shapesArray[i]->getName()) && (nameExists == false)){
                    objNum = i;
                    nameExists = true;
                }
            }
            
            if(lineStream.fail()&& !(lineStream.eof())) cout << "Error: invalid argument" << endl;
            else if(invalidName) cout << "Error: invalid shape name" << endl;
            else if(!nameExists && !oneArg) cout << "Error: shape " << name << " not found" << endl;    //if there's one argument you want to avoid the variables based on previous name
            else if(lineStream.peek(), lineStream.eof()) cout << "Error: too few arguments" << endl;
            
            else{
                lineStream >> angle;
                    
                    if(lineStream.fail()&& !(lineStream.eof())) cout << "Error: invalid argument" << endl;
                    else if(angle < 0 || angle > 360) cout << "Error: invalid value" << endl;
                    else if(!lineStream.peek(), !lineStream.eof()) cout << "Error: too many arguments" << endl;
                    
                    else{
                        shapesArray[objNum]->setRotate(angle);      //if everything is good change the values
                        cout << "Rotated " << name << " by " << angle << " degrees" << endl;
                    }   
            }  
        }
        
        else if(command == "draw"){
            
            nameExists = false;
            invalidName = false;
            oneArg = false;
                    
            if(lineStream.peek(), lineStream.eof()) oneArg = true;
            
            lineStream >> name;
 
            for(int i = 0; i<7; i++) if(name == keyWordsList[i]) invalidName = true;
            for(int i = 0; i<3; i++) if(name == shapeTypesList[i]) invalidName = true;
            for(int i = 0; i<shapeCount; i++){
                if((shapesArray[i]!= NULL) && (name == shapesArray[i]->getName())) nameExists = true;
            }    
            
            if(name == "all"){      //if name is "all" you have to override the invalidName and set nameExists to true in
                invalidName = false;
                nameExists = true;
            }
            
            if((lineStream.fail())&& !(lineStream.eof())) cout << "Error: invalid argument" << endl;
            else if(invalidName) cout << "Error: invalid shape name" << endl;
            else if(!nameExists && !oneArg) cout << "Error: shape " << name << " not found" << endl;    //if there's one argument you want to avoid the variables based on previous name
            else if(!lineStream.peek(), !lineStream.eof()) cout << "Error: too many arguments" << endl;
            else if(oneArg) cout << "Error: too few arguments" << endl;
            
            else{
                
                if(name == "all"){
                    cout << "Drew all shapes" << endl;
                    for(int i = 0; i<shapeCount; i++){
                        if(shapesArray[i]!= NULL) shapesArray[i]->draw();
                    }                    
                }
                
                else{
                    nameExists = false;
                    
                    for(int i = 0; i<shapeCount; i++){
                        if((shapesArray[i]!= NULL) && (name == shapesArray[i]->getName()) && (nameExists == false)){   
                            objNum = i;
                            nameExists = true;
                        }
                    }
                    
                    cout << "Drew " << name << endl;
                    shapesArray[objNum]->draw();
                }
            }    
        }
        
        else if(command == "delete"){
            
            nameExists = false;
            invalidName = false;;
            oneArg = false;
            
            if(lineStream.peek(), lineStream.eof()) oneArg = true;
            
            lineStream >> name;
            
            for(int i = 0; i<7; i++) if(name == keyWordsList[i]) invalidName = true;
            for(int i = 0; i<3; i++) if(name == shapeTypesList[i]) invalidName = true;
            for(int i = 0; i<shapeCount; i++){
                if((shapesArray[i]!= NULL) && (name == shapesArray[i]->getName())) nameExists = true;
            }
            
            if(name == "all"){      //if name is "all" you have to override the invalidName and set nameExists to true in
                invalidName = false;
                nameExists = true;
            }
            
            if(lineStream.fail()&& !(lineStream.eof())) cout << "Error: invalid argument" << endl;
            else if(invalidName) cout << "Error: invalid shape name" << endl;
            else if(!nameExists && !oneArg) cout << "Error: shape " << name << " not found" << endl;
            else if(!lineStream.peek(), !lineStream.eof()) cout << "Error: too many arguments" << endl;
            else if(oneArg) cout << "Error: too few arguments" << endl;
            
            else{
                
                if(name == "all"){ 
                    for(int i = 0; i<shapeCount; i++){ 
                        delete shapesArray[i];      //clears the content of the array, to avoid memory leak
                        shapesArray[i] = NULL;      //'clears' the pointer
                        cout << "Deleted: all shapes" << endl;
                    }
                }
                
                else{
                    nameExists = false;
                    for(int i = 0; i<shapeCount; i++){
                        if((shapesArray[i]!= NULL) && (name == shapesArray[i]->getName()) && (nameExists == false)){
                            objNum = i;
                            nameExists = true;
                        }
                    }
                    
                    delete shapesArray[objNum];     //clears the content of the array, to avoid memory leak
                    shapesArray[objNum] = NULL;     //'clears' the pointer
                    cout << "Deleted shape " << name << endl;
                }
            }    
        }
        
        else cout << "Error: invalid command" << endl;
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
        
    }  // End input loop until EOF.
    
    return 0;
}

