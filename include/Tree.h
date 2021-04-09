#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"
using namespace std;

class Tree{
public:
    /*--Constructor--*/
    Tree(int rootLabel);

    /*--Rule Of 5--*/
    virtual ~Tree();                    // destructor
    Tree(const Tree &other);            // copy constructor
    Tree& operator=(const Tree &other); // copy assignment operator
    Tree(Tree &&other);                 // move constructor
    Tree& operator=(Tree &&other);      // move assignment operator

    void clear();
    void steal(Tree &other);
    virtual Tree *clone() const = 0;

    /*--Given Functions--*/
    static Tree* createTree(const Session& session, int rootLabel);
    void addChild(const Tree& child);
    void addChild(Tree* child);         // adds child pointer
    virtual int traceTree() = 0;

    /*--Help Functions--*/
    void updateDepthsBFS();             // depth field updater
    void updateCyclesBFS(int cycle);    // currCycle field updater

    /*-----Getters------*/
    int getNode() const;
    int &getRank();
    int &getDepth();
    vector<Tree*> *getChildren();
    virtual int& getCurrCycle() = 0;

private:
    int node;
    int rank;                           // tree children's size
    int depth;

protected:
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    /*--Constructor--*/
    CycleTree(int rootLabel, int currCycle);

    virtual ~CycleTree() = default;                   // uses Tree destructor
    virtual Tree *clone() const;                      // deep-copy

    /*--Given Functions--*/
    virtual int traceTree();

    /*-----Getters------*/
    virtual int& getCurrCycle();

private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    /*--Constructor--*/
    MaxRankTree(int rootLabel);

    virtual ~MaxRankTree() = default;                 // uses Tree destructor
    virtual Tree *clone() const;                      // deep-copy

    /*--Given Functions--*/
    virtual int traceTree();

    /*--Help Functions--*/
    void updateSameRankBFS(vector<Tree*> *sameRank);  // first comparison

    /*-----Getters------*/
    virtual int& getCurrCycle();                      // for CycleTree traceTree
};

class RootTree: public Tree{
public:
    /*--Constructor--*/
    RootTree(int rootLabel);                          // constructor

    virtual ~RootTree() = default;                    // uses Tree destructor
    virtual Tree *clone() const;                      // deep-copy

    /*--Given Functions--*/
    virtual int traceTree();

    /*-----Getters------*/
    virtual int& getCurrCycle();                      // for CycleTree traceTree
};

#endif
