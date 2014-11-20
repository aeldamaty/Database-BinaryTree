/* 
 * File:   TreeDB.h
 * Author: eldamaty
 *
 * Created on November 11, 2014, 12:16 PM
 */

#ifndef TREEDB_H
#define	TREEDB_H

#include "TreeNode.h"

class TreeDB {
private:
    TreeNode* root;
    int probesCount;
    
    TreeNode* findName(TreeNode* ptr, string name);
    TreeNode* helperInsertOrDelete(string name, bool forInsert);
    void insertEntry(TreeNode* ptr, DBentry* entry);
    TreeNode* getRightMost(TreeNode* ptr);
    
    void actives(TreeNode* ptr, int & numActives);
    
    void printAll(TreeNode* ptr)const;
    
public:
    TreeDB();
    TreeDB(const TreeDB& orig);
    virtual ~TreeDB();
    
    DBentry* find(string name);
    bool insert(DBentry* newEntry);
    bool remove(string name);
    void clear();
    void printProbes() const;
    void countActive();
    
    friend ostream & operator<< (ostream & out, const TreeDB & rhs);
    
};

#endif	/* TREEDB_H */

