#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>
#include <queue>
using namespace std;

// Copy Constructor (public)
// Distructor (public)

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);

    //void infectNode(int nodeInd); // adding to Q
    //bool isInfected(int nodeInd); // boolean (how we know?)

    vector<vector<int>> getEdges() const; // Getter for private field
    vector<int> getVertex()const; // Getter for private field
    queue<int> getQueue() const;

private:
    std::vector<std::vector<int>> edges;
    vector<int> vecs;
    queue<int> q ;
};

#endif
