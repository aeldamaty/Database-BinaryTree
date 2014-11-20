/* 
 * File:   DBentry.cpp
 * Author: eldamaty
 * 
 * Created on November 11, 2014, 12:16 PM
 */

#include "DBentry.h"
#include <iostream>

DBentry::DBentry() {
}

DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active){
    name=_name;
    IPaddress=_IPaddress;
    active=_active;
}

DBentry::DBentry(const DBentry& orig) {
}

DBentry::~DBentry() {
}

string DBentry::getName() const{
    return name;
}

unsigned int DBentry::getIPaddress() const{
    return IPaddress;
}

bool DBentry::getActive() const{
    return active;
}

void DBentry::setName(string _name){
    name=_name;
}

void DBentry::setIPaddress(unsigned int _IPaddress){
    IPaddress=_IPaddress;
}

void DBentry::setActive(bool _active){
    active=_active;
}

ostream & operator<< (ostream & out, const DBentry& rhs){
    string status;
    if(rhs.active) status="active";
    else status="inactive";
    
    out<<rhs.name<<" : "<<rhs.IPaddress<<" : "<<status<<endl;
    return out;
}