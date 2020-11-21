
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
//    Session(const Session& other);                  //copy constructor
//    virtual ~Session();                            //destructor
//    Session(Session&& other);               //move constructor
//    Session& operator=(const Session &other);    //move Assignment operator
//    Session& operator=(const Session &&other);  //copy Assignment operator
//    void clear();

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    int dequeueInfected();
    
    TreeType getTreeType() const;
    //std::vector<Agent*> getAgents();
    Graph *getGraph();
    //std::queue<int> *getInfected(); //just for example
    std::vector<bool> *getDone();
    int counter;
    std::vector<bool>done;

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;

protected:
    bool terminated;
    std::queue<int>infectedNode;

};

#endif
