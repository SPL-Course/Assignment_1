
#include "../include/Agent.h"
#include "../include/Tree.h" // Added
#include <iostream>
using namespace std;

//=================Agent===================

/* Agent Default Constructor */
Agent::Agent() {}

/* Agent Default Destructor */
Agent::~Agent() {}

//=================Virus===================

/* Virus Constructor */
Virus::Virus(int nodeInd): Agent(), nodeInd(nodeInd) {}

Agent *Virus::clone() const
{  /* deep-copy */
    return (new Virus(*this));
}

/*--------Virus: Given Functions-----------*/

void Virus::act(Session &session)
{  /* infects virus-free neighbors */

    if (!session.getDone()->at(session.getIndex())) {

        bool act = false;
        Graph *graph = session.getGraph();
        int node = this->nodeInd;
        int status = graph->getVecs()->at(node);

        if (status == 0) {
            graph->getVecs()->at(node) = 1;
            int toInfect = session.toInfect(node);
            if (toInfect != -1)
            {
                fullyInfect(session, toInfect);
                act = true;
            }
            status++;
        }

        if (status == 1) {
            graph->getVecs()->at(node) = 2;
            session.enqueueInfected(node);
            if(!act) {
                int toInfect = session.toInfect(node);
                if (toInfect != -1)
                {
                    fullyInfect(session, toInfect);
                    act = true;
                }
            }
            status++;
        }

        if (status == 2)  {
            if(!act) {
                int toInfect = session.toInfect(node);
                if (toInfect == -1)
                    session.getDone()->at(session.getIndex()) = true;
                else
                    fullyInfect(session,toInfect);
            }
        }
    }
}

/*--------Help Functions--------*/

void Virus::fullyInfect(Session &session, int toInfect)
{  /* updates: vecs status, done status, agents, viruses */
    Graph *graph = session.getGraph();
    const Agent *a = new Virus(toInfect);
    graph->infectNode(toInfect);
    session.addAgent(*a);
    session.getViruses()->at(toInfect) = true;
    session.getDone()->push_back(false);
    session.getDone()->at(session.getIndex()) = false;
    delete (a);
}

/*----------- Getters -----------*/

int Virus::getNodeInd() const
{
    return nodeInd;
}

//=================Contact Tracer===================

/* Contact Tracer Constructor */
ContactTracer::ContactTracer() : Agent() {}

Agent *ContactTracer::clone() const
{  /* deep-copy */
    return (new ContactTracer());
}

/*-----Contact Tracer: Given Functions------*/

void ContactTracer::act(Session &session)
{  /* builds BFS tree and disconnects node */

    if(!session.getInfected()->empty()){
        int node=session.dequeueInfected();
        Tree *tree=session.getGraph()->BFS(session,node);
        if (tree->getRank() != 0) {
            if(session.getTreeType() == Cycle)
                tree->updateCyclesBFS(session.getSimulateCycle());
            int disconnected = tree->traceTree();
            session.getGraph()->removeNodeEdges(disconnected);
        }
        delete (tree);
    }
    session.getDone()->at(session.getIndex()) = true;
}





