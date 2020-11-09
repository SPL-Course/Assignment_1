#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>
#include <queue>

// Copy Constructor (public)
// Distractor (public)

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix); // Constructor

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    const std::vector<std::vector<int>> getEdges();
    const std::vector<int> getVertex();
    const std::queue<int> getQueue();

private:
    std::vector<std::vector<int>> edges;
    std::vector<int> vecs ;
    std::queue<int> q ;
};

#endif
