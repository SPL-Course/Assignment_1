
#include "../include/Tree.h"
#include <iostream>
using namespace std;

//============================Tree======================================

/* Tree Constructor */
Tree::Tree(int rootLabel): node(rootLabel), rank(0), depth(0), children() {}

/*--------Tree: Rule Of 5-----------*/

/* Tree Destructor */
Tree::~Tree()
{
    clear();
}

void Tree::clear()
{ /* clears Tree resources */
    unsigned int size = children.size();
    for(unsigned int i = 0; i < size; i++){
        if(children.at(i) != nullptr) {
            delete (children.at(i));
            children.at(i) = nullptr;
        }
    }
}

/* Tree Copy Constructor */
Tree::Tree(const Tree &other):
        node(other.node), rank(other.rank), depth(other.depth), children()
{
    clear();
    unsigned int count = other.children.size();
    for(unsigned int i=0; i < count; i++){
        children.push_back(other.children.at(i)->clone());
    }
}

/* Tree Copy Assignment Operator */
Tree & Tree::operator=(const Tree &other)
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

/* Tree Move Constructor */
Tree::Tree(Tree &&other):
        node(other.node), rank(other.rank), depth(other.depth), children(move(other.children))
{
    steal(other);
}

/* Tree Move Assignment Operator */
Tree & Tree::operator=(Tree &&other) {
    if(this != &other){
        clear();
        node = other.node;
        rank = other.rank;
        depth = other.depth;
        unsigned int count = other.children.size();
        for (unsigned int i = 0; i < count; ++i) {
            children.push_back(other.children.at(i));
        }
        steal(other);
    }
    return *this;
}

void Tree::steal(Tree &other)
{ /* other lose resources */
    unsigned int count=other.children.size();
    for(unsigned int i = 0; i<count; i++)
        children.at(i) = nullptr;
}

/*--------Tree: Given Functions-----------*/

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
{  /* using below function */
    Tree* copy = child.clone();
    addChild(copy);
}

void Tree::addChild(Tree *child)
{ /* keeps if changes - by pointer */
    children.push_back(child);
    child->updateDepthsBFS();
    rank++;
}

/*--------Help Functions--------*/

void Tree::updateDepthsBFS()
{ /* when adding children */
    queue<Tree*> q;
    q.push(this);
    while(!q.empty()){
        Tree* curr = q.front(); q.pop();
        unsigned int count = curr->getChildren()->size();
        for (unsigned int i = 0; i < count; ++i){
            Tree* child = curr->getChildren()->at(i);
            q.push(child);
        }
        curr->getDepth() = curr->getDepth() + 1;
    }
}

void Tree::updateCyclesBFS(int cycle)
{ /* helps CycleTree traceTree */
    queue<Tree*> q;
    q.push(this);
    while(!q.empty()){
        Tree* curr = q.front(); q.pop();
        unsigned int count = curr->getChildren()->size();
        for(unsigned int i = 0; i < count ; ++i) {
            Tree* child = curr->getChildren()->at(i);
            q.push(child);
        }

        if(curr->getCurrCycle() != -1)
            curr->getCurrCycle() = cycle;
    }
}

/*----------- Getters -----------*/

int Tree::getNode() const
{
    return node;
}

vector<Tree *> * Tree::getChildren()
{ /* each children is a tree */
    return &children;
}

int &Tree::getRank()
{ /* number of children */
    return rank;
}

int &Tree::getDepth()
{
    return depth;
}

//==========================RootTree=====================================

/* RootTree Constructor */
RootTree::RootTree(int rootLabel):Tree(rootLabel){}

Tree* RootTree::clone() const
{  /* Deep-Copy */
    return (new RootTree(*this));
}

int RootTree::traceTree()
{
    return getNode();
}

/*----------- Getters -----------*/

int& RootTree::getCurrCycle()
{  /* helps CycleTree traceTree */
    int fakeC = -1;
    int* p = &fakeC;
    return *p;
}

//==========================CycleTree=====================================

/* CycleTree Constructor */
CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle){}

Tree * CycleTree::clone() const
{  /* Deep-Copy */
    return (new CycleTree(*this));
}

int CycleTree::traceTree() {
    int output = getNode();
    Tree *curr = this;
    unsigned int cycles = getCurrCycle();
    for (unsigned int i = 0; (i < cycles) & (curr->getRank() != 0); ++i) {
        output = curr->getChildren()->at(0)->getNode();
        curr = curr->getChildren()->at(0);
    }
    return output;
}

/*----------- Getters -----------*/

int& CycleTree::getCurrCycle()
{  /* helps its traceTree */
        return currCycle;
}

//==========================MaxRankTree=====================================

/* MaxRankTree Constructor */
MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel){}

Tree *MaxRankTree::clone() const
{  /* Deep-Copy */
    return (new MaxRankTree(*this));
}

int MaxRankTree::traceTree()
{
    vector<Tree*> sameRank;
    sameRank.push_back(this);
    updateSameRankBFS(&sameRank);
    if(sameRank.size() == 1)
        return sameRank.at(0)->getNode();
    else
    {
        Tree* min = sameRank.at(0);
        for (auto &k : sameRank) {
            if (min->getDepth() > k->getDepth())
                min = k;
            else if (min->getDepth() == k->getDepth()) {
                if (min->getNode() > k->getNode())
                    min = k;
            }
        }
        return min->getNode();
    }
}

void MaxRankTree::updateSameRankBFS(vector<Tree*> *sameRank)
{  /* first comparison - by rank */
    int maxRank = sameRank->at(0)->getRank();
    queue<Tree*> q;
    q.push(this);
    while(!q.empty()){
        Tree* curr = q.front(); q.pop();
        if(curr->getRank() >= maxRank)
        {
            if(curr->getRank() > maxRank) {
                sameRank->clear();
                maxRank = curr->getRank();
            }
            if(curr->getNode() != getNode())
                sameRank->push_back(curr);
        }
        unsigned int count=curr->getChildren()->size();
        for (unsigned int i = 0; i < count; ++i)
            q.push(curr->getChildren()->at(i));
    }
}

/*----------- Getters -----------*/

int& MaxRankTree::getCurrCycle()
{  /* helps CycleTree traceTree */
    int fakeC = -1;
    int* p = &fakeC;
    return *p;
}