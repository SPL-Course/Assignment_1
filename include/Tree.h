
#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h" // added 16.11 18:00

class Tree{

/* When infect - notice to do last one rotation (1-->2) */

public:
    Tree(int rootLabel);              // Constructor (root)
    void addChild(const Tree& child); // Add node to Tree
   void addChild(const Tree &&child);
    virtual ~Tree();                  // Added - 12/11/20
    Tree(Tree &other);
    virtual Tree* clone() const=0;

    static Tree* createTree(const Session& session, int rootLabel); // returns a pointer to Tree
    virtual int traceTree()=0;        // Which node to disconnect?
    int getNode() const;
    vector<Tree*> getChildren() const;

    bool visited;
    int depth, rank;

protected:
    int node;                         // Tree root
    std::vector<Tree*> children;      // Pointer's vector to children
};


class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree(); // if 0 - root, else go-left currCycle times
    virtual Tree* clone() const ;

private:
    int currCycle;                    // How many steps to take
};

class MaxRankTree: public Tree{

/* Next-Node is: 
    1. Most Children 
    2. Smallest depth
    3. Most-Left */

public:
    MaxRankTree(int rootLabel);   
    virtual int traceTree(); // in loop updating Tree *max
    virtual Tree* clone() const;
};

class RootTree: public Tree{     

/* only root of Tree */

public:
    RootTree(int rootLabel); 
    virtual int traceTree();  // return relevant tree's getNode();
    virtual Tree* clone() const;
};

#endif
