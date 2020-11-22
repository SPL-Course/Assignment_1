
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
    Tree *bfsTree = Tree::createTree(s,node)->clone();
    Tree *currT = bfsTree;
    Graph *g=s.getGraph();
    queue<int> nodes;
    nodes.push(node);
    while(!nodes.empty()){
        int curr = nodes.front(); nodes.pop();
        if(curr != node)
            currT = Tree::createTree(s, curr)->clone();
        int amountOfNodes = g->getEdges().at(curr).size();
        for (int i = 0; i < amountOfNodes; ++i) {
            int neighbor = edges.at(curr).at(i);
            if(neighbor != node){
                Tree *child = Tree::createTree(s, neighbor);
                child->depth = currT->depth + 1;
                currT->addChildShallow(child);
                currT->rank++;
                nodes.push(neighbor);
            }
        }
    }
    return bfsTree;
}

Graph::Graph(Graph &other): edges(other.edges), vecs(other.vecs) {}

//Tree* Graph::BFS_V2(Session& s, Tree *root) {
//
//    Graph *g=s.getGraph();
//    queue<Tree*> nodes; Tree* temp; Tree* child;
//    vector <bool> visited(g->edges.size());
//    int tempDepth=0;
//    nodes.push(root); //root is the address of the root, meaning the address of node
//    while (!nodes.empty()){
//        int tempRank=0;
//        temp=nodes.front();
//        temp->depth=tempDepth;
//        temp->rank=tempRank;
//        nodes.pop();
//        int size = g->getEdges()[temp->getNode()].size();
//        for (int j = 0; j < size ; ++j) {
//            temp=nodes.front(); nodes.pop();
//            visited[temp->getNode()] = true;
//            for (int j = 0; j < g->edges[temp->getNode()].size(); ++j) {
//                if (!visited[edges[temp->getNode()][j]]){
//                    child=Tree::createTree(s,edges[temp->getNode()][j]);
//                    temp->rank = temp->rank+1; child->depth=temp->depth+1;
//                    temp->addChild(*child);
//                    tempRank++;
//                    nodes.push(child);
//                    child->depth=tempDepth+1;
//                    visited[edges[temp->getNode()][j]] = true;
//                }
//            }
//            root->getChildren().push_back(temp);
//        }
//    }
//        return root;
//}
