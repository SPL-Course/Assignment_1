
#include "../include/Tree.h"
#include <iostream>
using namespace std;
 /* changed pointers delete in traceTree Cycle*/
//==========================Tree=========================

Tree::Tree(int rootLabel): node(rootLabel), children(vector<Tree*>()), rank(0), depth(0) {}

Tree::~Tree()
{
    clear();
}

void Tree::clear()
{
   int size = children.size();
   for(unsigned int i = 0; i < size; i++){
       if(children.at(i) != nullptr) {
            delete (children.at(i));
            children.at(i) = nullptr;
       }
   }
}

Tree& Tree::operator=(const Tree &other)
{
    if(this != &other){
        clear();
        int size = other.children.size();
        for (unsigned int i = 0; i < size; ++i) {
            children.push_back(other.children.at(i)->clone());
        }
    }
    return *this;
}

Tree &Tree::operator=(Tree &&other) noexcept {
    if(this != &other){
        clear();
        node = other.node;
        rank = other.rank;
        depth = other.depth;
        int size = other.children.size();
        for (unsigned int i = 0; i < size; ++i) {
            children.push_back(other.children.at(i)->clone());
        }
        steal(other);
    }
    return *this;
}

void Tree::steal(Tree &other)
{
    int size=other.children.size();
    for(unsigned int i = 0; i<size; i++)
        children.at(i) = nullptr;
}

Tree * Tree::createTree(const Session &session, int rootLabel)
{
    Tree *p;
    TreeType tType = session.getTreeType();
    if(tType==MaxRank)
        p = new MaxRankTree(rootLabel);
    if(tType==Cycle)
        p = new CycleTree(rootLabel,0);
    if(tType==Root)
        p = new RootTree(rootLabel);
    return p;
}

void Tree::addChild(const Tree &child)
{
    children.push_back(child.clone());
}

void Tree::addChildShallow(Tree *child)
{
    children.push_back(child);
}

int Tree::getNode() const {
    return node;
}

Tree::Tree(Tree &&other) noexcept: children(move(other.children)), depth(other.depth),
                          rank(other.rank), node(other.node)
{
    steal(other);
}

vector<Tree *> *Tree::getChildren() {
    return &children;
}

Tree::Tree(const Tree &other): children(vector<Tree*>()),
                               depth(other.depth), rank(other.rank), node(other.node)
{
    int size = other.children.size();
    for(unsigned int i=0; i < size; i++){
        children.push_back(other.children.at(i)->clone());
    }
}
//==========================RootTree=====================================

RootTree::RootTree(int rootLabel):Tree(rootLabel){}

Tree * RootTree::clone() const
{
    return (new RootTree(*this));
}

int RootTree::traceTree()
{
    return node;
}

//==========================CycleTree=====================================
CycleTree::CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){}

Tree * CycleTree::clone() const
{
    return (new CycleTree(*this));
}

int CycleTree::traceTree() {// if 0 - root, else go-left currCycle times
    int output = node;
    Tree *curr = this;
    int length = curr->getChildren()->size();
    for (int i = 0; i < getCurrCycle() & length != 0; ++i) {
        output = curr->getChildren()->at(i)->getNode();
        curr = curr->getChildren()->at(i);
        length = curr->getChildren()->size();
    }
    return output;
}

    int CycleTree::getCurrCycle() const {
        return currCycle;
    }

//==========================MaxRankTree=====================================
    MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel){}

    Tree *MaxRankTree::clone() const {
        return (new MaxRankTree(*this));
    }

int MaxRankTree::traceTree() {
    vector<Tree*> sameRank;
    Tree *maxRank=this;
    sameRank.push_back(maxRank);
//    for (int i = 0; i < this.size; ++i) { //add field size
    for (int i = 0; i < 50; ++i) {
        Tree *curr=children.at(i);
        if(curr->rank>maxRank->rank) {
            maxRank = curr;
            sameRank.clear();
            sameRank.push_back(maxRank);
        }
        if(curr->rank==maxRank->rank)
            sameRank.push_back(curr);
    }
    if(sameRank.size()==1)
        return maxRank->getNode();
    Tree *min=sameRank[0];
    for (auto & k : sameRank) {
        if(min->depth>k->depth)
            min=k;
        if(min->depth==k->depth){
            if(min->getNode()>k->getNode())
                min=k;
        }
    }
    return min->getNode();
}