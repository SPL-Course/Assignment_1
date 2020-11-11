#ifndef AGENT_H_
#define AGENT_H_
//check
#include <vector>
#include <queue>
#include "Session.h"
using namespace std;

//class Session;   //next week prepare real session!(Allel's fault)

class Agent{                                                 //add getType function for virus/contact tracer
public:
    Agent();                                                // Prepare next Agent - depends on our Session
    virtual void act(Session& session)=0;                  // Prepare Next & act of V / CT
protected:
    char agentType;                                      //check if its contact tracer or virus
    int agentIndex;                                     // give the value for the first sick node
};

class ContactTracer: public Agent{
public:
    ContactTracer();                                    // new Contact
    
    virtual void act(Session& session);               // Node disconnect

};


class Virus: public Agent{
public:
    Virus(int nodeInd);                                     // new Virus (act from him)
    
    virtual void act(Session& session);                   // Infect other Node


private:
    const int nodeInd;                                  // Where is the virus
};

#endif
