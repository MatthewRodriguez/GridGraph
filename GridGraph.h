//
//  GridGraph.h
//  GridGraph
//
//  Created by Matt Rodriguez on 4/6/20.
//  Copyright © 2020 Matthew Rodriguez. All rights reserved.
//

#ifndef GridGraph_h
#define GridGraph_h
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <unordered_set>
#include <unordered_map>
#include <climits>
using namespace std;

struct Node{
    int x;
    int y;
    int info;
    bool visit;
    int heuristic;
    Node *parent = nullptr;
    vector<Node*> list;
    Node (int x_val, int y_val, int i, bool v = false) : x(x_val), y(y_val), info(i), visit(v) {}
};

class GridGraph{
    vector<Node*> nodes;
public:
    GridGraph();
    void addGridNode(int x, int y, int val);
    void addUndirectedEdge(Node *first, Node *second);
    void removeUndirectedGraph(Node *first, Node *second);
    unordered_set<Node*> getAllNodes();
    void createRandomGridGraph(int n);
    Node* findMinDistance(unordered_map<Node*, int> umap);
    void updateDistance(Node *first, Node *second, unordered_map<Node*, int> &umap);
    void setHeuristic(Node *first, Node *second);
    vector<Node*> astar(Node *sourceNode, Node *destNode);
    vector<Node*> a();
    void printNodes();
    void printU();
    
};
#endif /* GridGraph_h */
