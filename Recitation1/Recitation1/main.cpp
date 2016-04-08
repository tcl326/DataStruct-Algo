//
//  main.cpp
//  Recitation1
//
//  Created by Student on 2/12/16.
//  Copyright © 2016 Student. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

template <class Object>//, class Obj2>
Object doubleIt(Object a){//, Obj2 b){
    return a*2;
}

template <class Object>
void isVal(Object&& a){
    cout << "This is an rval" << endl;
}

template <class Object>
void isVal(Object& a){
    cout << "This is an lval" << endl;
}

int f() {return 1;}

//functor = function object

class isEven {
public:
    bool operator() (int a){
        return a%2 == 0;
    }
};

class sumNums {
public:
    sumNums () : size(0) {}
    void operator() (int a){
        size += a;
    }
    int operator() () {
        return size;
    }
private:
    int size;
};

class sumEven {
public:
    sumEven() : size(0) {}
    void operator () (int a) {
        if ( a% 2 == 0){
            size++;
        }
    }
    int operator() (){
        return size;
    }
private:
    int size;
};

template < class Itr, class Pred>
void outputSum (Itr begin, Itr end, Pred thing){
    for (Itr itr = begin; itr != end; itr++){
        thing (*itr);
    }
    cout << thing() << endl;
}

int main(){
    vector<int> a;
    a.push_back(10);
    a.push_back(3);
    a.push_back(5);
    a.pop_back();
    
    for (vector<int>::iterator itr = a.begin(); itr != a.end(); itr++){
        *itr = doubleIt(*itr);
    }
    for (int i = 0; i < a.size(); i++){
        cout << a[i] << endl;
    }
    double b = 3.14;
    b = doubleIt(b);
    cout << b << endl;
    
    /*
    string c = "a";
    cout << double(c);
    cout << c << endl;
     */
    int x = 4;
    isVal(x);
    isVal(5);
    isVal(*(new int(5)));
    isVal(f());
    
    //int x = 3;
    isEven obj;
    if(obj(x)){
        cout << "This is even" << endl;
    }
    vector<int> d {1,2,3,4};
    /*
    sumEven thing;
    for (vector<int>::iterator itr = d.begin(); itr != d.end(); itr++){
        thing (*itr);
    }
    cout << thing() << endl;
     */
    
    outputSum(d.begin(), d.end(), sumNums());
    outputSum(d.begin(),d.end(), sumEven());
}
