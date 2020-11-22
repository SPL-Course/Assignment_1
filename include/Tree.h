#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"
/*check if include ok -> else: class Session;*/
using namespace std;

class Tree{
/* When infect - notice to do last one rotation (1-->2) */

public:
    Tree(int rootLabel);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    void addChild(const Tree& child);
    void addChildShallow(Tree* child);

    virtual ~Tree();
    void clear();
    Tree(const Tree &other);
    virtual Tree *clone() const=0;
    //Tree(Tree &&other);
    //void steal(Tree &other);
    //Tree& operator=(const Tree &t);
    //Tree& operator=(Tree &&t);

    int getNode() const;
    vector<Tree*> *getChildren();
    int rank;
    int depth;

protected:
    int node;
    std::vector<Tree*> children;
};


class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual Tree *clone() const;
    virtual ~CycleTree() = default;
    int getCurrCycle() const;

protected:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);   
    virtual int traceTree();
    virtual Tree *clone() const;
    virtual ~MaxRankTree() = default;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel); 
    virtual int traceTree();
    virtual Tree *clone() const;
    virtual ~RootTree() = default;
};

#endif
