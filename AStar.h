#pragma once

#include <vector>
#include <list>

using namespace std;

struct Node{
    int x, y;
    int f, g, h;
    Node* parent = nullptr;

    Node() = default;
    Node(int a, int b) : x(a), y(b), f(0), g(0), h(0), parent(nullptr) { } 
};

class AStar
{
public:
    void init(vector<vector<int>> gridMap);
    list<Node*> getPath(int startX, int endX, int startY, int endY);
    AStar() = default;
    ~AStar();

private:
    Node* getLeastNode();
    void putNodeInList(Node*, list<Node*>&);
    vector<Node*> getAdjacentNode(Node*);
    bool isOutsideMap(int, int);
    bool isTerrain(int, int);
    bool isInList(Node*, const list<Node*>&);
    void updateNodeInOpen(Node*);
    void getEndNodeParent();
    void trackEndNode(list<Node*>&);
       
    vector<vector<int>> gridMap_;  // 1 for valid node, 0 for terrain
    Node* startNode_;
    Node* endNode_;
    list<Node*> openList_;
    list<Node*> closeList_;
};


