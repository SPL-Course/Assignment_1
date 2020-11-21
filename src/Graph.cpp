
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

//int * Graph::BFS(Session &s, int *root) {}

//Tree* Graph::BFS(Session& s, Tree *root) {
//
//    Graph *g=s.getGraph(); queue<Tree*> nodes; Tree* temp; Tree* child;
//    vector <bool> visited(edges.size());
//
//    nodes.push(root);
//    while (!nodes.empty()){
//        temp=nodes.front(); nodes.pop();
//        visited[temp->getNode()] = true;
//        for (int j = 0; j < g->edges[temp->getNode()].size(); ++j) {
//            if (!visited[edges[temp->getNode()][j]]){
//                child=Tree::createTree(s,edges[temp->getNode()][j]);
//                temp->rank = temp->rank+1; child->depth=temp->depth+1;
//                temp->addChild(*child);
//                nodes.push(child);
//                visited[edges[temp->getNode()][j]] = true;
//            }
//        }
//    }
//    return root;
//}

/*------------Unused_Functions------------*/

//vector<vector<int>> &Graph::getEdges() {  // 'edges' field getter
//   return edges;
//}

//vector<int> &Graph::getVertex() {         // 'vecs' field getter
//    return vecs;
//}

//queue<Virus> & Graph::getQueue() { return q;}

//queue<int> &Graph::getQueue() {           // 'q' field getter
//    return q;
//}

//queue<Virus> & Graph::getQueue() {
//    return q;
//}

//Graph &Graph::operator=(const Graph &other) {
//
//    edges=other.edges;
//    vecs = other.vecs;
//    //q = other.q;
//    int i=q.size();
//    queue<Virus> vaid;
//    while(i>0){
//        Virus ad=other.q.front().clone();
//        q.push(ad)
//    }
//}

//Graph::~Graph() {
//    clear();
//}

//void Graph::clear() {
//    if (this!= nullptr)
//        delete(this);
//}

/*------Old_infectedNode(V1)------*/
//void Graph::infectNode(int nodeInd){
//    if (!q.empty()) {
//        int x = q.back().nodeInd;
//        vecs[x]++;
//    }
//    Virus a(nodeInd);
//    q.push(a);
//    vecs[nodeInd]++;
//}

/*------Old_infectedNode(V2)------*/
//void Graph::infectNode(int nodeInd){
//   if (!q.empty()) {
//        int x = q.back();
//        vecs[x]++;
//    }
//    q.push(nodeInd);
//    vecs[nodeInd]++;
//}

/*-----------------------------------------*/





