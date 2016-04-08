//
//  main.cpp
//  HW03B
//
//  Created by Student on 2/14/16.
//  Copyright © 2016 Student. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>

using namespace std;

class trainStopData {
public:
    trainStopData(string stop_id = "", string stop_name = "", double stop_lat = 0.0, double stop_lon = 0.0):
    stop_id(stop_id), stop_name(stop_name), stop_lat(stop_lat), stop_lon(stop_lon){};
    
    string get_id( ) const{
        return stop_id;
    }
    string get_stop_name( ) const{
        return stop_name;
    }
    double get_latitude( ) const{
        return stop_lat;
    }
    double get_longitude( ) const{
        return stop_lon;
    }
private:
    string stop_id; // id of train stop (1st token)
    string stop_name; // name of station (4th token)
    double stop_lat; // latitude of train stop location
    double stop_lon; // longitude of train stop location
};

void getNextLineAndSplit(istream& stream, vector<string>& variables)
{
    string line;
    getline(stream,line);
    stringstream lineStream(line);
    string cell;
    
    while(getline(lineStream,cell,','))
    {
        variables.push_back(cell);
    }
}

vector<int> A {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
vector<int> B {1, 2, 1, 2, 1, 2};
vector<int> C{1, 2, 3, 1, 2, 3};
vector<int> D(6);
vector<int> E(10);

void printVector (const vector<int>& any){
    cout << "[";
    for (int i = 0; i < any.size(); i++) {
        cout << any[i];
        if (i == any.size() - 1){
            continue;
        }
        cout << ", ";
    }
    cout << "]";
}

int main(int argc, const char * argv[]) {
    string line;
    vector<trainStopData> stopData;
    ifstream MTATranData;// ("MTA_train_stop_data.txt");
    //open the file with absolute path because of where Xcode store the executables.
    MTATranData.open("/Users/student/Desktop/DataStruct&Algo/HW03B/HW03B/MTA_train_stop_data.txt");
    //by pass the first line
    getline(MTATranData, line, '\n');
    while (MTATranData.good()) {
        vector<string> variables;
        getNextLineAndSplit(MTATranData, variables);
        stopData.push_back(trainStopData(variables[0],variables[2],stod(variables[4]),stod(variables[5])));
    }
    
    cout << stopData[2].get_stop_name();
    
    //testing for HW03Bwritten
    /*
    copy(A.begin(), A.begin()+6, D.begin());
    // D now equals {1, 2, 3, 4, 5, 6}
    
    cout << count(B.begin(),B.end(),1);
    
    cout << count_if(B.begin( ), B.end(), bind1st(not_equal_to<int>( ), 1));
    //prints out the number of times a one doesn’t appear in B.
    
    bool same;
    same = equal(A.begin( ), A.begin()+3, C.begin());

    vector<int>::iterator vecItr;
    vecItr = find(A.begin(), A.end(), 5);
    // returns an iterator to 5 in vector A
    if (vecItr != A.end( ))
        cout << *vecItr;
    // prints out the value pointed to by vecItr
    
    vecItr = find_if(C.begin(), C.end(), bind2nd(greater<int>(), 2));
    // returns an iterator to 3 in C
    if (vecItr != C.end( ))
        cout << *vecItr;
    // prints out the value pointed to by vecItr
    */
    
    return 0;
}
