
#include "../include/Tree.h"
#include "../include/Session.h"
#include <iostream>
using namespace std;

Tree::Tree(int rootLabel): node(rootLabel), children(){}

Tree::~Tree() {
    if(this){
        for (int i = 0; i <children.size(); ++i) {
            delete (children[i]);
        }
        delete(this);
    }
}

Tree * Tree::createTree(const Session &session, int rootLabel){
    TreeType Ttype=session.getTreeType();
    if(Ttype==MaxRank)
        return new MaxRankTree(rootLabel);
    if(Ttype==Cycle)
        return new CycleTree(rootLabel,0);
    if(Ttype==Root)
        return new RootTree(rootLabel);
}

Tree::Tree(Tree &other) { clone(); }

Tree * Tree::clone() const {
    return (new Tree(*this))
}


void Tree::addChild(const Tree &child) {
    Tree* copy=child.clone();
    children.addChild(copy);
}

void Tree::addChild(Tree &&child) {
    Tree* copy=child.clone();
    children.addChild(copy);
}




