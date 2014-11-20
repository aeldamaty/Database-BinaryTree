/* 
 * File:   TreeNode.cpp
 * Author: eldamaty
 * 
 * Created on November 11, 2014, 12:17 PM
 */

#include "TreeNode.h"
#include <iostream>

TreeNode::TreeNode() {
}

TreeNode::TreeNode(DBentry* _entryPtr){
    left=NULL;
    right=NULL;
    data=_entryPtr;
}

TreeNode::TreeNode(const TreeNode& orig) {
}

TreeNode::~TreeNode() {
    delete data;
}

DBentry* TreeNode::getEntry() const{
    return data;
}

TreeNode* TreeNode::getLeft() const{
    return left;
}

TreeNode* TreeNode::getRight() const{
    return right;
}

void TreeNode::setLeft(TreeNode* newLeft){
    left=newLeft;
}

void TreeNode::setRight(TreeNode* newRight){
    right=newRight;
}