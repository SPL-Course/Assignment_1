
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

vector<vector<int>> &Graph::getEdges() {
   return edges;
}

vector<int> &Graph::getVertex() {
    return vecs;
}

queue<int> &Graph::getQueue() {
    return q;
}

Graph Graph::clone(Graph &other) {

}

void Graph::infectNode(int nodeInd) {

    if(!q.empty()) {

        int x = q.back();
        cout << " toUse: " << getQueue().back() << " " ;
        cout << "toUse before: " << (vecs[x]) << " ";;
        vecs[x]++;
        cout << "toUse after: " << (vecs[x]) << " ";;
    }

    q.push(nodeInd);
    cout << " toPush: " << getQueue().back() << " ";
    cout << " toPush before: " << (vecs[nodeInd]) << " ";
    vecs[nodeInd]++;
    cout << " toPush after: " << (vecs[nodeInd]) << " ";


}

bool Graph::isInfected(int nodeInd) {
    return vecs[nodeInd] != 0;
}



