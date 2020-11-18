
#include "../include/Graph.h"
#include "../include/Tree.h"
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
        vecs.push_back(0);                                      // non-infected
        edges.push_back(neighbors);
    }
}

vector<vector<int>> &Graph::getEdges() {                    // 'edges' field getter
   return edges;
}

vector<int> &Graph::getVertex() {                         // 'vecs' field getter
    return vecs;
}

queue<int> &Graph::getQueue() {                         // 'q' field getter
    return q;
}

Graph &Graph::operator=(const Graph &other) {

    this->edges = other.edges;
    this->vecs = other.vecs;
    this->q = other.q;
}

Graph::Graph(Graph &other) {
    *this =other;
}

Graph::~Graph() {
//    clear();
}

//void Graph::clear() {
//    if (this!= nullptr)
//        delete(this);
//}

void Graph::infectNode(int nodeInd) {
    if(!q.empty()) {
        int x = q.back();
        vecs[x]++;
    }
    q.push(nodeInd);
    vecs[nodeInd]++;
}

bool Graph::isInfected(int nodeInd) {
    return vecs[nodeInd] != 0;
}

void Graph::removeEdgeFromGraph(int &node) {
        edges[node].clear();
}

Tree* Graph::BFS(Session& s, Tree *root) {
    Graph *g=s.getGraph();
    queue<Tree*> nodes;
    nodes.push(root);     //root is the adress of the root, meaning the adress of node
    int tempDepth=0; Tree* temp; Tree* child;

    vector <bool> visited(edges.size());

    while (!nodes.empty()){
        int tempRank=0;
        temp=nodes.front();
       // cout << "temp: " << temp->getNode() << " ";
        temp->depth=tempDepth;
       // cout << "temp depth: " << temp->depth << " ";
        temp->rank=tempRank;
        //cout << "temp rank: " << temp->rank << endl;
        nodes.pop();
        for (int j = 0; j <g->edges[temp->getNode()].size(); ++j) {
            //if (!child->visited){
            if (!visited[edges[temp->getNode()][j]]){
                child=Tree::createTree(s,edges[temp->getNode()][j]);
                temp->addChild(*child);
                tempRank++;
                nodes.push(child);
                //child->visited = true;
                child->depth=tempDepth+1;
                visited[edges[temp->getNode()][j]] = true;
            }
        }
        root->getChildren().push_back(temp);

    }
   // delete (child);                                                        //check deletes
   // delete (temp);
    //delete (g);
    return root;
}





