//
// Created by spl211 on 10/11/2020.
//

#include "../include/Agent.h"
using namespace std;

Agent::Agent(){
//    if(agentType=='c'){                                  //check how to use Jason to get access to input
//        ContactTracer();
//    }
//    else
//         Virus(0);                                    //check Virus first value get
}

void Agent::act(Session &session) {
//    vector<Agent*> a= session.getAgents();
//    Agent *first=a.front();
//    if((*first).agentType == 'c') {
//         ContactTracer c2= ContactTracer();
//         c2.act(session);
//    }

//    else
//        Virus v2= Virus(*session);

}


Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd) {

}

ContactTracer::ContactTracer() : Agent(){

}

