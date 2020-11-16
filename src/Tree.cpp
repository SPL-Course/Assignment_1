
#include "../include/Tree.h"
#include <iostream>
using namespace std;

//==========================Tree=========================

Tree::Tree(int rootLabel): node(rootLabel), children(), visited(false){}

Tree::~Tree() {
    if(this){
        for (int i = 0; i <children.size(); ++i)
            delete (children[i]);
        delete(this);
    }
}

void Tree::BFS(Session& s , Tree *root) {
    Graph *g=s.getGraph();
    queue<Tree*> nodes;
    nodes.push(root);                               //root is the adress of the root, meaning the adress of node
    while (!nodes.empty()){
        Tree* temp=nodes.front();
        nodes.pop();
        for (int j = 0; j <g->getEdges().size(); ++j) {
            Tree* child=createTree(s,temp->node);
            if(child->visited) {
                temp->addChild(*child);
                nodes.push(child);
            }
        }
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