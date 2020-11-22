
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

Tree::Tree(const Tree &other): children(vector<Tree*>()),
    depth(other.depth), rank(other.rank), node(other.node)
{
    int size = other.children.size();
    for(unsigned int i=0; i < size; i++){
        children.push_back(other.children.at(i)->clone());
    }
}

//Tree& Tree::operator=(const Tree &other)
//{
//    if(this != &other){
//        clear();
////        for(auto& child: other.children)
////            children.push_back(child);
//        int size = other.children.size();
//        for (unsigned int i = 0; i < size; ++i) {
//            children.push_back(other.children.at(i)->clone());
//        }
//    }
//    return *this;
//}

//Tree::Tree(Tree &&other): children(other.children), depth(other.depth),
//     rank(other.rank), node(other.node)
//{
//    steal(other);
//}

//Tree &Tree::operator=(Tree &&other)
//{
//    if(this != &other){
//        clear();
//        node = other.node;
//        rank = other.rank;
//        depth = other.depth;
//        children = other.children;
//        steal(other);
//    }
//    return *this;
//}

//void Tree::steal(Tree &other)
//{
////    for(unsigned int i = 0; i<other.children.size(); i++)
////        children.at(i) = nullptr;
//}

Tree * Tree::createTree(const Session &session, int rootLabel)
{
    TreeType tType = session.getTreeType();
    if(tType==MaxRank)
        return new MaxRankTree(rootLabel);
    if(tType==Cycle)
        return new CycleTree(rootLabel,0);
    if(tType==Root)
        return new RootTree(rootLabel);
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
    for (int i = 0; i < currCycle & length != 0; ++i) {
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
    for (int k = 0; k < sameRank.size(); ++k) {
        if(min->depth>sameRank.at(k)->depth)
            min=sameRank.at(k);
        if(min->depth==sameRank[k]->depth){
            if(min->getNode()>sameRank[k]->getNode())
                min=sameRank[k];
        }
    }
    return min->getNode();
}