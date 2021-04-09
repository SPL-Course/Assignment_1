#ifndef SESSION_H_
#define SESSION_H_

#include "Graph.h"
#include <vector>
#include <string>
#include "json.hpp"
class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    /*--Constructor--*/
    Session(const std::string& path);

    /*--Rule Of 5--*/
    virtual ~Session();                          // destructor
    Session(const Session& other);               // copy constructor
    Session& operator=(const Session &other);    // copy assignment operator
    Session(Session&& other);                    // move constructor
    Session& operator=(Session &&other);         // move assignment operator

    void clear();
    void steal(Session &other);

    /*--Given Functions--*/
    void simulate();
    void addAgent(const Agent& agent);
    void enqueueInfected(int);
    int dequeueInfected();
    void setGraph(const Graph& graph);

    /*--Help Functions--*/
    int toInfect(int node);                      // next virus-free neighbor

    /*--Output Functions--*/
    void makeOutput();                           // using below makers for final output
    std::vector<int> makeInfected();
    std::vector<std::vector<int>> makeGraph();

    /*-----Getters-------*/
    Graph *getGraph();
    TreeType getTreeType() const;
    std::vector<Agent*> *getAgents();
    int& getIndex();
    int& getSimulateCycle();
    std::vector<bool> *getDone();
    std::queue<int> *getInfected();
    std::vector<bool> *getViruses();

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;

    bool terminated;                           // Simulate stop condition
    int index;                                 // agent's place in agents and done
    int simulateCycle;                         // helps CycleTree traceTree
    std::vector<bool>done;                     // agent acts unless done
    std::queue<int>infectedNode;               // helps Contact Tracer act
    std::vector<bool>viruses;                  // true for non Virus-free nodes
};

#endif
