
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>

class Tree;
class Session;

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    Graph(const Graph &other);
    bool infectNextNode(int father);
    Tree* BFS(Session &s, int node);
    void removeNodeEdges(int toRemove);

    std::vector<std::vector<int>> getEdges() const;
    std::vector<int> vecs;

private:
    std::vector<std::vector<int>> edges;
};

#endif
