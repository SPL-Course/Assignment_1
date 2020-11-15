
#include "../include/Agent.h"
#include <iostream>
using namespace std;

Agent::Agent(): point(nullptr){}

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
Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd), v(this) {}
Virus::~Virus() { clear(); }
Virus::Virus(Virus const &other): Agent(), nodeInd(other.nodeInd) { clone();}
Virus & Virus::operator=(Virus other) { this->other; }
Virus & Virus::operator=(Virus &&other){
    if(this!=&other){
        clear();
        this->other;
    }
    return *this;
}

Virus::Virus(Virus &&other): nodeInd(other.nodeInd) {
    this->other;
    other.point;
}

Agent * Virus::clone() const {
    return (new Virus(*this));
}

void Virus::clear() {
       delete(this);
       this->point;
}

int Virus::getNodeInd() const { return nodeInd; }
void Virus::act(Session &session) {}

/*------Contact Tracer--------*/

ContactTracer::ContactTracer() : Agent(), c(this) {}
ContactTracer::ContactTracer(ContactTracer const &other): Agent() { clone(); }
ContactTracer::~ContactTracer() { clear(); }


ContactTracer & ContactTracer::operator=(ContactTracer other) { this->other;}

ContactTracer::ContactTracer(ContactTracer &&other) {
    this->other;
    other.point;
}

ContactTracer & ContactTracer::operator=(ContactTracer &&other) {
    if(this!=&other){
        clear();
        this->other;
    }
    return *this;
}

Agent * ContactTracer::clone() const{
    return (new ContactTracer());
}

void ContactTracer::clear() {
        delete (this);
        this->point;
}

void ContactTracer::act(Session &session) {}
