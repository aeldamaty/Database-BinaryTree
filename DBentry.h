/* 
 * File:   DBentry.h
 * Author: eldamaty
 *
 * Created on November 11, 2014, 12:16 PM
 */

#ifndef DBENTRY_H
#define	DBENTRY_H

#include <string>

using namespace std;

class DBentry {

private:
    string name;
    unsigned int IPaddress;
    bool active;
    
public:
    DBentry();
    DBentry (string _name, unsigned int _IPaddress, bool _active);
    DBentry(const DBentry& orig);
    virtual ~DBentry();
    string getName() const;
    unsigned int getIPaddress() const;
    bool getActive() const;
    void setName(string _name);
    void setIPaddress(unsigned int _IPaddress);
    void setActive(bool _active);
    
    friend ostream & operator<< (ostream & out, const DBentry& rhs);
    
};

#endif	/* DBENTRY_H */

