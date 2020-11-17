
#include "../include/Tree.h"
#include <iostream>
using namespace std;

//==========================Tree=========================

Tree::Tree(int rootLabel): node(rootLabel), children(), visited(false), rank(0), depth(0){}

Tree::~Tree() {
    if(this){
        for (int i = 0; i <children.size(); ++i)
            delete (children[i]);
        delete(this);
    }
}

Tree * Tree::createTree(const Session &session, int rootLabel){
    TreeType tType=session.getTreeType();
    if(tType==MaxRank)
        return new MaxRankTree(rootLabel);
    if(tType==Cycle)
        return new CycleTree(rootLabel,0);
    if(tType==Root)
        return new RootTree(rootLabel);
}

Tree::Tree(Tree &other) {
    clone();
}

void Tree::addChild(const Tree &child) {
    Tree *copy=child.clone();
    children.push_back(copy);
}

//void Tree::addChild(const Tree &&child) {
//    Tree* copy=child.clone();
//    children.push_back(copy);
//}

int Tree::getNode() const {
    return node;
}

vector<Tree *> Tree::getChildren() const {
    return children;
}

//==========================RootTree=====================================

RootTree::RootTree(int rootLabel):Tree(rootLabel){}

Tree * RootTree::clone() const {
    return (new RootTree(this->getNode()));
}

int RootTree::traceTree() {
    return getNode();
}

//==========================CycleTree=====================================
CycleTree::CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){}

Tree * CycleTree::clone() const {
    return (new CycleTree(this->getNode(),currCycle));
}

int CycleTree::traceTree() {// if 0 - root, else go-left currCycle times
    int output=getNode();
    if(currCycle==0)
        return output;
    Tree* root=getChildren()[0];
    Tree* point;
    for (int i = 1; i <currCycle; ++i) {
        point= root->getChildren()[0];
        root=point;
    }
    output=root->getNode();
    delete (root);
    delete (point);
    return output;
}

//==========================MaxRankTree=====================================
MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel){}

Tree * MaxRankTree::clone() const {
    return (new MaxRankTree(this->getNode()));
}

int MaxRankTree::traceTree() {

    Tree *max = this;
    for (int i = 0; i < children.size(); ++i) {

        Tree *curr = children[i];
        if (max->rank < curr->rank)     //case 1
            max = curr;
        if (max->rank == curr->rank) {     //case 2
            if (curr->depth < max->depth)       //x
                max = curr;
            else if (max->depth == curr->depth && curr->getNode() < max->getNode())
                    max = curr;
            }
    }

    return max->getNode();
}

//    int output = getNode();            // root
//    Tree *max = getChildren()[0];      // first child
//    int maxChildren = max->getChildren().size();
//    for (int i = 1; i < getChildren().size() ; ++i) {
//        Tree* curr = getChildren()[i]; // other children
//        int currChildren = curr->getChildren().size();
//        if(maxChildren < currChildren){
//            max = curr;
//            maxChildren = currChildren;
//        }
//        else if( maxChildren == currChildren){
//
//        }
//    }
//
//
//    return output;
}