
#include "../include/Graph.h"
#include "../include/Tree.h"
using namespace std;

Graph:: Graph(vector<vector<int>> matrix): edges(), vecs() {

   int m = matrix.size();
   vecs = vector<int>(m,0);
   for (int i = 0; i < m; ++i) {
       int n = matrix.at(i).size();
       vector<int> neighbors;
       for (int j = 0; j < n; ++j){
           int containsEdge = matrix.at(i).at(j);
              if (containsEdge == 1)
                    neighbors.push_back(j);
       }
       edges.push_back(neighbors);
    }
}


void Graph::infectNode(int nodeInd)
{ // if(!isInfected(nodeInd)
    vecs.at(nodeInd)++;
}

bool Graph::isInfected(int nodeInd){
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
   for (int i = 0; (i < fatherEdgesSize) & !output; ++i) {
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
            int amountOfNodes = g->getEdges().at(node).size();
            for (int i = 0; i < amountOfNodes; ++i) {
                int neighbor = edges.at(node).at(i);
                if (neighbor != node && !visited.at(neighbor)) {
                    Tree *child = Tree::createTree(s, neighbor);
                    child->depth = bfsTree->depth + 1;
                    bfsTree->addChildShallow(child);
                    visited.at(neighbor) = true;
                    nodes.push(child);
                }
            }
        }

        else {
            int amountOfNodes = g->getEdges().at(currNode).size();
            for (int i = 0; i < amountOfNodes; ++i) {
                int neighbor = edges.at(currNode).at(i);
                if (neighbor != node && !visited.at(neighbor)) {
                    Tree *child = Tree::createTree(s, neighbor);
                    child->depth = currT->depth + 1;
                    currT->addChildShallow(child);
                    currT->rank++;
                    visited.at(neighbor) = true;
                    nodes.push(child);
                }
            }
        }
    }
    return bfsTree;
}

Graph::Graph(const Graph &other) :edges(other.edges), vecs(other.vecs) {}
