
#include "../include/Session.h"
#include <fstream>
#include <iostream>
#include "../include/Agent.h"
using namespace std;

void Session::setGraph(const Graph &graph) {
  g=graph;
}

void Session::addAgent(const Agent &agent) {
    Agent *toAdd;
    *toAdd = agent;
    agents.push_back(toAdd);
    delete toAdd;
}

void Session::enqueueInfected(int node) {
    g.getQueue().push(node);
}

int Session::dequeueInfected() {
    int node = g.getQueue().front();
    g.getQueue().pop();
    return node;
}

void Session::simulate() {
    for (int i = 0; i < agents.size(); ++i) {
        agents[i]->act(*this);
    }
}

vector<Agent *> Session::getAgents() {
    return agents;
}

Graph *Session::getGraph(){
    return &g;
}

Session::Session(const std::string& path): g(vector<vector<int>>()),treeType(), agents(vector<Agent*>()) {

    std::ifstream i(path);
    json j;
    i >> j;
    Graph g2(j["graph"]);
    g = g2;

    if (j["tree"] == "M")
        treeType = MaxRank;
    if (j["tree"] == "C")
        treeType = Cycle;
    if (j["tree"] == "R")
        treeType = Root;

    for (int i = 0; i < j["agents"].size(); i++) {
        if (j["agents"][i][0] == 'V')           //check what is in the input
            agents.push_back(new Virus(j["agents"][i][1]));     //check how to get the value of the pair in virus
        else
            agents.push_back(new ContactTracer());
    }
}


    TreeType Session::getTreeType() const {
        return treeType;
    }


