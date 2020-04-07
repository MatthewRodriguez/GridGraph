//
//  GridGraph.cpp
//  GridGraph
//
//  Created by Matt Rodriguez on 4/6/20.
//  Copyright © 2020 Matthew Rodriguez. All rights reserved.
//

#include "GridGraph.h"

GridGraph::GridGraph(){
    nodes.clear();
}

void GridGraph::addGridNode(int x, int y, int val){
    Node *n = new Node(x, y, val);
    if (nodes.empty())
        nodes.push_back(n);
    else{
        for (int i = 0; i < nodes.size(); i++)
            if (nodes[i]->info == val)
                return;
        nodes.push_back(n);
    }
}

void GridGraph::addUndirectedEdge(Node *first, Node *second){
    if (first->x == second->x || first->y == second->y){
        for (int i = 0; i < first->list.size(); i++)
            if (first->list[i]->info == second->info)
                return;
        for (int i = 0; i < second->list.size(); i++)
            if (second->list[i]->info == first->info)
              return;
        first->list.push_back(second);
        second->list.push_back(first);
    }
}

void GridGraph::removeUndirectedGraph(Node *first, Node *second){
    if (first->list.empty() && second->list.empty())
        return;
    for (int i = 0; i < first->list.size(); i++){
        if(first->list[i]->info == second->info)
            first->list.erase(first->list.begin()+i);
    }
    for (int i = 0; i < second->list.size(); i++){
        if(second->list[i]->info == first->info)
            second->list.erase(second->list.begin()+i);
    }
}

unordered_set<Node*> GridGraph::getAllNodes(){
    unordered_set<Node*> s;
    for (int i = 0; i < nodes.size(); i++)
        s.insert(nodes[i]);
    return s;
}

void GridGraph::createRandomGridGraph(int n){
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, (n*n));

    int same, a, b;
    srand((unsigned) time(0));
    for (int i = 0; i < n; i++){
        same = i;
        for (int j = 0; j < n; j++){
            addGridNode(j, same, dist(mt));
        }
    }
    for (int i = 0; i < nodes.size(); i++){
        if(nodes.size() > 1){
            a = rand() % nodes.size();
            b = rand() % nodes.size();
            addUndirectedEdge(nodes[a], nodes[b]);
        }
    }
}

void GridGraph::printU(){
    for (int i = 0; i < nodes.size(); i++){
        cout << nodes[i]->info << ": ";
        for (int j = 0; j < nodes[i]->list.size(); j++)
            cout << "{" << nodes[i]->list[j]->info << ":" << nodes[i]->list[j]->x << ":" << nodes[i]->list[j]->y << "} ";
        cout << endl;
    }
    cout << endl;
}
 
void GridGraph::printNodes(){
    cout << " { ";
    for (int i = 0; i < nodes.size(); i++)
        cout << "{" << nodes[i]->info << ":" << nodes[i]->x << ":"   << nodes[i]->y << "} ";
    cout << " }" << endl;
}

void GridGraph::setHeuristic(Node *first, Node *second){
    first->heuristic = abs((second->x-first->x) + (second->y-first->y));
}

void GridGraph::updateDistance(Node *first, Node *second, unordered_map<Node *, int> &umap){
    
    unordered_map<Node*, int>::iterator it;
    it = umap.find(first);
    int min = it->second + 1;
    it = umap.find(second);
    
    if (min < it->second)
        it->second = min;
}

Node* GridGraph::findMinDistance(unordered_map<Node *, int> umap){
    Node *n = nullptr;
    unordered_map<Node*, int>::iterator it;
    if (umap.empty())
        return nullptr;
    int minimum = INT_MAX, total_dist = 0;
    for (it = umap.begin(); it != umap.end(); it++){
        if (!it->first->visit){
            total_dist = it->second + it->first->heuristic;
            if (minimum > total_dist)
                n = it->first;
        }
    }
    return n;
}

vector<Node*> GridGraph::a(){
    return astar(nodes[0], nodes[nodes.size()-1]);
}

vector<Node*> GridGraph::astar(Node *sourceNode, Node *destNode){
    vector<Node*> v;
    unordered_map<Node*, int> m;
    unordered_map<Node*, int>::iterator it;
    Node *n;
    
    for (int i = 0; i < sourceNode->list.size(); i++)
        m.insert({sourceNode->list[i], INT_MAX});
    
    setHeuristic(sourceNode, destNode);
    m.insert({sourceNode, 0});
    n = sourceNode;
    
    while (n != destNode){
        if (n == nullptr)
            break;
        n->visit = true;
        
        for (int i = 0; i < n->list.size(); i++){
            if (!n->list[i]->visit){
                m.insert({n->list[i], INT_MAX});
                updateDistance(n, n->list[i], m);
                setHeuristic(n->list[i], destNode);
                n->list[i]->parent = n;
            }
        }
        n = findMinDistance(m);
    }
    
    for (it = m.begin(); it != m.end(); it++){
        if (it->first == destNode){
            n = it->first;
            v.push_back(n);
            while (n->parent != nullptr){
                v.push_back(n->parent);
                n = n->parent;
            }
        }
    }
    return v;
}
