
#include "../include/Graph.h"
#include "../include/Tree.h"
using namespace std;

Graph:: Graph(vector<vector<int>> matrix):
    vecs(vector<int>()), edges(vector<vector<int>>())
{
   unsigned int m = matrix.size();
   vecs = vector<int>(m,0);
    for (unsigned int i = 0; i < m; ++i) {
        unsigned int n = matrix.at(i).size();
        vector<int> neighbors;
        for (unsigned int j = 0; j < n; ++j){
            int containsEdge = matrix.at(i).at(j);
            if (containsEdge == 1)
                neighbors.push_back(j);
        }
        edges.push_back(neighbors);
    }
}


void Graph::infectNode(int nodeInd)
{
    vecs.at(nodeInd)++;
}

bool Graph::isInfected(int nodeInd)
{
    return vecs[nodeInd] != 0;
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
                 unsigned int innerSize = edges.at(i).size();
                for (unsigned int j = 0; j < innerSize; ++j) {
                    if(edges.at(i).at(j) != toRemove)
                        updated.push_back(edges.at(i).at(j));
                }
                edges.at(i) = vector<int>(updated);
             }
    }
}

bool Graph::infectNextNode(int father)
{
   bool output = false;
   unsigned int fatherEdgesSize = edges.at(father).size();
   for (unsigned int i = 0; (i < fatherEdgesSize) & !output; ++i) {
        int neighbor = edges.at(father).at(i);
        int status = vecs.at(neighbor);
        if (status == 0) {
            infectNode(neighbor);
            output = true;
        }
   }
   return output;
}

Tree *Graph::BFS(Session &s, int node)
{
    Tree *bfsTree = Tree::createTree(s,node);
    Tree *currT;
    vector<bool> visited (edges.size(), false);
    Graph *g=s.getGraph();
    queue<Tree*> nodes;
    nodes.push(bfsTree);
    visited.at(node) = true;
    while(!nodes.empty()) {
        currT = nodes.front();
        nodes.pop();
        int currNode = currT->getNode();
        if (currNode == node) {
            unsigned int amountOfNodes = g->getEdges().at(node).size();
            for (unsigned int i = 0; i < amountOfNodes; ++i) {
                int neighbor = edges.at(node).at(i);
                if (neighbor != node && !visited.at(neighbor)) {
                    Tree *child = Tree::createTree(s, neighbor);
                    //child->getDepth() = bfsTree->getDepth() + 1;
                    bfsTree->addChild(child);
                    //bfsTree->getRank()++;
                    visited.at(neighbor) = true;
                    nodes.push(child);
                }
            }
        }

        else {
            unsigned int amountOfNodes = g->getEdges().at(currNode).size();
            for (unsigned int i = 0; i < amountOfNodes; ++i) {
                int neighbor = edges.at(currNode).at(i);
                if (neighbor != node && !visited.at(neighbor)) {
                    Tree *child = Tree::createTree(s, neighbor);
//                    child->getDepth() = currT->getDepth()+ 1;
                    currT->addChild(child);
//                    currT->getRank()++;
                    visited.at(neighbor) = true;
                    nodes.push(child);
                }
            }
        }
    }
    return bfsTree;
}

Graph::Graph(const Graph &other) : vecs(other.vecs), edges(other.edges) {}
