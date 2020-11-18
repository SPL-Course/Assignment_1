
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
using namespace std;

class Tree;
class Session;

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    vector<vector<int>> &getEdges(); // 'edges' field getter
    vector<int> &getVertex();        // 'vecs' field getter
    queue<int> &getQueue();          // 'q' field getter

    Graph(Graph &other);             // Copy constructor
    Graph& operator=(const Graph &other);  // Assignment operator
    virtual ~Graph();                // Destructor
//    void clear();

    void removeEdgeFromGraph(int &node);
    Tree* BFS(Session& s, Tree *root);

private:
    std::vector<std::vector<int>> edges;
    vector<int> vecs;
    queue<int> q;
};

#endif
