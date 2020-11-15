
#include "../include/Tree.h"
#include "../include/Session.h"                 //we added, need to check if its ok
#include <iostream>
using namespace std;

//==========================Tree=========================

Tree::Tree(int rootLabel): node(rootLabel), children(){}

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

//==========================RootTree=====================================

RootTree::RootTree(int rootLabel):Tree(rootLabel){}

Tree * RootTree::clone() const {
    return (new RootTree(this->getNode()));
}

//==========================CycleTree=====================================
CycleTree::CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){}

Tree * CycleTree::clone() const {
    return (new CycleTree(this->getNode(),currCycle));
}

//==========================MaxRankTree=====================================
MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel){}

Tree * MaxRankTree::clone() const {
    return (new MaxRankTree(this->getNode()));
}