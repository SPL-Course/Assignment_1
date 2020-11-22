
/*---Start---*/
#include "../include/Session.h"
#include "../include/Agent.h" // Added 15:31 13/11/20
#include "../include/Tree.h" // Added 15:31 13/11/20
#include <iostream>
#include <fstream>
using namespace std;
using namespace nlohmann;

int main(int argc, char** argv) {

/*------------Original Main-------*/

//    if (argc != 2) {
//        cout << "usage cTrace <config_path>" << endl;
//        return 0;
//    }
//
//    Session sess(argv[1]);
//    sess.simulate();
//    return 0;
//}

/*------------Free Checks Main-------*/
    ifstream  i("../include/config1.json");
    json j;
    i >> j;

    //cout << j<< endl;


    Session sess("../include/config1.json"); // To Build Again
    //sess.simulate();
    cout << argv[0];
    cout << argc;

    Graph *g = sess.getGraph();
//    Tree* a = g->BFS(sess,0);
//    Tree* a = Tree::createTree(sess, 1);
//    Tree* b = Tree::createTree(sess, 2);
//    Tree* c = Tree::createTree(sess, 3);
//    Tree* d = Tree::createTree(sess, 4);
//    Tree* e = Tree::createTree(sess, 5);
//    b->addChild(*c);
//    b->addChildShallow(c);
//    c->depth=5;
//    c->addChildShallow(e);
//    a->addChild(*d);
//    a->operator=(*b);
//    *a = *b;
//    c->addChild(*e);



//    Agent* a= new Virus(2);
//    Agent *b = a->clone();


    //Tree *t = Tree::createTree(sess, 0);
//    g->BFS(sess, 0);


//    sess.simulate();
//
//  Agent *a = new Virus(0)

    //cout<<j["agents"];


//    Agent *a;
//
//    cout << j["agents"][0][0] << endl;
//    if(j["agents"][0][0] == "V"){
//        Virus b(j["agents"][0][1]);
//        a =  b.clone();
//    }
//    else{
//        ContactTracer b;
//        a = b.clone();
//    }


//    Virus a(2);
//    //cout << a.getNodeInd() << endl;
//    cout << a.getNodeInd() << endl;
//    cout << &a << endl;
//
//    Agent *b = a.clone();

    //Agent *b2 = new Virus(2);

    //cout << b.getNodeInd();
    //cout << &b << endl;
    //cout << b << "?" << endl;


    //a->act(sess);
//    sess.simulate();

    //cout << argc;
    //cout << argv[1];

//    vector<vector<int>> matrix = {{0, 1, 0, 0, 1, 0, 0, 0, 0},
//                                  {1, 0, 1, 1, 0, 1, 1, 0, 0},
//                                  {0, 1, 0, 1, 0, 1, 0, 0, 0},
//                                  {0, 1, 1, 0, 0, 1, 0, 0, 0},
//                                  {1, 0, 0, 0, 0, 1, 0, 0, 0},
//                                  {0, 1, 1, 1, 1, 0, 0, 1, 0},
//                                  {0, 1, 0, 0, 0, 0, 0, 1, 1},
//                                  {0, 0, 0, 0, 0, 1, 1, 0, 0},
//                                  {0, 0, 0, 0, 0, 0, 1, 0, 0}};

    //Graph g(matrix);

    //Tree *t = Tree::createTree(sess,0);
    //sess.getGraph()->BFS(sess,t);


//    Graph *g5 = sess.getGraph();
//    t=g.BFS(sess,t);

//    for (vector<int>::size_type i = 0; i < g.getEdges().size(); ++i) {
//        for (vector<int>::size_type j = 0; j < g.getEdges()[i].size(); ++j) {
//            cout << g.getEdges()[i][j];
//        }
//    }
//        cout << "" << endl;
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

//    Graph g2(g);
//    cout<<endl;

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

    //sess.simulate();

    //// == output_Try == ////
//    json k;
//    vector<int> infected;
//    while(!sess.getGraph()->getQueue().empty()){
//        infected.push_back(sess.getGraph()->getQueue().front());
//        sess.getGraph()->getQueue().pop();
//    }
//    vector<int> k["infected"](sess.getInfected()->size());
//    k["infected"] = sess.getInfected();
//    int n = sess.getGraph()->getEdges().size();
//    vector<vector<int>> graph(n);
//    for (int k = 0; k < n ; ++k)
//        for (int k = 0; k < sess.getGraph()->getEdges()[k].size(); ++k) {}
//    k["graph"] = graph;
//    ofstream  u("output.json");
//    k >> u;

    return 0;
}
/*----------------------------------*/