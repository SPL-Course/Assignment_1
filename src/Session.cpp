
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
    g = Graph(graph);
}

std::vector<bool> * Session::getDone()
{
    return &done;
}

TreeType Session::getTreeType() const
{
    return treeType;
}

queue<int> * Session::getInfected()
{
    return &infectedNode;
}

Session::~Session()
{
    clear();
}

void Session::steal(Session &other)
{
    int size=agents.size();
    for (unsigned int i = 0; i < size; ++i) {
        agents.at(i) = nullptr;
    }
}

Session & Session::operator=(const Session &other) {
    if(this!=&other) {
        clear();
        treeType = other.treeType;
        g = Graph(other.g);
        terminated = other.terminated;
        done = other.done;
        infectedNode = other.infectedNode;
        counter = other.counter;
    }
    int size=other.agents.size();
    for (unsigned int i = 0; i <size ; ++i) {
        Agent *newAgent = other.agents[i]->clone();
        agents.push_back(newAgent);
    }
    return *this;
}

Session & Session::operator=(Session &&other)
{
    if(this!= &other){
        clear();
        treeType=other.treeType;
        g=other.g;
        terminated=other.terminated;
        done=other.done;
        infectedNode=other.infectedNode;
        counter=other.counter;
        int count=agents.size();
        for (unsigned int i = 0; i <count ; ++i) {
            Agent *newAgent = other.agents[i]->clone();
            agents.push_back(newAgent);
        }
        steal(other);
    }
    return *this;
}

void Session::clear()
{
    int size = agents.size();
    for (unsigned int i = 0; i < size; ++i) {
        if (agents.at(i) != nullptr) {
            delete (agents.at(i));
            agents.at(i) = nullptr;
        }
    }
}

std::vector<int> Session::outputInfected()
{
    vector<int>output;
    int count=g.vecs.size();
    for (unsigned int i = 0; i <count ; ++i) {
        if(g.vecs.at(i)==2)
            output.push_back(i);
    }
    return output;
}

std::vector<std::vector<int>> Session::outputGraph()
{
    int n = g.getEdges().size();
    vector<vector<int>> output(n,vector<int>(n,0));
    for(unsigned int i = 0 ; i < n ; ++i){
        int in = g.getEdges().at(i).size();
        for(unsigned int j = 0 ; j < in ; ++j) {
            int value = g.getEdges().at(i).at(j);
            output.at(i).at(value) = 1;
            output.at(value).at(i) = 1;
        }
    }
    return output;
}

vector<Agent *> Session::getAgents()
{
    return agents;
}

Session::Session(const Session &other):
        g(vector<vector<int>>()), treeType(other.treeType), agents(), terminated(other.terminated),done(other.done),infectedNode(other.infectedNode),counter(other.counter)
{
    g=Graph(other.g);
    int count= other.agents.size();
    for (unsigned int i = 0; i < count ; ++i) {
        Agent *newAgent = other.agents[i]->clone();
        agents.push_back(newAgent);
    }
}

Session::Session(Session &&other): g(vector<vector<int>>()) ,treeType(other.treeType), agents(move(other.agents)), terminated(other.terminated),done(other.done),infectedNode(other.infectedNode),counter(other.counter)
{
    g=other.g;
    steal(other);
}


