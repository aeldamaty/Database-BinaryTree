/* 
 * File:   TreeNode.h
 * Author: eldamaty
 *
 * Created on November 11, 2014, 12:17 PM
 */

#ifndef TREENODE_H
#define	TREENODE_H

#include "DBentry.h"

class TreeNode {
private:
    TreeNode* left;
    TreeNode* right;
    DBentry* data;
    
public:
    TreeNode();
    TreeNode(DBentry* _entryPtr);
    TreeNode(const TreeNode& orig);
    virtual ~TreeNode();
    DBentry* getEntry() const;
    TreeNode* getLeft() const;
    TreeNode* getRight() const;
    void setLeft(TreeNode* newLeft);
    void setRight(TreeNode* newRight);
};

#endif	/* TREENODE_H */

