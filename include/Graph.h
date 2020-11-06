#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix) {}; // Constructor
    
    // Copy Constructor
    // Distructor

    void infectNode(int nodeInd); // adding to Q
    bool isInfected(int nodeInd); // boolean (how we know?)

    /* Allel foult */
    std::vector<std::vector<int>> getEdges(); // Getter for private field
    std::vector<std::vector<int>> main();

private:
    std::vector<std::vector<int>> edges;
    /* Adding protected Q to use*/

};

#endif
