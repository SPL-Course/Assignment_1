
// Last edited on 11/11/2020

#include "../include/Graph.h"
#include <iostream>
using namespace std;

Graph:: Graph(vector<vector<int>> matrix): edges(), vecs(), q() {  // Constructor

    for(vector<int> node : matrix) {
        vector<int> neighbors;
        int counter = 0;
        for (int other : node) {
            if (other == 1)
                neighbors.push_back(counter);
            counter = counter + 1;
        }
        vecs.push_back(0);                // non-infected
        edges.push_back(neighbors);
    }
}

vector<vector<int>> &Graph::getEdges() {  // 'edges' field getter

   return edges;
}

vector<int> &Graph::getVertex() {         // 'vecs' field getter

    return vecs;
}

queue<int> &Graph::getQueue() {           // 'q' field getter

    return q;
}

Graph & Graph::operator=(Graph &other) {

    this->edges = other.edges;
    this->vecs = other.vecs;
    this->q = other.q;
}

Graph::Graph(Graph &other) {

    *this = other;
}

Graph::~Graph() { }

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



