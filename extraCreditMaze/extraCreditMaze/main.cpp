//
//  main.cpp
//  extraCreditMaze
//
//  Created by Student on 3/18/16.
//  Copyright © 2016 Ting-Che Lin. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <fstream>

using namespace std;

vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;
    
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;
}

void convertMaze(string maze, vector<vector<char>>& mazeMatrix){
    vector<string> stringMatrix;
    stringMatrix = split(maze, ',');
    mazeMatrix.resize(stringMatrix.size());
    for (int i = 0; i < mazeMatrix.size(); i++) {
        for (int j = 0; j < stringMatrix[i].size(); j++) {
            mazeMatrix[i].push_back(char(stringMatrix[i][j]));
        }
    }
}

void printMaze(vector<vector<char>> mazeMatrix){
    for (int i = 0 ; i < mazeMatrix.size(); i++) {
        for (int j = 0; j<mazeMatrix[i].size(); j++) {
            cout << mazeMatrix[i][j];
        }
        cout << endl;
    }
}
vector<int> findStart(const vector<vector<char>>& mazeMatrix, char startSymbol){
    vector<int> startCoord;
    for (int i = 0; i < mazeMatrix.size(); i++) {
        for (int j = 0; j < mazeMatrix[i].size(); j++) {
            if (startSymbol == mazeMatrix[i][j]) {
                startCoord = {i , j};
                return startCoord;
            }
        }
    }
    return startCoord = {-1,-1};
}

vector<int> findLocationRecurv(vector<vector<char>>& mazeMatrix, vector<int> currentCoord, char endSymbol, vector<vector<int>>& path){
    mazeMatrix[currentCoord[0]][currentCoord[1]] = 'o';
    vector<int> nextCoord = {-1, -1};
    vector<int> result = {};
    int row = currentCoord[0];
    int col = currentCoord[1];
    //check up
    if (row - 1 >= 0 && mazeMatrix[row-1][col] != 'o') {
        if (mazeMatrix[row-1][col] == endSymbol) {
            path.push_back(currentCoord);
            return result = {row-1, col};
        }
        if (mazeMatrix[row-1][col] == '.') {
            nextCoord = {row-1, col};
            result = findLocationRecurv(mazeMatrix, nextCoord, endSymbol,path);
        }
    }
    if (!result.empty()) {
        path.push_back(currentCoord);
        return result;
    }
    //check right
    if (col + 1 < mazeMatrix[0].size() && mazeMatrix[row][col + 1] != 'o') {
        if (mazeMatrix[row][col + 1] == endSymbol) {
            path.push_back(currentCoord);
            return result = {row, col + 1};
        }
        if (mazeMatrix[row][col + 1] == '.') {
            nextCoord = {row, col + 1};
            result = findLocationRecurv(mazeMatrix, nextCoord, endSymbol, path);
        }
    }
    if (!result.empty()) {
        path.push_back(currentCoord);
        return result;
    }
    //check down
    if (row + 1 < mazeMatrix.size() && mazeMatrix[row + 1][col] != 'o') {
        if (mazeMatrix[row + 1][col] == endSymbol) {
            path.push_back(currentCoord);
            return result = {row + 1, col};
        }
        if (mazeMatrix[row + 1][col] == '.') {
            nextCoord = {row + 1, col};
            result = findLocationRecurv(mazeMatrix, nextCoord, endSymbol, path);
        }
    }
    if (!result.empty()) {
        path.push_back(currentCoord);
        return result;
    }
    //check left
    if (col -1 >= 0 && mazeMatrix[row][col - 1] != 'o') {
        if (mazeMatrix[row][col - 1] == endSymbol) {
            path.push_back(currentCoord);
            return result = {row, col - 1};
        }
        if (mazeMatrix[row][col - 1] == '.') {
            nextCoord = {row, col - 1};
            result = findLocationRecurv(mazeMatrix, nextCoord, endSymbol, path);
        }
    }
    if (!result.empty()) {
        path.push_back(currentCoord);
        return result;
    }
    return result;
}

vector<int> findLocation (const vector<vector<char>>& mazeMatrix, char startSymbol, char endSymbol, vector<vector<int>>& path){
    vector<vector<char>> tempMaze = mazeMatrix;
    vector<int> coordinate={0,0};
    vector<int> startCoord = findStart(mazeMatrix, startSymbol);
    coordinate = findLocationRecurv(tempMaze, startCoord, endSymbol, path);
    path.push_back(coordinate);
    return coordinate;
}

vector<int> findNextCoord (const vector<vector<char>>& mazeMatrix, vector<int> currentCoord, char endSymbol){
    vector<int> nextCoord = currentCoord;
    int row = currentCoord[0];
    int col = currentCoord[1];
    //check up
    if (row - 1 >= 0 && mazeMatrix[row-1][col] != 'o') {
        if (mazeMatrix[row-1][col] == endSymbol) {
            return nextCoord = {row-1, col, 1};
        }
        if (mazeMatrix[row-1][col] == '.') {
            nextCoord = {row-1, col};
            return nextCoord;
        }
    }
    //check right
    if (col + 1 < mazeMatrix[0].size() && mazeMatrix[row][col + 1] != 'o') {
        if (mazeMatrix[row][col + 1] == endSymbol) {
            return nextCoord = {row, col + 1, 1};
        }
        if (mazeMatrix[row][col + 1] == '.') {
            nextCoord = {row, col + 1};
            return nextCoord;        }
    }
    //check down
    if (row + 1 < mazeMatrix.size() && mazeMatrix[row + 1][col] != 'o') {
        if (mazeMatrix[row + 1][col] == endSymbol) {
            return nextCoord = {row + 1, col, 1};
        }
        if (mazeMatrix[row + 1][col] == '.') {
            nextCoord = {row + 1, col};
            return nextCoord;
        }
    }
    //check left
    if (col -1 >= 0 && mazeMatrix[row][col - 1] != 'o') {
        if (mazeMatrix[row][col - 1] == endSymbol) {
            return nextCoord = {row, col - 1,1};
        }
        if (mazeMatrix[row][col - 1] == '.') {
            nextCoord = {row, col - 1};
            return nextCoord;
        }
    }

    return nextCoord;
}

vector<int> findLocationStack (const vector<vector<char>>& mazeMatrix, char startSymbol, char endSymbol, vector<vector<int>> &path){
    vector<vector<char>> tempMaze = mazeMatrix;
    vector<int> startCoord = findStart(mazeMatrix, startSymbol);
    vector<int> locationCoordinate = {-1, -1};
    vector<int> nextCoord;
    vector<int> currentCoord;
    stack<vector<int>> backtrackingStack;
    backtrackingStack.push(startCoord);
    while (!backtrackingStack.empty()) {
        currentCoord = backtrackingStack.top();
        tempMaze[currentCoord[0]][currentCoord[1]] = 'o';
        nextCoord = findNextCoord(tempMaze, currentCoord, endSymbol);
        if (nextCoord.size() == 3) {
            locationCoordinate = {nextCoord[0],nextCoord[1]};
            break;
        }
        if (nextCoord == currentCoord) {
            backtrackingStack.pop();
            continue;
        }
        backtrackingStack.push(nextCoord);
    }
    while (!backtrackingStack.empty()) {
        path.push_back(backtrackingStack.top());
        backtrackingStack.pop();
    }
    path.push_back(locationCoordinate);
    return locationCoordinate;
}

vector<vector<int>> findNextNodes (const vector<vector<char>>& mazeMatrix, vector<int> currentCoord, char endSymbol){
    vector<vector<int>> nextNodes;
    vector<int> nextCoord = currentCoord;
    int row = currentCoord[0];
    int col = currentCoord[1];
    //check up
    if (row - 1 >= 0 && mazeMatrix[row-1][col] != 'o') {
        if (mazeMatrix[row-1][col] == endSymbol) {
            return nextNodes = {{row-1, col, 1}};
        }
        if (mazeMatrix[row-1][col] == '.') {
            nextCoord = {row-1, col};
            nextNodes.push_back(nextCoord);
        }
    }
    //check right
    if (col + 1 < mazeMatrix[0].size() && mazeMatrix[row][col + 1] != 'o') {
        if (mazeMatrix[row][col + 1] == endSymbol) {
            return nextNodes = {{row, col + 1, 1}};
        }
        if (mazeMatrix[row][col + 1] == '.') {
            nextCoord = {row, col + 1};
            nextNodes.push_back(nextCoord);
        }
    }
    //check down
    if (row + 1 < mazeMatrix.size() && mazeMatrix[row + 1][col] != 'o') {
        if (mazeMatrix[row + 1][col] == endSymbol) {
            return nextNodes = {{row + 1, col, 1}};
        }
        if (mazeMatrix[row + 1][col] == '.') {
            nextCoord = {row + 1, col};
            nextNodes.push_back(nextCoord);
        }
    }
    //check left
    if (col -1 >= 0 && mazeMatrix[row][col - 1] != 'o') {
        if (mazeMatrix[row][col - 1] == endSymbol) {
            return nextNodes = {{row, col - 1,1}};
        }
        if (mazeMatrix[row][col - 1] == '.') {
            nextCoord = {row, col - 1};
            nextNodes.push_back(nextCoord);
        }
    }
    
    return nextNodes;
}

vector<int> findLocationQueue (const vector<vector<char>>& mazeMatrix, char startSymbol, char endSymbol, vector<vector<int>>& path){
    vector<vector<char>> tempMaze = mazeMatrix;
    vector<int> locationCoordinate;
    vector<int> startCoord = findStart(mazeMatrix, startSymbol);
    vector<vector<int>> nextNodes;
    queue<vector<vector<int>>> nodeQueues;
    vector<vector<vector<int>>> vistedNode;
    nodeQueues.push({{-1,-1},startCoord});
    while (!nodeQueues.empty()) {
        tempMaze[nodeQueues.front()[1][0]][nodeQueues.front()[1][1]] = 'o';
        nextNodes = findNextNodes(tempMaze, nodeQueues.front()[1], endSymbol);
        if (!nextNodes.empty()){
            if (nextNodes[0].size() == 3) {
                locationCoordinate = {nextNodes[0][0],nextNodes[0][1]};
                break;
            }
            for (int i = 0; i < nextNodes.size(); i++) {
                nodeQueues.push({nodeQueues.front()[1],nextNodes[i]});
            }
        }
        vistedNode.push_back(nodeQueues.front());
        nodeQueues.pop();
    }
    path.push_back(locationCoordinate);
    path.push_back(nodeQueues.front()[1]);
    path.push_back(nodeQueues.front()[0]);
    while (true) {
        for (int i = 0; i < vistedNode.size(); i ++) {
            if (vistedNode[i][1] == path.back()) {
                path.push_back(vistedNode[i][0]);
                if (vistedNode[i][0] == startCoord) {
                    break;
                }
                continue;
            }
        }
        if (path.back() == startCoord) {
            break;
        }
    }
    
    return locationCoordinate;
}

class maze {
    char endSymbol;
    char startSymbol;
    vector<vector<char>> mazeMatrix;
    vector<int> finalLocation;
    vector<vector<int>> path;
    
public:
    maze(vector<vector<char>> maze = {}, char start = 's', char end = 'e'): endSymbol(end), startSymbol(start),mazeMatrix(maze){}
    void print_maze(){
        for (int i = 0 ; i < mazeMatrix.size(); i++) {
            for (int j = 0; j<mazeMatrix[i].size(); j++) {
                cout << mazeMatrix[i][j];
            }
            cout << endl;
        }
    }
    void loadMaze (ifstream& mazeStream){
        string  line;
        int i = 0;
        while(getline(mazeStream, line )){
            mazeMatrix.push_back({});
            for (int j = 0; j < line.size(); j++) {
                mazeMatrix[i].push_back (char(line[j]));
            }
            i++;
        }
    }
    vector<int> findLocationRecurv(){
        finalLocation = ::findLocation(mazeMatrix, startSymbol, endSymbol, path);
        return finalLocation;
    }
    vector<int> findLocationStack(){
        finalLocation = ::findLocationStack(mazeMatrix,startSymbol,endSymbol, path);
        return finalLocation;
    }
    vector<int> findLocationQueue(){
        finalLocation = ::findLocationQueue(mazeMatrix,startSymbol,endSymbol, path);
        return finalLocation;
    }
    void printMazeWithPath(){
        vector<vector<char>> tmpMaze = mazeMatrix;
        for (int i = 0; i < path.size(); i++) {
            tmpMaze[path[i][0]][path[i][1]] = 'o';
        }
        for (int i = 0 ; i < tmpMaze.size(); i++) {
            for (int j = 0; j<tmpMaze[i].size(); j++) {
                cout << tmpMaze[i][j];
            }
            cout << endl;
        }
    }
};

int main(int argc, const char * argv[]) {
//    string maze = "xxxxxxxxxxxxxxxxxx,s.x...x....x....xx,x.x.x.x.xx.x..xxxx,x...x..exx.x..x.xx,xxx.x..xxx...xx.xx,xxx.xx..xx......xx,xxx...x.xxxxxxxxxx,xxxxx.x.......xxxx,xxxxxxxxxxxxxxxxxx";
//    vector<vector<char>> maze1;
//    vector<int> startCoord;
//    vector<int> location;
//    convertMaze(maze, maze1);
//    printMaze(maze1);
//    startCoord = findStart(maze1, 's');
//    location = findLocation(maze1, 's', 'e');
//    
//    cout << location[0] << "," << location[1] << endl;
//    
//    location = findLocationStack(maze1, 's', 'e');
//    
//    cout << location[0] << "," << location[1] << endl;
//    
//    location = findLocationQueue(maze1, 's', 'e');
//    
//    cout << location[0] << "," << location[1] << endl;
    
//    maze1 = {
//        {
//    }
    
    maze maze1;
    ifstream myfile;
    myfile.open("/Users/student/Desktop/DataStruct&Algo/extraCreditMaze/maze.txt");
    maze1.loadMaze(myfile);
    maze1.print_maze();
    maze1.findLocationQueue();
    maze1.printMazeWithPath();
    return 0;
}
