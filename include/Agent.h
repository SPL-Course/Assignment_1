#ifndef AGENT_H_
#define AGENT_H_
//check
#include <vector>

class Session;

class Agent{

public:
    
    Agent();   // Prepare next Agent - depends on our Session
    virtual void act(Session& session)=0;      // Prepare Next & act of V / CT
};

class ContactTracer: public Agent{
public:
    ContactTracer();      // new Contact
    
    virtual void act(Session& session);                   // Node disconnect
};


class Virus: public Agent{
public:
    Virus(int nodeInd); // new Virus (act from him)
    
    virtual void act(Session& session);                   // Infect other Node

private:
    const int nodeInd;                    // Where is the virus
};

#endif
