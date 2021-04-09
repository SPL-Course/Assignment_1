
#include "../include/Graph.h"
#include "../include/Tree.h"
using namespace std;

//====================Graph==========================

/* Graph Constructor */
Graph:: Graph(vector<vector<int>> matrix):
        edges(vector<vector<int>>()), vecs(vector<int>())
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

/* Graph Default Destructor */
Graph::~Graph() {}

/* Graph Copy Constructor */
Graph::Graph(const Graph &other) : edges(other.edges), vecs(other.vecs) {}

/*-----Graph: Given Functions-----*/

void Graph::infectNode(int nodeInd)
{
    vecs.at(nodeInd)++;
}

bool Graph::isInfected(int nodeInd)
{
    return vecs.at(nodeInd) != 0;
}

/*--------Help Functions--------*/

Tree *Graph::BFS(Session &s, int node)
{  // builds a BFS tree for Contact Tracer

    Tree *bfsTree = Tree::createTree(s,node);
    Tree *currT; Tree *child;
    Graph *g=s.getGraph();

    queue<Tree*> nodes;
    nodes.push(bfsTree);

    vector<bool> visited (edges.size(), false);
    visited.at(node) = true;

    while(!nodes.empty())
    {
        currT = nodes.front(); nodes.pop();

        int currNode = currT->getNode();
        unsigned int amountOfNodes = g->getEdges().at(currNode).size();
        for (unsigned int i = 0; i < amountOfNodes; ++i)
        {
            int neighbor = edges.at(currNode).at(i);
            if (neighbor != node && !visited.at(neighbor))
            {
                child = Tree::createTree(s, neighbor);
                if (currNode == node)
                    bfsTree->addChild(child);
                else
                {
                    child->getDepth() = currT->getDepth();
                    currT->addChild(child);
                }
                nodes.push(child);
                visited.at(neighbor) = true;
            }
        }
    }
    return bfsTree;
}

void Graph::removeNodeEdges(int toRemove)
{   // disconnects a node from the graph

    int mainSize = edges.size();
    for (int i = 0; i < mainSize; ++i) {
             if(i == toRemove)
                 edges.at(i).clear();
             else
             {
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

/*----------- Getters -----------*/

vector<vector<int>> Graph::getEdges() const
{
    return edges;
}

vector<int> *Graph::getVecs()
{
    return &vecs;
}

