
// Created by spl211 on 6/11/2020.
#include "Graph.h"
#include <fstream>
using namespace std;
// Need to build Operation Function

Graph::Graph(std::vector <std::vector<int>> matrix) {

    for(vector<int> node : matrix) {

        vector<int> neighbors;
        int counter  = 0;

        for (int other : node){

            if (other == 1)
               neighbors.push_back(counter);
            counter = counter + 1;
        }

        edges.push_back(neighbors);
    }
}

int main(int argv, char** argc){

    vector<vector<int>> matrix = {{1},{0}};
    std::cout << matrix << endl;

    Graph(x);
    return 0;
}



}


}



