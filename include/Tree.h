
#ifndef TREE_H_
#define TREE_H_

#include <vector>
class Session;

class Tree{

/* When infect - notice to do last one rotation (1-->2) */

public:
    Tree(int rootLabel);              // Constructor (root)
    void addChild(const Tree& child); // Add node to Tree
    virtual ~Tree();                  // Added - 12/11/20


    static Tree* createTree(const Session& session, int rootLabel); // returns a pointer to Tree
    virtual int traceTree()=0;        // Which node to disconnect?
private:
    int node;                         // Tree root
    std::vector<Tree*> children;      // Pointer's vector to children
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();

private:
    int currCycle;                    // How many steps to take
};

class MaxRankTree: public Tree{

/* Next-Node is: 
    1. Most Children 
    2. Deepest 
    3. Most-Left */

public:
    MaxRankTree(int rootLabel);   
    virtual int traceTree();
};

class RootTree: public Tree{     

/* only root of Tree */

public:
    RootTree(int rootLabel); 
    virtual int traceTree();  
};

#endif
