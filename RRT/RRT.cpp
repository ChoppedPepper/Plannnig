#include "RRT.h"
#include <vector>
#include <memory>
#include <climits>
#include <iostream>

using namespace std;

void RRT::init(vector<vector<int>> gridMap, int stepLength){
    gridMap_ = gridMap; 
    stepLength_ = stepLength;
}

vector<shared_ptr<Node>> RRT::getPath(int startX, int endX, int startY, int endY){
    // init start node and end node
    startNode_ = make_shared<Node>(startX, endX);
    endNode_ = make_shared<Node>(startY, endY);
    // init avail node vector
    availNodeVec_.push_back(startNode_);
    // find path
    while(1){
        // get random node
        shared_ptr<Node> randomNode = getRandomNode();
        // find the closest node of the random node in the avail node vec
        shared_ptr<Node> closestNode = findClosestNode(randomNode);
        // get another avail node, if not exist, return nullptr 
        shared_ptr<Node> availNode = getAvailNode(randomNode, closestNode); 
        // check the avail node, 
        if(availNode){
            // cout << "availNode" << availNode->x << availNode->y << endl;
            if(availNode == endNode_){
                endNode_->parent = availNode->parent;
                break;
            }
            availNodeVec_.push_back(availNode);
        }
    }

    // track the end node back to get path
    vector<shared_ptr<Node>> pathVec;
    trackEndNode(pathVec);

    return pathVec;
}


bool operator==(shared_ptr<Node> node1, shared_ptr<Node> node2){
    return node1->x == node2->x && node1->y== node2->y;
}

shared_ptr<Node> RRT::getRandomNode(){
    int ranX = ran_() % 50;
    int ranY = ran_() % 50;
    shared_ptr<Node> ranNode = make_shared<Node>(ranX - 25, ranY - 25);
    // cout << ranNode->x << " " << ranNode->y << endl; 
    return ranNode;
}

shared_ptr<Node> RRT::findClosestNode(shared_ptr<Node> randomNode){
    shared_ptr<Node> cloNode;
    int minDistance = INT_MAX;
    for(auto node : availNodeVec_){
        int distance = (node->x - randomNode->x) * (node->x - randomNode->x) + 
                       (node->y - randomNode->y) * (node->y - randomNode->y);
        if(distance < minDistance){
            minDistance = distance;
            cloNode = node;
        }
    }
    return cloNode;
}

shared_ptr<Node> RRT::getAvailNode(shared_ptr<Node> randomNode, shared_ptr<Node> closestNode){
    double slope = 0.0;
    if(randomNode->x - closestNode->x != 0){
        slope = abs((randomNode->y - closestNode->y) / (randomNode->x - closestNode->x));
    }else{
        slope = 10;
    }
    // get the potential avail node according to the slope    
    int avaX =  closestNode->x, avaY =  closestNode->y;
    if(slope < 1.0){
        if(randomNode->x - closestNode->x > 0){
            avaX += stepLength_;
        }else{
            avaX -= stepLength_;
        }
    }else{
        if(randomNode->y - closestNode->y > 0){
            avaY += stepLength_;
        }else{
            avaY -= stepLength_;
        }
    }
    // cout << avaX << " " << avaY << endl;
    if(!isAvail(avaX, avaY)){
        return nullptr;
    }

    shared_ptr<Node> avaNode = make_shared<Node>(avaX, avaY);
    avaNode->parent = closestNode;
    return avaNode;
}

bool RRT::isAvail(int x, int y){
    if(x < 0 || x >= gridMap_.size() || y < 0 || y >= gridMap_[0].size() || 
       gridMap_[x][y] == 0){
        return false;
    }
    return true;
}

void RRT::trackEndNode(vector<shared_ptr<Node>>& pathVec){
    shared_ptr<Node> node = endNode_;  
    pathVec.push_back(node);
    while(node->parent){
        pathVec.push_back(node->parent);
        node = node->parent;
    }
    return;
}