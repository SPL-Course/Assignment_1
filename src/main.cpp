
#include "../include/Session.h"
#include "../include/Agent.h" // Added 15:31 13/11/20
#include "../include/Tree.h" // Added 15:31 13/11/20
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "usage cTrace <config_path>" << endl;
//        return 0;
    }

    ifstream  i("../include/config4.json");
    json j;
    i >> j;


 //   cout << j<< endl;
    Session sess("../include/config4.json");

    Agent *a = new Virus(0);

    //a->act(sess);
//    sess.simulate();

    //cout << argc;
    //cout << argv[1];

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

    Tree *t = Tree::createTree(sess,0);
    sess.getGraph()->BFS(sess,t);
//    Graph *g5 = sess.getGraph();
    t=g.BFS(sess,t);


//    for (vector<int>::size_type i = 0; i < g.getEdges().size(); ++i) {
//        for (vector<int>::size_type j = 0; j < g.getEdges()[i].size(); ++j) {
//            cout << g.getEdges()[i][j];
//        }
//    }
////        cout << "" << endl;
//
//       g.infectNode(0);
//       cout << "" << endl;
//       g.infectNode(1);
//       cout << "" << endl;
//       g.infectNode(4);
//       cout << "" << endl;
//       g.infectNode(5);
//       cout << "" << endl;
//
//       while(!g.getQueue().empty()) {
//
//           cout << " " << g.getQueue().front() << " ";
//           g.getQueue().pop();
//           cout << "" << endl;
//       }

//       for (vector<int>::size_type j = 0; j < g.getVertex().size(); ++j){
//            //cout << g.getVertex()[j] << endl;
//            cout << g.isInfected(j) << " ";
//       }

    Graph g2(g);
   // cout<<endl;

//        for (vector<int>::size_type i = 0; i < g2.getEdges().size(); ++i) {
//            for (vector<int>::size_type j = 0; j < g2.getEdges()[i].size(); ++j) {
//                cout << g2.getEdges()[i][j];
//            }
//        }

//    for (vector<int>::size_type j = 0; j < g2.getVertex().size(); ++j){
//
//        //cout << g.getVertex()[j] << endl;
//        cout << g2.isInfected(j) << " ";
//    }
//    cout << "" << endl;

//    while(!g2.getQueue().empty()) {
//
//        cout << " " << g2.getQueue().front() << " ";
//        g2.getQueue().pop();
//        cout << "" << endl;
//    }

    //Session session();
    return 0;
}