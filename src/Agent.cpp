
#include "../include/Agent.h"
#include "../include/Tree.h" /*added*/
#include <iostream>
using namespace std;

/*----------Agent------------*/

Agent::Agent() {}
Agent::~Agent() {}

/*----------Virus------------*/

Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd){}

void Virus::act(Session &session) {

    if (!session.getDone()->at(session.counter)) {
        Graph *graph = session.getGraph();
        int node = this->nodeInd;
        int status =graph->vecs.at(node);
        if (status == 0) {
            graph->vecs.at(node) =1;
            const Agent *a = new Virus(node);
            session.addAgent(*a);
            status++;
        }
        if (status == 1) {
            graph->vecs.at(node) = 2;
            session.enqueueInfected(node);
            status++;
        }
        if (status == 2) {
            bool ans = graph->infectNextNode(node);
            if (ans)
                session.getDone()->at(session.counter) = true;
        }
    }
}

Agent *Virus::clone() const
{
    return (new Virus(*this));
}

int Virus::getNodeInd() const
{
    return nodeInd;
}

/*------Contact Tracer--------*/

ContactTracer::ContactTracer() : Agent() {}

void ContactTracer::act(Session &session)
{
    if(!session.getInfected()->empty()){
//        int node=session.dequeueInfected();
        //Tree *tree=session.getGraph()->BFS(session,node);
        //int disconnected=tree->traceTree();
        //session.getGraph()->removeNodeEdges(disconnected);
    } else
        session.getDone()->at(session.counter)=true;
}

Agent *ContactTracer::clone() const
{
    return (new ContactTracer());
}



