#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    
    void simulate();                     // !~Most general function~!
    void addAgent(const Agent& agent);   // Each Infec' get-in
    void setGraph(const Graph& graph);   // Change Edges
    
    void enqueueInfected(int);           // Need to build Q (Standard C++)
    int dequeueInfected();               // Need to build Q (Standard C++)
    
    TreeType getTreeType() const;        // from input (json-?)
    
private:
    Graph g;                             // from string & can change status
    TreeType treeType;
    std::vector<Agent*> agents;
};

#endif
