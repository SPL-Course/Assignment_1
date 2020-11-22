
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
   for(unsigned int i=0; i < children.size(); i++){
       if(children.at(i) != nullptr) {
            delete (children.at(i));
            children.at(i) = nullptr;
       }
   }
}

Tree::Tree(const Tree &other): children(vector<Tree*>()),
    depth(other.depth), rank(other.rank), node(other.node)
{
    for(unsigned int i=0; i < other.children.size(); i++){
        children.push_back(other.children.at(i)->clone());
    }
}

Tree& Tree::operator=(const Tree &t) {
    if(this != &t) {
        clear();
        for(unsigned int i=0; i<t.children.size(); i++)
            children.push_back(t.children.at(i)->clone());
    }
    return *this;
}

Tree::Tree(Tree &&other): children(move(other.children)), depth(other.depth),
     rank(other.rank), node(other.node)
{
    steal(other);
}

Tree &Tree::operator=(Tree &&other)
{
    if(this != &other){
        clear();
        node = other.node;
        rank = other.rank;
        depth = other.depth;
        children = other.children;
        steal(other);
    }
    return *this;
}

void Tree::steal(Tree &other)
{
    for(unsigned int i=0; i<other.children.size(); i++)
        children.at(i) = nullptr;
}

Tree * Tree::createTree(const Session &session, int rootLabel)
{
    Tree* treeP;
    TreeType tType = session.getTreeType();
    if(tType==MaxRank)
        treeP = new MaxRankTree(rootLabel);
    if(tType==Cycle)
        treeP = new CycleTree(rootLabel,0);
    if(tType==Root)
        treeP = new RootTree(rootLabel);
    return treeP;
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

vector<Tree *> *Tree::getChildren() {
    return &children;
}

//==========================RootTree=====================================

RootTree::RootTree(int rootLabel):Tree(rootLabel){}

Tree * RootTree::clone() const {
    return (new RootTree(*this));
}

int RootTree::traceTree() {
    return getNode();
}

//==========================CycleTree=====================================
CycleTree::CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){}

Tree * CycleTree::clone() const {
    return (new CycleTree(*this));
}

int CycleTree::traceTree() {
    int output=getNode();
    if(currCycle==0)
        return output;
    Tree* root = getChildren()->at(0);
    Tree* point;
    for (int i = 1; i <currCycle; ++i) {
        point= root->getChildren()->at(0);
        root=point;
    }
    output=root->getNode();
    delete (root);
    delete (point);
    return output;
}

int CycleTree::getCurrCycle() const {
    return currCycle;
}

//==========================MaxRankTree=====================================
MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel){}

Tree * MaxRankTree::clone() const {
    return (new MaxRankTree(*this));
}

int MaxRankTree::traceTree() {

    Tree *max = this;
    for (auto& curr :children) {
        if (max->rank < curr->rank)
            max = curr;
        else if (max->rank == curr->rank) {
             if (curr->depth < max->depth)
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