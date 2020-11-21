
#include "../include/Graph.h"
#include "../include/Tree.h"
#include <iostream>
using namespace std;

Graph:: Graph(vector<vector<int>> matrix): edges(), vecs()
{
    for(vector<int> node : matrix) {

        vector<int> neighbors;
        int counter = 0;
        for (int other : node) {
            if (other == 1)
                neighbors.push_back(counter);
            counter = counter + 1;
        }
        vecs.push_back(0); // initiates healthy nodes
        edges.push_back(neighbors);
    }
}

Graph::Graph(Graph &other): edges(other.edges), vecs(other.vecs) {}

bool Graph::isInfected(int nodeInd)
{
    return vecs[nodeInd] != 0;
}

void Graph::infectNode(int nodeInd)
{
// if(!isInfected(nodeInd)
    vecs[nodeInd]++;
}

std::vector<std::vector<int>> Graph::getEdges() const
{
    return edges;
}

void Graph::removeNodeEdges(int toRemove)
{
    int mainSize = edges.size();
    for (int i = 0; i < mainSize; ++i) {
             if(i == toRemove)
                 edges.at(i).clear();
             else {
                vector<int> updated;
                int innerSize = edges.at(i).size();
                for (int j = 0; j < innerSize; ++j) {
                    if(edges.at(i).at(j) != toRemove)
                        updated.push_back(edges.at(i).at(j));
                }
                edges[i] = vector<int>(updated);
             }
    }
}

bool Graph::infectNextNode(int father)
{
   bool output = false;
   int fatherEdgesSize = edges.at(father).size();
   for (int i = 0; i < fatherEdgesSize & !output; ++i) {
        int neighbor = edges.at(father).at(i);
        int status = vecs.at(neighbor);
        if (status == 0) {
            infectNode(neighbor);
            output = true;
        }
   }
   return output;
}

Tree * Graph::BFS(Session &s, int node) {

}
