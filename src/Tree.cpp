
#include "../include/Tree.h"
#include <iostream>
using namespace std;
 /* changed pointers delete in traceTree Cycle*/
//==========================Tree=========================

Tree::Tree(int rootLabel): rank(0), depth(0), node(rootLabel), children() {}

Tree::~Tree()
{
    clear();
}

void Tree::clear()
{
   unsigned int size = children.size();
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
        node = other.node;
        rank = other.rank;
        depth = other.depth;
        unsigned int count = other.children.size();
        for (unsigned int i = 0; i < count; ++i) {
            children.push_back(other.children.at(i)->clone());
        }
    }
    return *this;
}

Tree &Tree::operator=(Tree &&other) {
    if(this != &other){
        clear();
        node = other.node;
        rank = other.rank;
        depth = other.depth;
        unsigned int count = other.children.size();
        for (unsigned int i = 0; i < count; ++i) {
            children.push_back(other.children.at(i)->clone());
        }
        steal(other);
    }
    return *this;
}

void Tree::steal(Tree &other)
{
    unsigned int count=other.children.size();
    for(unsigned int i = 0; i<count; i++)
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

int Tree::getNode() const
{
    return node;
}

Tree::Tree(Tree &&other):
  rank(other.rank),depth(other.depth), node(other.node),children(move(other.children))
{
    steal(other);
}

vector<Tree *> *Tree::getChildren()
{
    return &children;
}

Tree::Tree(const Tree &other):
     rank(other.rank),depth(other.depth), node(other.node), children()
{
    unsigned int count = other.children.size();
    for(unsigned int i=0; i < count; i++){
        children.push_back(other.children.at(i)->clone());
    }
}


int Tree::getSize()
{
    int size = 0;
    queue<Tree*> q;
    q.push(this);
    while(!q.empty()){
        Tree* curr = q.front(); q.pop();
        unsigned int count=curr->getChildren()->size();
        for (unsigned int i = 0; i < count; ++i)
            q.push(curr->getChildren()->at(i));
        size= size+1;
    }
    return size;
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
    unsigned int cycles = getCurrCycle();
    for (unsigned int i = 0; (i < cycles) & (length != 0); ++i) {
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
    Tree* min;
    sameRank.push_back(maxRank);
    unsigned int treeSize = getSize();
    while(treeSize > 0) {
        unsigned int count = children.size();
        for (unsigned int i = 0; i < count; ++i) {
            Tree *curr = children.at(i);
            if (curr->rank > maxRank->rank) {
                maxRank = curr;
                sameRank.clear();
                sameRank.push_back(maxRank);
            }
            if (curr->rank == maxRank->rank)
                sameRank.push_back(curr);
        }
        if (sameRank.size() == 1)
            return maxRank->getNode();
        min = sameRank[0];
        for (auto &k : sameRank) {
            if (min->depth > k->depth)
                min = k;
            if (min->depth == k->depth) {
                if (min->getNode() > k->getNode())
                    min = k;
            }
        }
        treeSize--;
    }
    return min->getNode();
}