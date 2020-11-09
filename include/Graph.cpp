
// Last edited on 9/11/2020
// Need to build Operation Function

#include "Graph.h"
#include <iostream>
using namespace std;

Graph:: Graph(vector<vector<int>> matrix): edges(), vecs(), q() { // Constructor

    for(vector<int> node : matrix) {
        vector<int> neighbors;
        int counter = 0;
        for (int other : node) {
            if (other == 1)
                neighbors.push_back(counter);
            counter = counter + 1;
        }
        vecs.push_back(0); // zero for non-infected
        edges.push_back(neighbors);
    }
}

const vector<vector<int>> Graph::getEdges(){
   return edges;
}

const vector<int> Graph::getVertex(){
    return vecs;
}

const queue<int> Graph::getQueue(){
    return q;
}

void infectNode(int nodeInd){
   //Graph::getQueue().push(nodeInd);
   //Graph::getVertex().at(nodeInd) = 1;
}

bool isInfected(int nodeInd){
    //return Graph::getVertex().at(nodeInd) == 1;
}


