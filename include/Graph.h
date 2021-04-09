#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>

class Tree;
class Session;

class Graph{
public:
    /*--Constructor--*/
    Graph(std::vector<std::vector<int>> matrix);

    virtual ~Graph();                     // default destructor
    Graph(const Graph &other);            // copy constructor

    /*--Given Functions--*/
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    /*--Help Functions--*/
    Tree* BFS(Session &s, int node);      // builds a BFS tree
    void removeNodeEdges(int toRemove);   // disconnects a node

    /*-----Getters-------*/
    std::vector<std::vector<int>> getEdges() const;
    std::vector<int> *getVecs();

private:
    std::vector<std::vector<int>> edges;
    std::vector<int> vecs;                // each node infection phase: 0-1-2
};

#endif
