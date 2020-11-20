
#ifndef SESSION_H_
#define SESSION_H_

#include "Graph.h"
#include <vector>
#include <string>
#include "json.hpp"
using namespace std;

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    Session(const Session& other);
    
    void simulate();
    //void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    int dequeueInfected();
    
    TreeType getTreeType() const;
//    vector<Agent*> getAgents();
    Graph *getGraph();

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;

protected:
    bool terminated;
};

#endif
