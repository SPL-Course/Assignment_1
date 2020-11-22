
#include "../include/Session.h"
#include <fstream>
#include <iostream>
#include "../include/Agent.h"
using namespace std;
using namespace nlohmann;

Session::Session(const std::string& path):
     g(vector<vector<int>>()),treeType(),
     agents(), terminated(false),done(),infectedNode(),counter(0)
{
    std::ifstream i(path);
    json j;
    i >> j;
    g = Graph(j["graph"]);
    if (j["tree"] == "M")
        treeType = MaxRank;
    if (j["tree"] == "C")
        treeType = Cycle;
    if (j["tree"] == "R")
        treeType = Root;

    infectedNode = queue<int>();

    for(pair<string, int> pair : j["agents"]){
        if (pair.second == -1)
            agents.push_back(new ContactTracer());
        else
            agents.push_back(new Virus(pair.second));
    }
    done = vector<bool>(agents.size(), false);
}

void Session::simulate() {
    while (!terminated) {
        int count = agents.size();
        for (int i = 0; i < count; ++i) {
            agents.at(i)->act(*this);
            counter++;
        }
        bool check = true;
        count = done.size();
        for (int k = 0; k < count && check; ++k) {
            if (!done.at(k))
                check = false;
        }
        if (check)
            terminated = true;
    }
}

void Session::addAgent(const Agent &agent)
{
    Agent *toAdd=agent.clone();
    agents.push_back(toAdd);
}

void Session::enqueueInfected(int node)
{
    infectedNode.push(node);

//    Virus add(node);
//    g.getQueue().push(add);
}

int Session::dequeueInfected()
{
    int output=infectedNode.front();
    infectedNode.pop();
    return output;
//    int node = g.getQueue().front().nodeInd;
//    g.getQueue().pop();
//    return node;
}

Graph *Session::getGraph()
{
    return &g;
}

void Session::setGraph(const Graph &graph)
{
    //g = graph;
}

std::vector<bool> * Session::getDone()
{
    return &done;
}

TreeType Session::getTreeType() const
{
    return treeType;
}


//Session::Session(const Session &other):
//   g(vector<vector<int>>()), treeType(other.treeType), agents(), terminated(other.terminated),done(other.done),infectedNode(other.infectedNode),counter(other.counter)
//{
//    int count= other.agents.size();
//    for (int i = 0; i <count ; ++i) {
//        Agent *newAgent = other.agents[i]->clone();
//        agents.push_back(newAgent);
//    }
//    //g=other.g;
//}

//Session::Session(Session &&other): g(vector<vector<int>>()) ,treeType(other.treeType), agents(other.agents), terminated(other.terminated),done(other.done),infectedNode(other.infectedNode),counter(other.counter)
//{
//    other.treeType = Root;
//    other.terminated= 0;
//    other.done = vector<bool>();
//    other.infectedNode = queue<int>();
//    other.counter=0;
//}

//Session & Session::operator=(const Session &other) {
//    treeType=other.treeType;
//    g=other.g;
//    agents=other.agents;
//    terminated=other.terminated;
//    done=other.done;
//    infectedNode=other.infectedNode;
//    counter=other.counter;
//}

//Session & Session::operator=(const Session &&other) {
//    if(this!= &other){
//        clear();
//        treeType=other.treeType;
//        g=other.g;
//        agents=other.agents;
//        terminated=other.terminated;
//        done=other.done;
//        infectedNode=other.infectedNode;
//        counter=other.counter;
//
//    }
//}
//void Session::clear()
//{
//    delete (g);
//    treeType=Root;
//    for(int i=0;i<agents.size();i++){
//        delete(agents[i]);
//    }
//    delete (terminated);
//
//}


//    while(!terminated) { // endless loop need to set true at Graph
//        for (int i = 0; i < agents.size(); ++i){}
//            //agents[i]->act(*this);
//    }

//vector<Agent *> Session::getAgents()
//{
//    return agents;
//}



//std::queue<int> * Session::getInfected()
//{
//    return &infectedNode;
//}



