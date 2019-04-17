#pragma once

#include <vector>
#include <memory>
#include <random>

using namespace std; 

struct Node{
    int x, y;
    shared_ptr<Node> parent;
    Node() = default;
    Node(int a, int b) : x(a), y(b), parent(nullptr) { } 
};

bool operator==(shared_ptr<Node> node1, shared_ptr<Node> node2);

class RRT{
public:
    void init(vector<vector<int>> gridMap, int stepLength);
    vector<shared_ptr<Node>> getPath(int startX, int endX, int startY, int endY);
private:
    shared_ptr<Node> getRandomNode();
    shared_ptr<Node> findClosestNode(shared_ptr<Node> randomNode);
    shared_ptr<Node> getAvailNode(shared_ptr<Node> randomNode, shared_ptr<Node> closestNode);
    bool isAvail(int x, int y);
    void trackEndNode(vector<shared_ptr<Node>>& pathVec);

    vector<vector<int>> gridMap_; 
    int stepLength_;
    shared_ptr<Node> startNode_;
    shared_ptr<Node> endNode_;
    vector<shared_ptr<Node>> availNodeVec_;
    random_device ran_;
};