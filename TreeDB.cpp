/* 
 * File:   TreeDB.cpp
 * Author: eldamaty
 * 
 * Created on November 11, 2014, 12:16 PM
 */

#include "TreeDB.h"
#include "DBentry.h"
#include "TreeNode.h"
#include <iostream>
#include <cstdlib>

using namespace std;


//Privates

//function to help you find name
TreeNode* TreeDB::findName(TreeNode* ptr, string name){
    if (ptr==NULL) return NULL;
    if(ptr->getEntry()->getName()==name){
        return ptr;
    }
    else if (ptr->getEntry()->getName() < name){
        probesCount++;
        return findName(ptr->getRight(), name);
    }
    else{
        probesCount++;
        return findName(ptr->getLeft(), name);
    }
    
}

//fn which is used to get helper pointers, used for insert or delete
TreeNode* TreeDB::helperInsertOrDelete(string name, bool forInsert){
    TreeNode* helpPtr=root;
    while(helpPtr!=NULL){
        if(helpPtr->getEntry()->getName()<name){
            if(forInsert){
                if(helpPtr->getRight()==NULL) return helpPtr;
                else helpPtr=helpPtr->getRight();
            }
            else{
                if(helpPtr->getRight()->getEntry()->getName()==name) return helpPtr;
                else helpPtr=helpPtr->getRight();
            }
        }
        else{
            if(forInsert){
                if(helpPtr->getLeft()==NULL) return helpPtr;
                else helpPtr=helpPtr->getLeft();
            }
            else{
                if(helpPtr->getLeft()->getEntry()->getName()==name) return helpPtr;
                else helpPtr=helpPtr->getLeft();
            }
        }
    }
}

//used to insert a new entry
void TreeDB::insertEntry(TreeNode* ptr, DBentry* entry){
    if(root==NULL) {
        root = new TreeNode(entry);
    }
    else if (ptr==NULL) {
        TreeNode* previousTreeNode = helperInsertOrDelete(entry->getName(), true);
        ptr = new TreeNode(entry);
        if(previousTreeNode->getEntry()->getName()<entry->getName())previousTreeNode->setRight(ptr);
        else previousTreeNode->setLeft(ptr);
    }
    else if(ptr->getEntry()->getName()<entry->getName()){
        insertEntry(ptr->getRight(), entry);
    }
    else{
        insertEntry(ptr->getLeft(), entry);
    }
}

//gets the rightmost, used for the remove function
TreeNode* TreeDB::getRightMost(TreeNode* ptr){
    while(ptr->getRight()!=NULL){
        ptr=ptr->getRight();
    }
    return ptr;
}

//gets number of actives
void TreeDB::actives(TreeNode* ptr, int & numActives){
    if(ptr!=NULL){
        if(ptr->getEntry()->getActive()==true) numActives++;
        actives(ptr->getLeft(), numActives);
        actives(ptr->getRight(), numActives);
    }
}

//prints everything
void TreeDB::printAll(TreeNode* ptr)const{
    if(ptr!=NULL){
        printAll(ptr->getLeft());
        cout<<*ptr->getEntry();
        printAll(ptr->getRight());
    }
    
}

//Publics
TreeDB::TreeDB() {
    root = NULL;
    probesCount=1;
}

TreeDB::TreeDB(const TreeDB& orig) {
}

TreeDB::~TreeDB() {
    clear();
}

//find function, used to help find any db entry given a name
DBentry* TreeDB::find(string name){
    probesCount=1;
    TreeNode* ptr;
    if(root==NULL) {
        return NULL;
    }
    else {
        ptr=findName(root, name);
        
        if(ptr==NULL) {
            return NULL;
        }
        else return ptr->getEntry();
    }
} 

//used to insert a new entry
bool TreeDB::insert(DBentry* newEntry){
    DBentry* ptr = find(newEntry->getName());
    if(ptr!=NULL) return false;
    else{
        insertEntry(root, newEntry);
        return true;
    }
}

//used to remove an individual entry
bool TreeDB::remove(string name){
    TreeNode* toDelete = findName(root, name);
    if(toDelete==NULL) return false;
    else{
        if(toDelete==root){
            if(root->getLeft()==NULL && root->getRight()==NULL){
                delete root;
                root=NULL;
            }
            else if (root->getLeft()==NULL && root->getRight()!=NULL){
                TreeNode* helperTemp = root;
                root = root->getRight();
                delete helperTemp;
            }
            else if(root->getLeft()!=NULL && root->getRight()==NULL){
                TreeNode* helperTemp = root;
                root = root->getLeft();
                delete helperTemp;
            }
            else{
                TreeNode* helperTemp=root;
                TreeNode* rightMost = getRightMost(root->getLeft());
                TreeNode* rightMostPrevious = helperInsertOrDelete(rightMost->getEntry()->getName(),false);
                if(rightMostPrevious==root){
                    TreeNode* helperRight = root->getRight();
                    root = root->getLeft();
                    root->setRight(helperRight);
                    delete helperTemp;
                }
                else{
                    rightMostPrevious->setRight(rightMost->getLeft());
                    root=rightMost;
                    root->setLeft(helperTemp->getLeft());
                    root->setRight(helperTemp->getRight());
                    delete helperTemp;
                }
            }
        }
        else{
            //to get the previous node and whether the left part points to the required node to delete or the right does
            TreeNode* previousTreeNode = helperInsertOrDelete(name, false);
            bool toLeft;
            if(previousTreeNode->getLeft()==toDelete) toLeft=true;
            else toLeft=false;
            if(toDelete->getLeft()==NULL && toDelete->getRight()==NULL){
                if(toLeft){
                    delete previousTreeNode->getLeft();
                    previousTreeNode->setLeft(NULL);
                }
                else{
                    delete previousTreeNode->getRight();
                    previousTreeNode->setRight(NULL);
                }
            }
            else if (toDelete->getLeft()==NULL && toDelete->getRight()!=NULL){
                TreeNode* helperTemp = toDelete;
                if(toLeft) previousTreeNode->setLeft(toDelete->getRight());
                else previousTreeNode->setRight(toDelete->getRight());
                delete helperTemp;
            }
            else if (toDelete->getLeft()!=NULL && toDelete->getRight()==NULL){
                TreeNode* helperTemp = toDelete;
                if(toLeft) previousTreeNode->setLeft(toDelete->getLeft());
                else previousTreeNode->setRight(toDelete->getLeft());
                delete helperTemp;
            }
            else{
                TreeNode* helperTemp = toDelete;
                TreeNode* rightMost;
                rightMost = getRightMost(toDelete->getLeft());
                TreeNode* rightMostPrevious = helperInsertOrDelete(rightMost->getEntry()->getName(),false);
                //if the rightmost is directly following the node you want to delete
                if(rightMostPrevious==toDelete){
                    if(toLeft) previousTreeNode->setLeft(rightMost);
                    else previousTreeNode->setRight(rightMost);
                    rightMost->setRight(helperTemp->getRight());
                }
                else{
                    rightMostPrevious->setRight(rightMost->getLeft());
                    if(toLeft) previousTreeNode->setLeft(rightMost);
                    else previousTreeNode->setRight(rightMost);
                    rightMost->setLeft(helperTemp->getLeft());
                    rightMost->setRight(helperTemp->getRight());
                }
                delete helperTemp;
            }

            return true;
        }
    }
}

//deletes everything
void TreeDB::clear(){
    while (root!=NULL) remove (root->getEntry()->getName());
}

//prints probesCount
void TreeDB::printProbes() const{
    cout<<probesCount<<endl;
}

//counts active
void TreeDB::countActive(){
    int numActives=0;
    actives(root, numActives);
    cout<<numActives<<endl;
}

//used to help print the tree db
ostream & operator<<(ostream & os, const TreeDB & rhs){
    
    rhs.printAll(rhs.root);
    
    return (os);
}