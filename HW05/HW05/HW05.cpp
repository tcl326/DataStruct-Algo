//
//  main.cpp
//  HW05
//
//  Created by Student on 3/3/16.
//  Copyright © 2016 Ting-Che Lin. All rights reserved.
//

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <random>
#include <functional>
#include <string>

using namespace std;



template <class RandItr>
void mergeSort(RandItr tmp, RandItr start, RandItr end)
{
    
    if ((end - start) != 1)
    {
        RandItr mid = start + (end - start) / 2;
        mergeSort(tmp,start, mid);
        mergeSort(tmp,mid, end);
        merge(start, mid, mid, end, tmp);
        copy(tmp, tmp + (end - start), start);
    }

    
}


template <class RandItr>
void mergeSort( RandItr start, RandItr end )
{
    int sz = end - start; // or use auto sz = end-start;
    //  cout << sz;
    typedef typename iterator_traits< RandItr >::value_type Object; //Xcode
    // typedef iterator_traits< RandItr >::value_type Object; //Other compilers
    // Don’t worry about this line of code
    vector<Object> tmp( sz );
    mergeSort( tmp.begin(), start, end);
//    for (int i = 0; i < tmp.size(); i++) {
//        cout << tmp[i]<< endl;
//    }
}

class student {
public:
    student (const string& who, double grade) : name(who), gpa(grade) {}
    string getName () const { return name; }
    double getGPA () const { return gpa; }
private:
    string name;
    double gpa;
};

class meFirst {
private:
    string _me;
    
public:
    meFirst (string me = "") : _me(me) {}
    bool operator() (student first, student second){
        if (first.getName() == _me){
            return true;
        }
        if (second.getName() == _me) {
            return false;
        }
        return first.getName() < second.getName();
    }
};

void orderContainer (vector<bool>& trueFalse){
    int swapIndex = 0;
    bool boolSwap = false;
    //boolSwap＝false;
    for (int i = 0 ; i < trueFalse.size(); i++) {
        if (boolSwap) {
            if (!trueFalse[i]) {
                swap(trueFalse[i], trueFalse[swapIndex]);
                swapIndex++;
            }
        }
        boolSwap = trueFalse[i];
        if (!boolSwap) {
            swapIndex++;
        }
    }
}

void bigSmallSort (vector< int>& intVector ){
    bool bigger;
    for (int i = 0 ; i < intVector.size()-1; i++) {
        bigger = !i%2;
        if (bigger){
            if (intVector[i+1] > intVector[i]) {
                swap(intVector[i+1], intVector[i]);
            }
        }
        else{
            if (intVector[i+1] < intVector[i] ) {
                swap(intVector[i+1], intVector[i]);
            }
        }
    }
}

//For Written HW testing

//void printVec (vector<int> a){
//    cout << "[";
//    for (int i = 0 ; i < a.size(); i++) {
//        cout << a[i];
//        if (i == a.size()-1) {
//            continue;
//        }
//        cout << ", ";
//    }
//    cout << "]" << endl;
//}
//
//template<class Comparable>
//void insertionSort( vector<Comparable> & a )
//{
//    int j;
//    for( int p = 1; p < a.size( ); p++ )
//    {
//        Comparable tmp = a[ p ];
//        for( j = p; j > 0 && tmp < a[ j - 1 ]; j-- )
//            a[ j ] = a[ j - 1 ];
//        a[ j ] = tmp;
//        printVec(a); // prints the contents of the vector in order
//    }
//}
//
//template <class Comparable>
//void myMerge( vector<Comparable> & a, vector<Comparable>& tmpArray,
//             int leftPos, int rightPos, int rightEnd )
//{
//    int leftEnd = rightPos - 1;
//    int tmpPos = leftPos;
//    int numElements = rightEnd - leftPos + 1;
//    
//    // Main loop
//    while( leftPos <= leftEnd && rightPos <= rightEnd ){
//        if( a[ leftPos ] <= a[ rightPos ] )
//            tmpArray[ tmpPos++ ] = std::move(a[ leftPos++ ]);
//        else
//            tmpArray[ tmpPos++ ] = std::move(a[ rightPos++ ]);
//    }
//    while( leftPos <= leftEnd ){ // Copy rest of first half
//        tmpArray[ tmpPos++ ] = std::move(a[ leftPos++ ]);
//    }
//    while( rightPos <= rightEnd ){ // Copy rest of right half
//        tmpArray[ tmpPos++ ] =std::move(a[ rightPos++ ]);
//    }
//    // Copy tmpArray back
//    for( int i = 0; i < numElements; i++, --rightEnd )
//        a[ rightEnd ] = std::move(tmpArray[ rightEnd]);
//    }
//
//template <class Comparable>
//void mergeSort( vector<Comparable> & a, vector<Comparable> & tmpArray, int left, int right )
//{
//    if( left < right )
//    {
//        int center = ( left + right ) / 2;
//        cout << left << "," << center << endl;
//        printVec(a);
//        mergeSort( a, tmpArray, left, center );
//        cout << center + 1 << "," << right << endl;
//        printVec(a);
//        mergeSort( a, tmpArray, center + 1, right );
//        myMerge( a, tmpArray, left, center + 1, right );
//        printVec(a); // prints the contents of the vector in order
//    }
//}
//
//
//void quickSort( vector<int> & a, int low, int high )
//{
//    if (low < high)
//    {
//        int mid = ( low + high )/2; // select pivot to be element in middle position
//        int pivot = a[ mid ];
//        swap( a[high], a[mid] ); // put pivot in a[high]
//        // Begin partitioning
//        int i, j;
//        for( i = low, j = high - 1; ; )
//        {
//            while ( a[i ] < pivot ) ++i;
//            while( j > i && pivot < a[j ] ) --j;
//            if( i < j )
//                swap( a[ i++ ], a[ j-- ] );
//            else
//                break;
//        }
//        swap( a[ i ], a[ high ] ); // Restore pivot
//        cout << i << ", " << j << ", " << pivot << endl;
//        printVec(a); // prints the contents of the vector in order
//        quickSort( a, low, i - 1 ); // Sort small elements
//        cout << i << ", " << j << ", " << pivot << endl;
//        printVec(a);
//        quickSort( a, i + 1, high ); // Sort large elements
//    }
//}
//
//void myRecFunc1(int n)
//{
//    if (n < 1) return;
//    cout << n << ", ";
//    myRecFunc1(n/2);
//    cout << n << ", ";
//}
//
//void myRecFunc2(int n)
//{
//    if (n < 1) return;
//    cout << n << ", ";
//    myRecFunc2(n/2);
//    cout << n << ", ";
//    myRecFunc2(n/2);
//}


int main(int argc, const char * argv[]) {

    vector<int> a {4,3,2,1,4,5,6,72,3,3};
    vector<int> b = {2,3,4};
    //mergeSort(a.begin(), a.end());
    vector<int> c(a.size());
    //std::merge(a.begin(), a.begin()+1, a.begin()+1, a.end(), c.begin());
    cout << "a" << endl;
    mergeSort(a.begin(), a.end());
    for (int i = 0; i < a.size(); i++) {
        cout<< a[i] << endl;;
    }
    vector<bool> trueFalse = {1,1,1,0,1,1,0,1,1,1};
    orderContainer(trueFalse);
    
    //swap(trueFalse[0],trueFalse[1]);
    
    for (int i = 0; i < trueFalse.size(); i++) {
        cout << trueFalse [i];
    }
    cout << endl;
    
    vector<int> intVector = {5,9,8,2,3,4};
    bigSmallSort(intVector);
    
    for (int i = 0; i < intVector.size(); i++) {
        cout << intVector [i];
    }
    
    cout << endl;
    
    //For written HW testing
    
//    vector<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//    vector<int> B = {1, 2, 1, 2, 1, 2};
//    vector<int> C(16);
//    
//    sort(B.begin( ), B.begin()+4);
//    
//    for (int i = 0; i < B.size(); i++) {
//                cout << B [i];
//    }
//    cout << endl;
//    sort(A.begin(), A.end(), greater<int>());
//    
//    for (int i = 0; i < A.size(); i++) {
//        cout << A [i];
//    }
//    cout << endl;
//    
//    sort(B.begin(), B.end(), greater<int>());
//    
//    for (int i = 0; i < B.size(); i++) {
//        cout << B [i];
//    }
//    cout << endl;
//    
//    merge(A.begin( ), A.end(), B.begin( ), B.end(), C.begin( ), greater<int>());
//    
//    for (int i = 0; i < C.size(); i++) {
//        cout << C [i];
//    }
//    cout << endl;
//    
//    vector<int> a =  {28, 10, 2, 27, 5, 1};//{11,10,1,3,2,5};
//    
//    //insertionSort(a);
//    
//    vector<int> tmp(a.size());
//    
//    //mergeSort(a, tmp, 0, a.size()-1);
//    
//    quickSort(a, 0, a.size()-1);
//    
//    vector<int> b = {0,1,2,3,4,5};
//    for (int i = 0; i< b.size(); ) {
//        cout << b[++i];
//    }
//    
//    vector<int> c = {2, 1, 4, 3, 6, 5};
//    
//    //insertionSort(c);
//    
//    quickSort(c, 0, c.size()-1);
//    
//    myRecFunc1(4);
//    
//    cout << endl;
//    
//    myRecFunc2(4);
    
    return 0;
}
