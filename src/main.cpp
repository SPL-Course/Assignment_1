#include <iostream>
#include "Session.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;


int main(int argc, char** argv) {

//    if (argc != 2) {
//        cout << "usage cTrace <config_path>" << endl;
//        return 0;
//    }

    //ifstream  i("config1.json");
    //json j;
    //j << i;
    //Session sess(argv[1]);
    //sess.simulate();

    vector<vector<int>> matrix = {{0, 1, 0, 0, 1, 0, 0, 0, 0},
                                  {1, 0, 1, 1, 0, 1, 1, 0, 0},
                                  {0, 1, 0, 1, 0, 1, 0, 0, 0},
                                  {0, 1, 1, 0, 0, 1, 0, 0, 0},
                                  {1, 0, 0, 0, 0, 1, 0, 0, 0},
                                  {0, 1, 1, 1, 1, 0, 0, 1, 0},
                                  {0, 1, 0, 0, 0, 0, 0, 1, 1},
                                  {0, 0, 0, 0, 0, 1, 1, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 1, 0, 0}};

    Graph g(matrix);


    for (vector<int>::size_type i = 0; i < g.getEdges().size(); ++i) {
        for (vector<int>::size_type j = 0; j < g.getEdges()[i].size(); ++j) {
            cout << g.getEdges()[i][j];
        }
        cout << "" << endl;
    }
    return 0;
}