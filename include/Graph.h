
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
// #include "Agent.h"

class Tree;
class Session;

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    void infectNode(int nodeInd);                   // Done - to check
    bool isInfected(int nodeInd);                   // Done - to check
    Graph(const Graph &other);                            // Done - to check
    std::vector<std::vector<int>> getEdges() const; // Done - to check
    void removeNodeEdges(int toRemove);             // Done - checked
    bool infectNextNode(int father);                // Done - checked
    Tree* BFS(Session &s, int node);
    std::vector<int> vecs;

private:
    std::vector<std::vector<int>> edges;
};

#endif
