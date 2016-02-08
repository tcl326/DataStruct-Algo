//
//  main.cpp
//  HW02
//
//  Created by Student on 2/5/16.
//  Copyright © 2016 Student. All rights reserved.
//
#include <memory>

#include <iostream>

using namespace std;



class IntArray{
public:
    IntArray(int n = 0): size(n), array(new int[n]){}
    // add your methods here
    IntArray(const IntArray &obj)
    {
        array = new int[size];
        for (int i = 0; i < size; i++){
            array[i] = obj.array[i]; // copy the value
        }
        
    }
    IntArray(IntArray&& other):array(nullptr), size(0)
    {
        
        array = other.array;
        size = other.size;
        other.array = nullptr;
        other.size = 0;
    }

    IntArray& operator=(IntArray&& other){
        if (this != &other)
        {
            delete[] array;
            array = other.array;
            size = other.size;
            other.array = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    ~IntArray(){
        if (array != nullptr)
        {
            std::cout << " Deleting resource.";
            // Delete the resource.
            delete[] array;
        }

    };

    void put (int i, int value);
    int get( int i);
    
private:
    int * array;
    int size;
};

void IntArray::put(int i, int value){
    array[i] = value;
    cout << array[i];
}

int IntArray::get (int i){
    return array[i];
}

// Function 1
void f( const string & s )
{
    cout << "Function 1 was called." << endl;
}
// Function 2
void f( string & s )
{
    cout << "Function 2 was called." << endl;
}
// Function 3
void f( string && s )
{
    cout << "Function 3 was called." << endl;
}


int main(int argc, const char * argv[]) {
    IntArray numbers(5);
    for (int i = 0; i < 5; i ++){
        numbers.put(i,2);
    }
    cout << numbers.get(0);
    
    f(string("hello"));
    string s1 = "hello";
    f(s1);
    string s2 = "hello";
    f( std::move(s2) );
    const string s3 = "hello";
    f(s3);
    
    return 0;
}


