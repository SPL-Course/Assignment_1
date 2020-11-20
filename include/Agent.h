
#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
/*----Added-------*/
#include <queue>
#include "Session.h"
//class Session;
using namespace std;
/*----------------*/

class Agent{
public:
    Agent();
    virtual void act(Session& session)=0;
    virtual ~Agent();                  //added
    virtual Agent* clone() const = 0;  //added
//protected: Agent* pAgent;
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual void act(Session& session);
    virtual Agent* clone() const;  //added

//    ~ContactTracer();                                     //destructor
//    ContactTracer(ContactTracer const &other);            //copy constructor
//    ContactTracer &operator=(ContactTracer other);        //copy assignment operator
//    ContactTracer(ContactTracer &&other);                 //move constructor
//    ContactTracer &operator=(ContactTracer &&other);      //move assignment operator
//    void clear();                                         //so we can put "other" into
//protected: ContactTracer *pCT; ContactTracer *other;      //checks all other's
};

class Virus: public Agent{
public:
    Virus (int nodeInd) ;
    virtual void act(Session& session);
    virtual Agent* clone() const;   //added
    int getNodeInd() const;         //added

    //virtual ~Virus();                         //destructor
    //Virus(Virus const &other);                //copy constructor
    //Virus &operator=(Virus other);            //assignment operator
    //Virus &operator=(Virus &&other);          //move assignment operator
    //Virus(Virus &&other);                     //move constructor
    //void clear();
//protected: Virus const *pV; Virus *other;
//private:
    const int nodeInd; // @ Changed to public
};

#endif
