/* 
 * File:   TreeNode.cpp
 * Author: Sebastian Wardzinski
 * 
 * Created on November 19, 2018, 2:47 PM
 */

#include "DBentry.h"
#include "TreeNode.h"

using namespace std;

//Default constructor for TreeNode
TreeNode::TreeNode(DBentry* _entryPtr){
    entryPtr = _entryPtr;
    left = NULL;
    right = NULL;
}

//The destructor for Treenode
TreeNode::~TreeNode(){
    delete entryPtr;
    entryPtr = NULL;
    left = NULL;
    right = NULL;
}

//Mutator functions
void TreeNode::setLeft(TreeNode* newLeft) { left = newLeft; }
void TreeNode::setRight(TreeNode* newRight) { right = newRight; }

//Accessor functions
TreeNode* TreeNode::getLeft() const { return (left); }
TreeNode* TreeNode::getRight() const { return (right); }
DBentry* TreeNode::getEntry() const { return (entryPtr); }
