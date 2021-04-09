#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include <queue>
#include "Session.h"
using namespace std;

class Agent{
public:
    /*--Constructor--*/
    Agent();

    virtual ~Agent();                                 // default destructor
    virtual Agent* clone() const = 0;                 // deep-copy

    /*--Given Functions--*/
    virtual void act(Session& session)=0;
};

class ContactTracer: public Agent{
public:
    /*--Constructor--*/
    ContactTracer();

    virtual ~ContactTracer() = default;               // uses Agent destructor
    virtual Agent* clone() const;                     // deep-copy

    /*--Given Functions--*/
    virtual void act(Session& session);
};

class Virus: public Agent{
public:
    /*--Constructor--*/
    Virus (int nodeInd);

    virtual ~Virus() = default;                       // uses Agent destructor
    virtual Agent* clone() const;                     // deep-copy

    /*--Given Functions--*/
    virtual void act(Session& session);

    /*--Help Functions--*/
    void fullyInfect(Session& session, int toInfect); // updates relevant fields

    /*-----Getters------*/
    int getNodeInd() const;

private:
    const int nodeInd;
};

#endif
