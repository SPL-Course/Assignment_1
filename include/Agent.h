#ifndef AGENT_H_
#define AGENT_H_

#include <vector>

class Agent{

/* Note in site - 2 options */

public:
    
    Agent(Session& session);   // Prepare next Agent - depends on our Session    
    virtual void act()=0;      // Prepare Next & act of V / CT

private:
    Session &session;          // Reference to our Session
}

class ContactTracer: public Agent{
public:
    ContactTracer(Session& session);      // new Contact 
    
    virtual void act();                   // Node disconnect 
}


class Virus: public Agent{
public:
    Virus(int nodeInd, Session& session); // new Virus (act from him)
    
    virtual void act();                   // Infect other Node 

private:
    const int nodeInd;                    // Where is the virus
}

#endif
