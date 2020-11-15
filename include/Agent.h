
#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include <queue>
#include "Session.h"
using namespace std;

//class Session;   //next week prepare real session!(Allel's fault)

class Agent{                                     //add getType function for virus/contact tracer
public:
    Agent();                                     // Prepare next Agent - depends on our Session
    virtual void act(Session& session)=0;        // Prepare Next & act of V / CT

protected:
    Agent* point;
    char agentType;                              //check if its contact tracer or virus
    int agentIndex;                              // give the value for the first sick node
};

class ContactTracer: public Agent{
public:
    ContactTracer();                                           //constructor
    ~ContactTracer();                                         //destructor
    ContactTracer(ContactTracer const &other);               //copy constructor
    ContactTracer &operator=(ContactTracer other);          //copy assignment operator
    ContactTracer(ContactTracer &&other);                  //move constructor
    ContactTracer &operator=(ContactTracer &&other);      //move assignment operator

    void clear();                               //clean "this" so we can put "other" in it
    virtual Agent* clone() const;

    virtual void act(Session& session);                 // Node disconnect

protected:
    ContactTracer *c;
    ContactTracer *other;
};

class Virus: public Agent{
public:
    Virus (int nodeInd) ;                          //constructor
    virtual ~Virus();                             //destructor
    Virus(Virus const &other);                   //copy constructor
    Virus &operator=(Virus other);              //assignment operator
    Virus &operator=(Virus &&other);           //move assignment operator
    Virus(Virus &&other);                     //move constructor

    void clear();
    int getNodeInd() const;
    virtual Agent* clone() const;
    virtual void act(Session& session);          // Infect other Node

protected:
    Virus const *v;
    Virus *other;

private:
    const int nodeInd;                           // Where is the virus

};

#endif
