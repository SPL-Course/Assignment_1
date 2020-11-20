
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
//#include "Agent.h"
//using namespace std;

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    void infectNode(int nodeInd); // @
    bool isInfected(int nodeInd); // @

    Graph(Graph &other);                 // Copy constructor
    void removeEdgeFromGraph(int &node); // change (int &) to (int)
    //Tree* BFS(Session& s, int *root);
    std::vector<int> vecs;                    // private to public

    //  vector<vector<int>> &getEdges();       // 'edges' field getter
    //  vector<int> &getVertex();              // 'vecs' field getter
//      queue<int> &getQueue();              // 'q' field getter
    //  Graph& operator=(const Graph &other);  // Assignment operator
    //  virtual ~Graph();                      // Destructor

private:
    std::vector<std::vector<int>> edges;
    //  vector<int> vecs; // private to public
//      queue<Virus> q;
};

#endif
