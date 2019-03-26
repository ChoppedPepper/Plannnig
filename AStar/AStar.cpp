#include "AStar.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

AStar::~AStar(){

}

void AStar::init(vector<vector<int>> gridMap){
    gridMap_ = gridMap;    
}

list<Node*> AStar::getPath(int startX, int endX, int startY, int endY){
    startNode_ = new Node(startX, endX);
    endNode_ = new Node(startY, endY);
    // init openlist_   
    openList_.push_back(startNode_);
    // find the path 
    while(!openList_.empty()){
        // get the node in openList_ with the least f value, named leastNode
        Node* leastNode = getLeastNode();
        // cout << "leastNode " << leastNode->x << " " << leastNode->y << endl;
        // cout << "size of open list " << openList_.size() << endl;
        
        // put leastNode in the closeList
        putNodeInList(leastNode, closeList_);
        // find the adjacent nodes of leastNode
        vector<Node*> adjacentNodes = getAdjacentNode(leastNode); 
        // work on the adjacent nodes
        for(auto adjNode : adjacentNodes){            
            if(isInList(adjNode, closeList_)){  // if in the close list, do nothing 
                continue;
            }else if(isInList(adjNode, openList_)){  // else if in the open list, update it 
                updateNodeInOpen(adjNode);
            }else{  // else add it in the open list
                putNodeInList(adjNode, openList_);
            }
            
        } 
        // cout << "out for" << endl;        
        // check the endNode is in the openList or not, if in it, end the loop
        if(isInList(endNode_, openList_)){
            getEndNodeParent();
            break;
        }    
    }
    // cout << "out while" << endl;

    // get the path
    list<Node*> pathList;    
    if(endNode_->parent){  // if find the path, get it
        // track back according to endNode's parent to get the path
        trackEndNode(pathList);        
    }else{ // else print message
        cout << "the path is not exist" << endl;
    }
    return pathList;        
}

Node* AStar::getLeastNode(){
    if(openList_.empty()){
        cout << "try to get the leastNode in a empty open list" << endl;
    }

    Node* leastNode = openList_.front();
    int leastF = openList_.front()->f;
    auto iterForLeast = openList_.begin();

    // find leastNode
    for(auto iter = openList_.begin(); iter != openList_.end(); ++iter){
        if((*iter)->f < leastF){            
            leastF = (*iter)->f;
            leastNode = *iter;
            iterForLeast = iter;
        }
    }
    // delete leastNode from open list
    openList_.erase(iterForLeast);

    return leastNode;
}

void AStar::putNodeInList(Node* node, list<Node*>& nodeList){
    nodeList.push_back(node);
    return;
}

vector<Node*> AStar::getAdjacentNode(Node* node){
    vector<Node*> adjacentNodes;
    for(int i = node->x - 1; i <= node->x + 1; ++i){
        for(int j = node->y - 1; j <= node->y + 1; ++j){
            if(isOutsideMap(i, j) || isTerrain(i, j) || (i == node->x && j == node->y)){
                continue;
            }
            Node* adjNode = new Node(i, j);
            if(abs(adjNode->x - node->x) + abs(adjNode->y - node->y) == 1){
                adjNode->g = node->g + 10;
            }else{
                adjNode->g = node->g + 14;
            }            
            adjNode->h = abs(adjNode->x - endNode_->x) + 
                         abs(adjNode->y - endNode_->y);  //Manhattan distance 
            adjNode->f =  node->g + node->h;
            adjNode->parent = node;
            adjacentNodes.push_back(adjNode);                        
        }
    }
    return adjacentNodes;
}

bool AStar::isOutsideMap(int x, int y){
    if(x < 0 || x >= gridMap_.size() || y < 0 || y >= gridMap_[0].size()){
        return true;
    }
    return false; 
}

bool AStar::isTerrain(int x, int y){
    if(gridMap_[x][y] == 0){
        return true;        
    }
    return false;
}

bool AStar::isInList(Node* node, const list<Node*>& nodeList){
    for(auto nodeInList : nodeList){
        if(node->x == nodeInList->x && node->y == nodeInList->y){
            return true;
        }
    }
    return false;
}

void AStar::updateNodeInOpen(Node* node){
    for(auto& nodeInList : openList_){
        if(node->x == nodeInList->x && node->y == nodeInList->y &&
           node->g < nodeInList->g){
            nodeInList->g = node->g;
            nodeInList->f = node->f;
            nodeInList->parent = node->parent;
            return;
        }
    }
    return;
}

void AStar::getEndNodeParent(){
    for(auto nodeInList : openList_){
        if(endNode_->x == nodeInList->x && endNode_->y == nodeInList->y 
           && nodeInList->h == 0){
            endNode_->g = nodeInList->g;            
            endNode_->h = nodeInList->h;
            endNode_->f = nodeInList->f;
            endNode_->parent = nodeInList->parent;
            return;
        }
    }
    cout << "the end node is actually not in open list" << endl;
    return;
}

void AStar::trackEndNode(list<Node*>& nodeList){
    Node* node = endNode_;
    nodeList.push_front(node);
    while(node->parent){
        nodeList.push_front(node->parent);
        // cout << "path node " << node->parent->x << " " << node->parent->y << endl;
        node = node->parent;
    }
    return;
}