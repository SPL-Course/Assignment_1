
// Last edited on 9/11/2020
// Need to build Operation Function

#include "Graph.h"
#include <iostream>

using namespace std;

Graph:: Graph(vector<vector<int>> matrix):edges() { // Constructor

    for(vector<int> node : matrix) {
        vector<int> neighbors;
        int counter = 0;
        for (int other : node) {
            if (other == 1)
                neighbors.push_back(counter);
            counter = counter + 1;
        }
        edges.push_back(neighbors);
    }
}

vector<vector<int>> Graph::getEdges() const{
   return edges;
}

void infectNode(int nodeInd){ // adding to Q


}

bool isInfected(int nodeInd){ // boolean (how we know?)


}


