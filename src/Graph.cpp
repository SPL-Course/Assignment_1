
#include "../include/Graph.h"
#include "../include/Tree.h"
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

//vector<vector<int>> &Graph::getEdges() {                    // 'edges' field getter
//   return edges;
//}
//
//vector<int> &Graph::getVertex() {                         // 'vecs' field getter
//    return vecs;
//}

//queue<Virus> & Graph::getQueue() {}
//queue<int> &Graph::getQueue() {                         // 'q' field getter
    //return q;
//}
//
queue<Virus> & Graph::getQueue() {
    return q;
}

Graph &Graph::operator=(const Graph &other) {

    edges=other.edges;
    vecs = other.vecs;
    //q = other.q;
//    int i=q.size();
//    queue<Virus> vaid;
//    while(i>0){
//        Virus ad=other.q.front().clone();
//        q.push(ad)
//    }
}
//
Graph::Graph(Graph &other):edges(), vecs(), q() {
    *this = other;
}
//
//Graph::~Graph() {
//    clear();
//}

//void Graph::clear() {
//    if (this!= nullptr)
//        delete(this);
//}

void Graph::infectNode(int nodeInd) {
    if(!q.empty()) {
        int x = q.back().nodeInd;
        vecs[x]++;
    }
    Virus a(nodeInd);
    q.push(a);
    vecs[nodeInd]++;

//   if (!q.empty()) {
//        int x = q.back();
//        vecs[x]++;
//    }
//    q.push(nodeInd);
//    vecs[nodeInd]++;
}

bool Graph::isInfected(int nodeInd) {
    return vecs[nodeInd] != 0;
}

void Graph::removeEdgeFromGraph(int &node) {
        edges[node].clear();
}

Tree* Graph::BFS(Session& s, Tree *root) {

    Graph *g=s.getGraph(); queue<Tree*> nodes; Tree* temp; Tree* child;
    vector <bool> visited(edges.size());

    nodes.push(root);
    while (!nodes.empty()){
        temp=nodes.front(); nodes.pop();
        visited[temp->getNode()] = true;
        for (int j = 0; j < g->edges[temp->getNode()].size(); ++j) {
            if (!visited[edges[temp->getNode()][j]]){
                child=Tree::createTree(s,edges[temp->getNode()][j]);
                temp->rank = temp->rank+1; child->depth=temp->depth+1;
                temp->addChild(*child);
                nodes.push(child);
                visited[edges[temp->getNode()][j]] = true;
            }
        }
    }
    return root;
}





