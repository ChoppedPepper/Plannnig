#include "AStar.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

int main(){
    // init map
    vector<vector<int>> searchMap(6, vector<int>(10, 1));
    searchMap[2][5] = 0;
    searchMap[3][5] = 0;
    searchMap[4][5] = 0;
    cout << "the map for searching is depicted" << endl;
    for(auto& a : searchMap){
        for(auto& b : a){
            cout << b;
        }
        cout << endl;
    }
    
    // get path    
    int startX = 0, endX = 0, startY = 0, endY = 0;
    cout << "please input the (x, y) of start node and end node" << endl;        
    cin >> startX >> endX >> startY >> endY;
    cout << "you input is (" << startX << ", " << endX << ") for start node and (" 
         << startY << ", " << endY << ") for end node" << endl;
    AStar astar;
    astar.init(searchMap);
    list<Node*> path;
    path = astar.getPath(startX, endX, startY, endY);

    // print path
    for(auto point : path){
       searchMap[point->x][point->y] = 2;
    }
    cout << "the path is depicted" << endl;
    for(auto& a : searchMap){
        for(auto& b : a){
            cout << b;
        }
        cout << endl;
    }

    
    return 0;
}