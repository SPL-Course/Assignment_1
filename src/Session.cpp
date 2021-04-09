
#include "../include/Session.h"
#include <fstream>
#include <iostream>
#include "../include/Agent.h"
using namespace std;
using namespace nlohmann;

//========================Session===============================

/* Session Constructor */
Session::Session(const std::string& path):
   g(vector<vector<int>>()),treeType(), agents(),
    terminated(false), index(0), simulateCycle(0), done(), infectedNode(), viruses()
{
    std::ifstream i(path);
    json j;
    i >> j;

    g = Graph(j["graph"]);

    if (j["tree"].front() == "M")
        treeType = MaxRank;
    if (j["tree"].front() == "C")
        treeType = Cycle;
    if (j["tree"].front() == "R")
        treeType = Root;

    infectedNode = queue<int>();
    viruses = vector<bool>(g.getVecs()->size(), false);

    for(pair<string, int> pair : j["agents"]) {
        if (pair.second == -1)
            agents.push_back(new ContactTracer());
        else{
            agents.push_back(new Virus(pair.second));
            viruses.at(pair.second) = true;
        }
    }
    done = vector<bool>(agents.size(), false);
}

/*--------Session: Rule Of 5-----------*/

/* Session Destructor */
Session::~Session()
{
    clear();
}

void Session::clear()
{  /* clears Session resources */

    unsigned int size = agents.size();
    for (unsigned int i = 0; i < size; ++i) {
        if (agents.at(i) != nullptr) {
            delete (agents.at(i));
            agents.at(i) = nullptr;
        }
    }
}

/* Session Copy Constructor */
Session::Session(const Session &other):
   g(vector<vector<int>>()), treeType(other.treeType), agents(),
    terminated(other.terminated), index(other.index), simulateCycle(other.simulateCycle),
      done(other.done), infectedNode(other.infectedNode), viruses(other.viruses)
{
    g = Graph(other.g);
    unsigned count= other.agents.size();
    for (unsigned int i = 0; i < count ; ++i) {
        Agent *newAgent = other.agents[i]->clone();
        agents.push_back(newAgent);
    }
}

/* Session Copy Assignment Operator */
Session & Session::operator=(const Session &other)
{
    if(this!=&other) {
        clear();
        treeType = other.treeType;
        g = Graph(other.g);
        terminated = other.terminated;
        done = other.done;
        infectedNode = other.infectedNode;
        index = other.index;
    }
    unsigned int size=other.agents.size();
    for (unsigned int i = 0; i <size ; ++i) {
        Agent *newAgent = other.agents[i]->clone();
        agents.push_back(newAgent);
    }
    return *this;
}

/* Session Move Constructor */
Session::Session(Session &&other):
   g(vector<vector<int>>()), treeType(other.treeType), agents(move(other.agents)),
     terminated(other.terminated), index(other.index), simulateCycle(other.simulateCycle),
       done(other.done), infectedNode(other.infectedNode), viruses(other.viruses)
{
    g = other.g;
    steal(other);
}

/* Session Move Assignment Operator */
Session & Session::operator=(Session &&other)
{
    if(this!= &other){
        clear();
        treeType=other.treeType;
        g=other.g;
        terminated=other.terminated;
        done=other.done;
        infectedNode=other.infectedNode;
        index=other.index;
        unsigned int count=agents.size();
        for (unsigned int i = 0; i <count ; ++i) {
            Agent *newAgent = other.agents[i];
            agents.push_back(newAgent);
        }
        steal(other);
    }
    return *this;
}

void Session::steal(Session &other)
{  /* other lose resources */

    unsigned int size = agents.size();
    for (unsigned int i = 0; i < size; ++i) {
        agents.at(i) = nullptr;
    }
}

/*--------Session: Given Functions-----------*/

void Session::simulate() {

    while (!terminated) {

        int count = agents.size();
        for (int i = 0; i < count; ++i) {
            index = i;
            (agents.at(i))->act(*this);
        }

        bool check = true;
        count = done.size();
        for (int k = 0; (k < count) & (check); ++k) {
            if (!done.at(k))
                check = false;
        }

        if (check) {
            int size = g.getVecs()->size();
            for (int a = 0; (a < size) & (check); ++a) {
                if(g.getVecs()->at(a) == 1)
                    check = false;
            }
        }
        terminated = check;
        simulateCycle++;
    }
    makeOutput();
}

void Session::addAgent(const Agent &agent)
{
    Agent *toAdd = agent.clone();
    agents.push_back(toAdd);
}

void Session::enqueueInfected(int node)
{
    infectedNode.push(node);
}

int Session::dequeueInfected()
{
    int output = infectedNode.front();
    infectedNode.pop();
    return output;
}

void Session::setGraph(const Graph &graph)
{
    g = Graph(graph);
}

/*--------Help Functions--------*/

int Session::toInfect(int father)
{  /* finding next virus-free neighbor */

    int toInfect = -1;
    unsigned int fatherEdgesSize = g.getEdges().at(father).size();
    for (unsigned int i = 0; (i < fatherEdgesSize) & (toInfect == -1); ++i) {
        int neighbor = g.getEdges().at(father).at(i);
        int status = getGraph()->getVecs()->at(neighbor);
        if (status == 0)
        {
            unsigned int virusesSize = viruses.size();
            for(unsigned int j = 0; (j < virusesSize) & (toInfect == -1); j++)
                if(!viruses.at(neighbor))
                    toInfect = neighbor;
        }
    }
    return toInfect;
}

/*--------Output Functions--------*/

void Session::makeOutput()
{
    json k;
    vector<int> outputInfected = this->makeInfected();
    vector<vector<int>> outputGraph = this->makeGraph();
    k["graph"] = outputGraph;
    k["infected"] = outputInfected;
    ofstream  u("output.json");
    u << k;
}

std::vector<int> Session::makeInfected()
{
    vector<int>output;
    unsigned int count = g.getVecs()->size();
    for (unsigned int i = 0; i < count ; ++i) {
        if(g.getVecs()->at(i) == 2)
            output.push_back(i);
    }
    return output;
}

std::vector<std::vector<int>> Session::makeGraph()
{
    unsigned int n = g.getEdges().size();
    vector<vector<int>> output(n,vector<int>(n,0));
    for(unsigned int i = 0 ; i < n ; ++i){
        unsigned int in = g.getEdges().at(i).size();
        for(unsigned int j = 0 ; j < in ; ++j) {
            int value = g.getEdges().at(i).at(j);
            output.at(i).at(value) = 1;
            output.at(value).at(i) = 1;
        }
    }
    return output;
}

/*----------- Getters -----------*/

Graph *Session::getGraph()
{
    return &g;
}

TreeType Session::getTreeType() const
{
    return treeType;
}

vector<Agent *> *Session::getAgents()
{
    return &agents;
}

int & Session::getIndex()
{
    return index;
}

int& Session::getSimulateCycle()
{
    return simulateCycle;
}

std::vector<bool> * Session::getDone()
{
    return &done;
}

queue<int> * Session::getInfected()
{
    return &infectedNode;
}

std::vector<bool> * Session::getViruses()
{
    return &viruses;
}











