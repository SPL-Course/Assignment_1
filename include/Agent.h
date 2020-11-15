
#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include <queue>
#include "Session.h"                            //check if ok
using namespace std;

class Agent{
public:
    Agent();
    virtual void act(Session& session)=0;

protected:
    Agent* pAgent;
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
    ContactTracer *pCT;
    ContactTracer *other;                           //check all other's
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

    virtual void act(Session& session);          // Infect node

protected:
    Virus const *pV;
    Virus *other;

private:
    const int nodeInd;

};

#endif
