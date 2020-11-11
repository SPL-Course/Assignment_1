//
// Created by spl211 on 11/11/2020.
//

#include "Session.h"

using namespace std;

vector<Agent *> Session::getAgents() {
    return agents;
}

Session::Session(const std::string& path): g(nullptr),treeType(),agents(){

}
