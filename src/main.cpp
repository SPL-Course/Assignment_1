#include <iostream>
#include "Session.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;


int main(int argc, char** argv){
    
    if(argc != 2){
        cout << "usage cTrace <config_path>" << endl;
        return 0;
    }
    //ifstream  i("config1.json");
    //json j;
    //j << i;
    Session sess(argv[1]);
    sess.simulate();
    return 0;
}
