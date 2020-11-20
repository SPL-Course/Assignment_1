
#include "../include/Agent.h"
#include "../include/Tree.h"    //added
#include <iostream>
using namespace std;

/*----------Agent------------*/

Agent::Agent() {}
// Agent::~Agent() {} // Added 19.11 20:25

/*----------Virus------------*/

Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd)
{
    clone();
}

Agent *Virus::clone() const
{
    return (new Virus(*this));
}

int Virus::getNodeInd() const
{
    return nodeInd;
}

void Virus::act(Session &session)
{
    Graph *g = session.getGraph();
//    Tree *root=Tree::createTree(session,nodeInd);     //fix root
//    Tree *bfsTree = g->BFS(session,root);
//    g->infectNode(bfsTree->traceTree()); // prepare next insure
}

/*------Contact Tracer--------*/

ContactTracer::ContactTracer() : Agent()
{
    clone();
}

Agent *ContactTracer::clone() const
{
    return (new ContactTracer());
}

void ContactTracer::act(Session &session)
{
//    Graph *g=session.getGraph();
//    Tree *root=Tree::createTree(session,g->getQueue().back().getNodeInd());
//    Tree *bfsTree = g->BFS(session,root);
//    int num= bfsTree->traceTree();
//    g->removeEdgeFromGraph(num);
}
