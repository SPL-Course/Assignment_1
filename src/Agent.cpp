
#include "../include/Agent.h"
#include "../include/Tree.h"    //added
#include <iostream>
using namespace std;

/*----------Agent------------*/

Agent::Agent() {}
// Agent::~Agent() {} // Added 19.11 20:25

/*----------Virus------------*/

Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd){}

Agent *Virus::clone() const
{
    return (new Virus(*this));
}

int Virus::getNodeInd() const
{
    return nodeInd;
}

void Virus::act(Session &session) {

    if (!session.done.at(session.counter)) {
        Graph *graph = session.getGraph();
        int node = this->nodeInd;
        int status = graph->vecs.at(node);
        if (status == 0) {
            graph->vecs.at(node) == 1;
            const Agent *a = new Virus(node);
            session.addAgent(*a);
        }
        if (status == 1) {
            graph->vecs.at(node) = 2;
            session.enqueueInfected(graph->vecs.at(node));
        }
        if (status == 2) {
            bool ans = graph->infectNextNode(graph->vecs.at(node));
            if (ans)
                session.done.at(session.counter) = 1;
        }
    }
}



//  Graph *g = session.getGraph();
//    Tree *root=Tree::createTree(session,nodeInd);     //fix root
//    Tree *bfsTree = g->BFS(session,root);
//    g->infectNode(bfsTree->traceTree()); // prepare next insure
//}

/*------Contact Tracer--------*/

ContactTracer::ContactTracer() : Agent()
{
    //ContactTracer *c;
    //    clone();
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
