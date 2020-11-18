
#include "../include/Agent.h"
#include "../include/Tree.h"    //added
#include <iostream>
using namespace std;

Agent::Agent(): pAgent(nullptr){}


/*----------Virus------------*/

Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd), pV(this) {}

Virus::~Virus() {
    clear();
}

Virus::Virus(Virus const &other): Agent(), nodeInd(other.nodeInd) {
    clone();
}

Virus & Virus::operator=(Virus other) {
    this->other;
}

Virus & Virus::operator=(Virus &&other){
    if(this!=&other){
        clear();
        this->other;
    }
    return *this;
}

Virus::Virus(Virus &&other): nodeInd(other.nodeInd) {
    this->other;
    other.pAgent;
}

Agent * Virus::clone() const {
    return (new Virus(*this));
}

void Virus::clear() {
       delete(this);
       this->pAgent;
}

int Virus::getNodeInd() const {
    return nodeInd;
}

void Virus::act(Session &session) {
    Graph *g = session.getGraph();
    Tree *root=Tree::createTree(session,nodeInd);     //fix root
    Tree *bfsTree = g->BFS(session,root);
    g->infectNode(bfsTree->traceTree()); // prepare next insure
   // delete (g);
    //delete (root);
    //delete (bfsTree);
}

/*------Contact Tracer--------*/

ContactTracer::ContactTracer() : Agent(), pCT(this) {}

ContactTracer::ContactTracer(ContactTracer const &other): Agent() {
    clone();
}

ContactTracer::~ContactTracer() {
    clear();
}

ContactTracer & ContactTracer::operator=(ContactTracer other) {
    this->other;
}

ContactTracer::ContactTracer(ContactTracer &&other) {
    this->other;
    other.pAgent;
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
        this->pAgent;
}

void ContactTracer::act(Session &session) {
    Graph *g=session.getGraph();
    Tree *root=Tree::createTree(session,g->getQueue().back());     //fix root
    Tree *bfsTree = g->BFS(session,root);
    int num= bfsTree->traceTree();
    g->removeEdgeFromGraph(num);
    //delete (root);
    //delete (bfsTree);
}
