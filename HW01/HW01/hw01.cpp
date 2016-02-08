//
//  main.cpp
//  HW01
//
//  Created by Student on 1/29/16.
//  Copyright © 2016 Student. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
using namespace std;

class timer {
public:
    timer() : start(clock()) {}
    double elapsed() { return ( clock() - start ) / CLOCKS_PER_SEC; }
    void reset() { start = clock(); }
private:
    double start;
};

//Use the following code from Weissâ€™ book â€Data Structures and Algorithm Analysis in C++â€ (4th edition) http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/MaxSumTest.cpp


/**
 * Cubic maximum contiguous subsequence sum algorithm.
 */
int maxSubSum1( const vector<int> & a )
{
    int maxSum = 0;
    
    for( int i = 0; i < a.size( ); ++i )
        for( int j = i; j < a.size( ); ++j )
        {
            int thisSum = 0;
            
            for( int k = i; k <= j; ++k )
                thisSum += a[ k ];
            
            if( thisSum > maxSum )
                maxSum   = thisSum;
        }
    
    return maxSum;
}


/**
 * Quadratic maximum contiguous subsequence sum algorithm.
 */
int maxSubSum2( const vector<int> & a )
{
    int maxSum = 0;
    
    for( int i = 0; i < a.size( ); ++i )
    {
        int thisSum = 0;
        for( int j = i; j < a.size( ); ++j )
        {
            thisSum += a[ j ];
            
            if( thisSum > maxSum )
                maxSum = thisSum;
        }
    }
    
    return maxSum;
}


/**
 * Linear-time maximum contiguous subsequence sum algorithm.
 */
int maxSubSum4( const vector<int> & a )
{
    int maxSum = 0, thisSum = 0;
    
    for( int j = 0; j < a.size( ); ++j )
    {
        thisSum += a[ j ];
        
        if( thisSum > maxSum )
            maxSum = thisSum;
        else if( thisSum < 0 )
            thisSum = 0;
    }
    
    return maxSum;
}

vector<int> initVectorWithRandomN (double n)
{
    vector<int> initVector(n);
    for (int &i : initVector)
        i = (rand() % 2001) - 1000;
    return initVector;
}

int main(int argc, const char * argv[]) {
    vector<double> n = {pow(2.0,8), pow(2.0,9), pow(2.0,10), pow(2.0,11), pow(2.0,12)};
    cout.setf( ios::fixed, ios::floatfield );
    cout.precision( 10 );
    vector<int> vec = initVectorWithRandomN(n[0]);
    cout << vec[0] << "," << vec.size() << endl;
    timer t;
    double nuClicks;
    
    // Part1
    cout << "maxSubSum1" << endl;
    for (int i = 0; i < n.size(); i++){
        vector<int> items;
        t.reset();
        items = initVectorWithRandomN(n[i]);
        maxSubSum1( items );
        nuClicks = t.elapsed();
        cout << "n = 2^" << i+7 << ": " << nuClicks << endl;
    }
    cout << "maxSubSum2" << endl;
    for (int i = 0; i < n.size(); i++){
        vector<int> items;
        t.reset();
        items = initVectorWithRandomN(n[i]);
        maxSubSum2( items );
        nuClicks = t.elapsed();
        cout << "n = 2^" << i+7 << ": " << nuClicks << endl;
    }
    cout << "maxSubSum4" << endl;
    for (int i = 0; i < n.size(); i++){
        vector<int> items;
        t.reset();
        items = initVectorWithRandomN(n[i]);
        maxSubSum4( items );
        nuClicks = t.elapsed();
        cout << "n = 2^" << i+7 << ": " << nuClicks << endl;
    }
    
    // Part2
    for (int a = 0; a < n.size(); a++){
        
        int sum = 0;
        t.reset();
        for (int i = 0; i < n[a]; i++){
            ++sum;
        }
        nuClicks = t.elapsed();
        cout << nuClicks << ",";
        
        
        sum = 0;
        t.reset();
        for(int i = 0; i < n[a]; i++){
            for(int j = 0; j < n[a]; ++j){
                ++sum;}
        }
        nuClicks = t.elapsed();
        cout << nuClicks << ",";
        
        sum = 0;
        t.reset();
        for(int i = 0; i < n[a]; i++){
            for(int j = 0; j < i; ++j){
                ++sum;}
        }
        nuClicks = t.elapsed();
        cout << nuClicks << ",";
        
        sum = 0;
        t.reset();
        for(int i = 0; i < n[a]; i++){
            for(int j = 0; j < n[a]; ++j){
                for(int k = 0; k < n[a]; ++k){
                    ++sum;}
            }
        }
        nuClicks = t.elapsed();
        cout << nuClicks << endl;
    }
    cout << n[0];
    return 0;
}
