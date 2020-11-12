//
// Created by spl211 on 11/11/2020.
//
#include "Session.h"
#include <fstream>
#include <iostream>
using namespace std;


vector<Agent *> Session::getAgents() {
    return agents;
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


}


