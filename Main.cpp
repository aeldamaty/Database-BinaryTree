/* 
 * File:   Main.cpp
 * Author: eldamaty
 *
 * Created on November 11, 2014, 12:13 PM
 */

#include <cstdlib>
#include <ios>
#include <iostream>
#include <sstream>
#include "DBentry.h"
#include "TreeDB.h"
#include "TreeNode.h"

using namespace std;


int main(int argc, char** argv) {

    //dynamically creates a new tree db
    TreeDB* database = new TreeDB;
    
    //initializes 
    cout<<"> ";
    string line;
    getline(cin, line);
    
    //this will keep looping until eof is reached
    while (!cin.eof()){
        
        string command, name, status;
        unsigned int IPaddress;
        
        stringstream linestream (line);
        
        linestream >> command;
        //the following looks at the input and performs the required operation by dynamically making objects if needed and calling fns
        if(command=="insert"){
            linestream >> name;
            linestream >> IPaddress;
            linestream >> status;
            
            bool active;
            if(status=="active") active=true;
            else{
                active=false;
            }
            
            DBentry* temp = new DBentry(name, IPaddress, active);
            bool success=database->insert(temp);
            if(success) cout<<"Success\n";
            else{
                cout<<"Error: entry already exists\n";
                delete temp;
            }
        }
        
        else if (command=="find"){
            linestream >> name;
            DBentry* temp = database->find(name);
            
            if(temp==NULL){
                cout<<"Error: entry does not exist\n";
                delete temp;
            }
            else{
                cout<<*temp;
            }
            
        }
        
        else if (command=="remove"){
            linestream >> name;
            bool deleted = database->remove(name);
            if(deleted) cout<<"Success\n";
            else cout<<"Error: entry does not exist\n";
        }
        
        else if (command=="printall"){
            cout<<*database;
        }
        
        else if (command=="printprobes"){
            linestream >> name;
            DBentry* ptr = database->find(name);
            if(ptr==NULL){
                cout<<"Error: entry does not exist\n";
                delete ptr;
            }
            else database->printProbes();
            
        }
        
        else if (command=="removeall"){
            database->clear();
            cout<<"Success\n";
        }
        
        else if (command=="countactive"){
            database->countActive();
        }
        
        else if (command=="updatestatus"){
            linestream >> name;
            linestream >> status;
            
            bool active;
            if(status=="active") active=true;
            else active=false;
            
            DBentry* temp = database->find(name);
            
            if(temp==NULL){
                cout<<"Error: entry does not exist\n";
                delete temp;
            }
            else{
                temp->setActive(active);
                cout<<"Success\n";
            }
            
            
        }
        
        cout<<"> ";
        linestream.clear();
        getline(cin, line);
        
    }
    delete database;
    return 0;
}

