//
//  main.cpp
//  GridGraph
//
//  Created by Matt Rodriguez on 4/6/20.
//  Copyright © 2020 Matthew Rodriguez. All rights reserved.
//

#include  "GridGraph.h"

int main(int argc, const char * argv[]) {
    vector<Node*> v;
    Node* n;
    GridGraph g;
    g.createRandomGridGraph(10);
    cout << "GridGraph: ";
    g.printNodes();
    g.printU();
    v = g.a();
    cout << "Astar: ";
    for (int i = 0; i < v.size(); i++){
        n = v.back();
        v.pop_back();
        cout << n->info << " ";
    }
    cout << endl;
    return 0;
}
