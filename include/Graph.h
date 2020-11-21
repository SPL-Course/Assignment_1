
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
// #include "Agent.h"

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    Graph(Graph &other);                // Done - to check
    void infectNode(int nodeInd);       // Done - to check
    bool isInfected(int nodeInd);       // Done - to check
    std::vector<std::vector<int>> getEdges() const; // Done - to check
    void removeNodeEdges(int toRemove); // Done - checked
    bool infectNextNode(int father);    // Done - checked
    std::vector<int> vecs;
    //Tree* BFS(Session& s, int *root);

private:
    std::vector<std::vector<int>> edges;
};

#endif
