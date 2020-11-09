#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>

// Copy Constructor (public)
// Distructor (public)

class Graph{
public:

    Graph(std::vector<std::vector<int>> matrix);

    void infectNode(int nodeInd); // adding to Q
    bool isInfected(int nodeInd); // boolean (how we know?)

    std::vector<std::vector<int>> getEdges() const; // Getter for private field
    int main();

private:
    std::vector<std::vector<int>> edges;
protected:
    std::queue<int> Q;
    std::vector<int> vertices; // **Update in Git**
};

#endif
