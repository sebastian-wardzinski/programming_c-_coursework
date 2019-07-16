/* 
 * File:   TreeDB.cpp
 * Author: Sebastian Wardzinski
 * 
 * Created on November 19, 2018, 2:47 PM
 */

#include "TreeDB.h"
#include "TreeNode.h"
#include "DBentry.h"

#include <iostream>
#include <string>

//Default constructor, creates an empty database
TreeDB::TreeDB(){
    root = NULL;
    probesCount = 0;
}

//The destructor, deletes all the entries in the database.
TreeDB::~TreeDB(){
    clear();
    root = NULL;
}

//Helper function for insert (found below)
bool TreeDB::insertHelper(TreeNode *newNode, TreeNode *node){
    
    if(newNode->getEntry()->getName() > node->getEntry()->getName()){
         if(node->getRight() == NULL){
            node->setRight(newNode);
         }
         else return insertHelper(newNode, node->getRight());
    }
    
    else if(newNode->getEntry()->getName() < node->getEntry()->getName()){
         if(node->getLeft() == NULL){
            node->setLeft(newNode);
         }
         else return insertHelper(newNode, node->getLeft());
    }
    return true;
}

//Inserts a new entry into the ordered binary tree
//Always returns true since I check if the name exists in main before calling this function
bool TreeDB::insert(DBentry* newEntry){
    
    if(root == NULL){
        root = new TreeNode(newEntry);
        return true;
    }
    
    else{
        TreeNode* entryPtr = new TreeNode(newEntry);
        return insertHelper(entryPtr, root);
    }
}


//Helper function for find (found below)
DBentry* TreeDB::findHelper(TreeNode* node, string name){
    probesCount++; 
    
    if (node->getEntry()->getName() == name) return node->getEntry();
     
    if(node->getEntry()->getName() < name){
         if(node->getRight() != NULL){
             return findHelper(node->getRight(), name);
         }
    }
    
    else if(node->getEntry()->getName() > name){
         if(node->getLeft() != NULL){
            return findHelper(node->getLeft(), name);
         }
    }
    
    return NULL;
 }

//Searches database for entry with key "name"
//If found, returns pointer to the entry, otherwise returns null
//Also sets probesCount which records how far down the tree the node is
DBentry* TreeDB::find(string name){
    probesCount = 0;
    
    if (root == NULL) return NULL;
    
    return findHelper(root, name);
}


//Helper function for remove (found below)
bool TreeDB::removeHelper(TreeNode* parent,TreeNode* node, string name){
    if(node->getEntry()->getName() == name){
        
        //if node to be deleted is a leaf node
        if(node->getLeft() == NULL && node->getRight() == NULL){
            if(parent->getEntry()->getName() < node->getEntry()->getName()) parent->setRight(NULL);
            else if(parent->getEntry()->getName() > node->getEntry()->getName()) parent->setLeft(NULL);
            
            delete node;
            node = NULL;
        }
        
        //if node to be deleted has one child
        else if(node->getLeft() == NULL && node->getRight() != NULL){
            if(parent->getEntry()->getName() < node->getEntry()->getName()) parent->setRight(node->getRight());
            else if(parent->getEntry()->getName() > node->getEntry()->getName()) parent->setLeft(node->getRight());
           
            delete node;
            node = NULL;
        }
        else if(node->getLeft() != NULL && node->getRight() == NULL){
            if(parent->getEntry()->getName() < node->getEntry()->getName()) parent->setRight(node->getLeft());
            else if(parent->getEntry()->getName() > node->getEntry()->getName()) parent->setLeft(node->getLeft());
           
            delete node;
            node = NULL;
        }
        
        //if node to be deleted has two children
        else if(node->getLeft() != NULL && node->getRight() != NULL){
            TreeNode* newNodeParent = node;
            TreeNode* newNode = node;
            newNode = newNode->getLeft();
            if(newNode->getRight() != NULL){ 
                newNode = newNode->getRight();
                newNodeParent = newNodeParent->getLeft();
                while(newNode->getRight() != NULL){
                    newNodeParent = newNode;
                    newNode = newNode->getRight();
                }
                if(newNode->getLeft() != NULL) newNodeParent->setRight(newNode->getLeft());
            
                node->getEntry()->setName(newNode->getEntry()->getName());
                node->getEntry()->setIPaddress(newNode->getEntry()->getIPaddress());
                node->getEntry()->setActive(newNode->getEntry()->getActive());
                
                delete newNode;
                newNode = NULL;
            }
            else{
                newNode->setRight(newNodeParent->getRight());
                if(parent->getEntry()->getName() < node->getEntry()->getName()) parent->setRight(newNode);
                else if(parent->getEntry()->getName() > node->getEntry()->getName()) parent->setLeft(newNode);
                
                delete newNodeParent;
                newNodeParent = NULL;
            }
        }
        return true;
    }
    
    //Serves the recursive function of finding the node to delete, while recording its parent (for deletion purposes)
    if(node->getEntry()->getName() < name){
        parent = node;
        node = node->getRight();
        return removeHelper(parent, node, name);
    }
    if(node->getEntry()->getName() > name){
        parent = node;
        node = node->getLeft();
        return removeHelper(parent, node, name);
    }
    
    return false;
}

//Remove the node with key "name"
//Returns true if node is found and deleted, false if it wasn't found
//Deleted nodes with two children based on description in the handout
bool TreeDB::remove(string name){
    if(root == NULL) return false;
    
    //if we want to delete the root
    if(root->getEntry()->getName() == name){
        
        //if root to be deleted is the only node in the tree
        if(root->getLeft() == NULL && root->getRight() == NULL){
            delete root;
            root = NULL;
        }
        
        //if root to be deleted only has one child
        else if(root->getLeft() == NULL && root->getRight() != NULL){
            TreeNode* oldRoot = root;
            root = root->getRight();
            delete oldRoot;
            oldRoot = NULL;
        }
        else if(root->getLeft() != NULL && root->getRight() == NULL){
            TreeNode* oldRoot = root;
            root = root->getLeft();
            delete oldRoot;
            oldRoot = NULL;
        }
        
        //if root to be deleted has two children
        else if(root->getLeft() != NULL && root->getRight() != NULL){
            TreeNode* newRootParent = root;
            TreeNode* newRoot = root;
            
            newRoot = newRoot->getLeft();
            if(newRoot->getRight() != NULL){ 
                newRoot = newRoot->getRight();
                while(newRoot->getRight() != NULL){
                    newRootParent = newRoot;
                    newRoot = newRoot->getRight();
                }
                if(newRoot->getLeft() != NULL) newRootParent->setRight(newRoot->getLeft());
            
                root->getEntry()->setName(newRoot->getEntry()->getName());
                root->getEntry()->setIPaddress(newRoot->getEntry()->getIPaddress());
                root->getEntry()->setIPaddress(newRoot->getEntry()->getActive());
                
                delete newRoot;
                newRoot = NULL;
            }
            else{
                newRoot->setRight(newRootParent->getRight());
                root = newRoot;
                delete newRootParent;
                newRootParent = NULL;
            }
        }
        
        return true;
    }
    
    //Serves the recursive function of finding the node to delete, while recording its parent (for deletion purposes)
    else if(root->getEntry()->getName() < name) return removeHelper(root, root->getRight(), name);
    else if(root->getEntry()->getName() > name) return removeHelper(root, root->getLeft(), name);
    
    return false;
}
	
//Helper function for remove (found below)
void TreeDB::clearHelper(TreeNode* node){
    if(node->getLeft() != NULL) clearHelper(node->getLeft());
    if(node->getRight() != NULL) clearHelper(node->getRight());
    
    delete node;
}

//Deletes all the entries in the database
void TreeDB::clear(){
    if(root != NULL) clearHelper(root);
    root = NULL;
}
    
//Prints the number of probes stored in probesCount (which is calculated in find)
void TreeDB::printProbes() const{
    cout << probesCount << endl;
}
   
//Helper function for countActive (found below)
void TreeDB::countActiveHelper(TreeNode* node, int &count) const{
    if(node->getEntry()->getActive()) count++;
    if(node->getRight() != NULL) countActiveHelper(node->getRight(), count);
    if(node->getLeft() != NULL) countActiveHelper(node->getLeft(), count);
}

//Counts and prints the number of 'active' entries in the database
void TreeDB::countActive () const{
    int count = 0;
    countActiveHelper(root, count);
    
    cout << count << endl;
}

//Prints the entire tree, in ascending order of key (name)
ostream& operator<< (ostream& out, const TreeDB& rhs){
    if(rhs.root != NULL) out << rhs.root;
    
    return out;
}

//Helper function for the function above
ostream& operator<< (ostream& out, TreeNode* node){
    if(node->getLeft() != NULL) out<< node->getLeft();
    out << *(node->getEntry()) << endl;
    if(node->getRight() != NULL) out<<node->getRight();
    
    return out;
}
    