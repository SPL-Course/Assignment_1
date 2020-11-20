
#include "../include/Session.h"
#include <fstream>
#include <iostream>
#include "../include/Agent.h"
using namespace std;
using namespace nlohmann;

Session::Session(const std::string& path):
     g(vector<vector<int>>()),treeType(), agents(vector<Agent*>()), terminated(false)
{
    std::ifstream i(path);
    json j;
    i >> j;
    Graph g(j["graph"]);

    if (j["tree"] == "M")
        treeType = MaxRank;
    if (j["tree"] == "C")
        treeType = Cycle;
    if (j["tree"] == "R")
        treeType = Root;

    for (int i = 0; i < j["agents"].size(); i++) {

        Agent *currAgent;

        if (j["agents"][i][0] == "V") {
            Virus v(j["agents"][i][1]);
            currAgent = v.clone();
        }

        else {
            ContactTracer c;
            currAgent = c.clone();
        }

        agents.push_back(currAgent);
    }
}


Session::Session(const Session &other):
   g(vector<vector<int>>()), treeType(other.treeType), agents(), terminated(other.terminated)
{
    for (int i = 0; i < other.agents.size(); ++i) {
        Agent *newAgent = other.agents[i]->clone();
        agents.push_back(newAgent);
    } //g=other.g;
}

TreeType Session::getTreeType() const
{
        return treeType;
}

void Session::setGraph(const Graph &graph) { /*g=graph;*/}

//void Session::addAgent(const Agent &agent)
//{
//    Agent *toAdd = agent.clone();
//    agents.push_back(toAdd);
//}

void Session::enqueueInfected(int node)
{
//    Virus add(node);
//    g.getQueue().push(add);
}

int Session::dequeueInfected()
{
//    int node = g.getQueue().front().nodeInd;
//    g.getQueue().pop();
//    return node;
}

void Session::simulate()
{
    while(!terminated) { // endless loop need to set true at Graph
        for (int i = 0; i < agents.size(); ++i){}
            //agents[i]->act(*this);
    }
}

//vector<Agent *> Session::getAgents()
//{
//    return agents;
//}

Graph *Session::getGraph()
{
    return &g;
}


