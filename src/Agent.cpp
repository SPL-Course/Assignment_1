
#include "../include/Agent.h"
#include <iostream>
using namespace std;

Agent::Agent(){}
//    if(agentType=='c')            //check how to use Json to get access to input
//        ContactTracer();
//    else
//         Virus(0);                //check Virus first value get
//}


void Agent::act(Session &session) {}
//    vector<Agent*> a= session.getAgents();
//    Agent *first=a.front();
//    if((*first).agentType == 'c') {
//         ContactTracer c2= ContactTracer();
//         c2.act(session);
//    }
//    else
//        Virus v2= Virus(*session);
//}


/*----------Virus------------*/
Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd) {}
Virus::~Virus() {}
Virus::Virus(Virus &other): Agent(), nodeInd(other.nodeInd) {}

int Virus::getNodeInd() { return nodeInd; }
void Virus::act(Session &session) {}

//Virus Virus::clone(Virus other) {
//    this->nodeInd = other.getNodeInd();
//}

/*------Contact Tracer--------*/

ContactTracer::ContactTracer() : Agent() {}
void ContactTracer::act(Session &session) {}
