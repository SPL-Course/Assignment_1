
#include "../include/Session.h"
#include <fstream>
#include <iostream>
#include "../include/Agent.h"
using namespace std;


vector<Agent *> Session::getAgents() {
    return agents;
}

Graph* Session::getGraph() {
    return &g;
}

Session::Session(const std::string& path): g(vector<vector<int>>()),treeType(), agents(vector<Agent*>()){

    std::ifstream i("config1.json");
    json j;
    i >> j;

    vector<vector<int>> matrix2 = j["graphs"];
    Graph g2(matrix2);
    g.operator=(g2);

    if (j["tree"] == "M")
        treeType = MaxRank;
    if (j["tree"] == "C")
        treeType = Cycle;
    if (j["tree"] == "R")
        treeType = Root;

//
//    for(int i=0;i<j["agents"].size();i++){
//        if(j["agents"][i]==?)           //check what is in the input
//            agents.push_back(new Virus(?));     //check how to get the value of the pair in virus
//        else
//            agents.push_back(new ContactTracer());
//    }

}



TreeType Session::getTreeType() const {
    return treeType;
}


