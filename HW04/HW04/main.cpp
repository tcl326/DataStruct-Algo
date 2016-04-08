//
//  main.cpp
//  HW04
//
//  Created by Student on 2/25/16.
//  Copyright © 2016 Ting-Che Lin. All rights reserved.
//

#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>

//#define _USE_MATH_DEFINES

using namespace std;

double degrad(double d) {
    return d * M_PI / 180;
}


// Code below is adapted from http://www.movable-type.co.uk/scripts/latlong.html
// FYI: That website has an applet that computes the haversine distance.
// It also has a link that will show the locations on a map,
// with a line between them.
double haverdist(double lat1, double longit1, double lat2, double longit2)
{
    double r = 6371;
    double dlat = degrad(lat2 - lat1);
    double dlongit = degrad(longit2 - longit1);
    double a = sin(dlat/2)*sin(dlat/2)+
    cos(degrad(lat1))*cos(degrad(lat2))*sin(dlongit/2)*sin(dlongit/2);
    double c = 2*atan2(sqrt(a),sqrt(1-a));
    return r*c;
}

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

//generic function template called perform if that takes four parameters: two iterators, itrStart, itrEnd, and two functors, pred and op. The return value of the generic function template perform if is an int which returns the number of items for which the functor pred returned true.

template<class Itr, class Pred, class Op>
int perform_if(Itr itrStart, Itr itrEnd, Pred pred, Op op)
{
    Itr itr;
    int how_many = 0;
    for (itr = itrStart ; itr != itrEnd; itr++){
        if ( pred( *itr ) )
        {
            op(*itr);
            how_many++;
        }
    }
    return how_many;
}

//Write a functor called isStopOnRoute that has a private member variable called route of type char. The constructor takes a single parameter of type char which it uses to initialize the variable route. It also contains an overloaded operator() that takes a single parameter of type trainStopData; the operator returns true if the train stop is on the route.3

class isStopOnRoute
{
private:
    char _route;
public:
    isStopOnRoute (char route) : _route(route) {}
    bool operator() (trainStopData stopData){
        return stopData.get_id()[0] == _route;
    }
};

//Write a functor called isSubwayStop that has a private member variable called stopId of type string. The constructor takes a single parameter of type string which it uses to initialize the variable stopId. It also contains an overloaded operator() that takes a single parameter of type trainStopData; the operator returns true if the train stop has an id which is the same as stopid.

class isSubwayStop
{
private:
    string _stopId;
public:
    isSubwayStop (string stopID) : _stopId(stopID) {}
    bool operator() (trainStopData stopData){
        return stopData.get_id() == _stopId;
    }
};

//Write a functor called isSubwayStopNearX that has three private member variables called longitude, latitude, and d of type double. The constructor takes three parameters of type double which it uses to initialize the private member variables. It also contains an overloaded operator() that takes a single parameter of type trainStopData; the operator returns true if the distance between the train station location and the value of the functors private member variables, longitude and latitude, is at most d.

class isSubwayStopNearX
{
private:
    double _longitude;
    double _latitude;
    double _d;
public:
    isSubwayStopNearX (double latitude, double longitude, double d) : _longitude(longitude), _latitude(latitude), _d(d) {}
    bool operator() (trainStopData stopData){
        return _d >= haverdist(_latitude, _longitude, stopData.get_latitude(), stopData.get_longitude());
    }
};

//Write a functor called printTrainStopInfo. This class contains a single method, an overloaded operator(), that takes a single parameter of type trainStationData that prints out the train stop information.

class printTrainStopInfo
{
public:
    //printTrainStopInfo ();
    void operator() (trainStopData stopData){
        cout << "Stop ID: " << stopData.get_id()<< endl;
        cout << "Stop Name: " << stopData.get_stop_name() << endl;
        cout << "Stop Latitude: " << stopData.get_latitude() << endl;
        cout << "Stop Longitude: " << stopData.get_longitude() << endl;
    }
};

void menu (vector<trainStopData>& stopDataList){
    char choice;
    cout << "Please make a selection:" << endl;
    cout << "a. Print out the information about all the train stops on a specific route"<< endl;
    cout << "b. Print out the information about a specific train stop" << endl;
    cout << "c. Print out all the train stops within a certain distance" << endl;
    cout << "d. Quit" << endl;
    
    cout << "Input your choice (a, b, c, d): ";
    cin >> choice;
    
    if (choice == 'a'){
        char route;
        cout << "Input the route: ";
        cin >> route;
        //printTrainStopInfo print;
        //isStopOnRoute isStopOnRoute (route);
        //isStopOnRoute p(route);
        //printTrainStopInfo s;
        if (!perform_if(stopDataList.begin(), stopDataList.end(), isStopOnRoute(route), printTrainStopInfo())){
            cout << "No route is found" << endl;
        }
        
        menu(stopDataList);
    }
    
    if (choice == 'b') {
        string ID;
        cout << "Input the train stop ID: ";
        cin >> ID;
        if (!perform_if(stopDataList.begin(), stopDataList.end(), isSubwayStop(ID), printTrainStopInfo())){
            cout << "No route is found" << endl;
        }
        menu(stopDataList);
    }
    
    if (choice == 'c'){
        double longitude;
        double latitude;
        double d;
        cout << "Input the train stop latitude: ";
        cin >> latitude;
        cout << "Input the train stop longitude: ";
        cin >> longitude;
        cout << "Input the search radius in km: ";
        cin >> d;
        if (!perform_if(stopDataList.begin(), stopDataList.end(), isSubwayStopNearX(latitude, longitude, d), printTrainStopInfo())){
            cout << "No route is found" << endl;
        }

        menu(stopDataList);
    }
    
    if (choice == 'd') {
        cout << "The Program Has Quitted";
    }
}

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

int GCD (int a, int b){
    if (b == 0) {
        return a;
    }
    if (a < b) {
        return GCD (b, a);
    }
    return GCD(b, a%b);
}

template <class Object>
Object sumVectorRec(const vector<Object>& a, int left, int right) {
    if( left == right ){ // Base case
        return a[left];
    }
    int center = ( left + right ) / 2;
    Object leftSum = sumVectorRec( a, left, center );
    Object rightSum = sumVectorRec( a, center + 1, right );
    
    return leftSum + rightSum;
}

template<class Object>
Object sumVector( const vector<Object> & a) // driver program
{
    return sumVectorRec(a, 0, a.size()-1);
}

void permuteRec (string& str, int startIndex, int endIndex){
    int i;
    if (startIndex == endIndex) {
        cout << str << endl;
    }
    else{
        for (i = startIndex; i <= endIndex; i++){
            swap(str[startIndex], str[i]);
            permuteRec(str, startIndex+1, endIndex);
            swap(str[startIndex], str[i]);
        }
    }
}

void permute (const string& str){
    string modifiable = str;
    int n;
    n = modifiable.size();
    permuteRec (modifiable, 0, n-1);
}

void myRecFunc(int n)
{
    cout << n << ": ";
    if (n < 1) return;
    myRecFunc(n/2);
    myRecFunc(n/2);
    for (int i = 1; i < n; ++i)
        cout << "*";
    cout << endl;
}

int main(int argc, const char * argv[]) {
//    char choice;
//    cout << "Please make a selection:" << endl;
//    cout << "a. Print out the information about all the train stops on a specific route"<< endl;
//    cout << "b. Print out the information about a specific train stop" << endl;
//    cout << "c. Print out all the train stops within a certain distance" << endl;
//    cout << "d. Quit" << endl;
//    
//    cout << "Input your choice (a, b, c, d): ";
//    cin >> choice;
    
    string line;
    vector<trainStopData> stopDataList;
    ifstream MTATranData;// ("MTA_train_stop_data.txt");
    //open the file with absolute path because of where Xcode store the executables.
    MTATranData.open("/Users/student/Desktop/DataStruct&Algo/HW03B/HW03B/MTA_train_stop_data.txt");
    //by pass the first line
    getline(MTATranData, line, '\n');
    while (MTATranData.good()) {
        vector<string> variables;
        getNextLineAndSplit(MTATranData, variables);
        stopDataList.push_back(trainStopData(variables[0],variables[2],stod(variables[4]),stod(variables[5])));
    }
    //cout << isStopOnRoute('b')(stopDataList[0]);
    
    //menu(stopDataList);
    cout << GCD(10, 20);
    
    // insert code here...
    vector<int> a = {3};
    
    cout << sumVector(a);
    
    string d = "abc";
    
    permute(d);
    
    vector<int> f = {1,2,3,4,5,6,7,8,9,10, 11};
    
    vector<int>::iterator itrStart;
    vector<int>::iterator itrMid;
    vector<int>::iterator itrEnd;
    
    itrStart = f.begin();
    itrEnd = f.end();
    itrMid = f.begin() + f.size()/2;
    
    for (; itrMid != itrEnd; itrMid++) {
        cout << *itrMid;
    }
    
    
    cout << "start" << endl;
    myRecFunc(4);
    
    return 0;
}
