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
    static vector<int> getVertex(); // Getter for private field
    static queue<int> getQueue();

private:
    std::vector<std::vector<int>> edges;
    static vector<int> vecs;
    static queue<int> q ;
};

#endif
