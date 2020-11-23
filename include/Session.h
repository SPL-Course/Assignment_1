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
    Session(const std::string& path);
    Session(const Session& other);
    virtual ~Session();
    Session(Session&& other);
    Session& operator=(const Session &other);
    void steal(Session &other);
    Session& operator=(Session &&other);
    void clear();

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    int dequeueInfected();
    
    TreeType getTreeType() const;
    std::vector<Agent*> getAgents();
    Graph *getGraph();
    std::queue<int> *getInfected(); //just for example
    std::vector<bool> *getDone();
    int toInfect(int node);
    std::vector<int> outputInfected();
    std::vector<std::vector<int>> outputGraph();
    void makeOutput();
    std::vector<bool>done;
    int index;

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;

protected:
    bool terminated;
    std::queue<int>infectedNode;
};

#endif
