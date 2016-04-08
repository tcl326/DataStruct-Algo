//
//  main.cpp
//  HW03A
//
//  Created by Student on 2/12/16.
//  Copyright © 2016 Student. All rights reserved.
//

#include <iostream>
#include <string>



template <typename Object>
class Vector
{
public:
    explicit Vector( int initSize = 0 )
    : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }
    { objects = new Object[ theCapacity ]; }
    
    Vector( const Vector & rhs )
    : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
    {
        objects = new Object[ theCapacity ];
        for( int k = 0; k < theSize; ++k )
            objects[ k ] = rhs.objects[ k ];
    }
    
    Vector & operator= ( const Vector & rhs )
    {
        Vector copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    ~Vector( )
    { delete [ ] objects; }
    
    Vector( Vector && rhs )
    : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }
    
    Vector & operator= ( Vector && rhs )
    {
        std::swap( theSize, rhs.theSize );
        std::swap( theCapacity, rhs.theCapacity );
        std::swap( objects, rhs.objects );
        
        return *this;
    }
    
    bool empty( ) const
    { return size( ) == 0; }
    int size( ) const
    { return theSize; }
    int capacity( ) const
    { return theCapacity; }
    
    Object & operator[]( int index )
    {
        return objects[ index ];
    }
    
    const Object & operator[]( int index ) const
    {
        return objects[ index ];
    }
    
    void resize( int newSize )
    {
        if( newSize > theCapacity )
            reserve( newSize * 2 );
        theSize = newSize;
    }
    
    void reserve( int newCapacity )
    {
        if( newCapacity < theSize )
            return;
        
        Object *newArray = new Object[ newCapacity ];
        for( int k = 0; k < theSize; ++k )
            newArray[ k ] = std::move( objects[ k ] );
        
        theCapacity = newCapacity;
        std::swap( objects, newArray );
        delete [ ] newArray;
    }
    
    // Stacky stuff
    void push_back( const Object & x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = x;
    }
    // Stacky stuff
    void push_back( Object && x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = std::move( x );
    }
    
    // Iterator stuff: not bounds checked
    typedef Object * iterator;
    typedef const Object * const_iterator;
    
    iterator begin( )
    { return &objects[ 0 ]; }
    const_iterator begin( ) const
    { return &objects[ 0 ]; }
    iterator end( )
    { return &objects[ size( ) ]; }
    const_iterator end( ) const
    { return &objects[ size( ) ]; }
    
    static const int SPARE_CAPACITY = 2;
    
    //erase method
    
    iterator erase(Vector<Object>::iterator vItr){
        std::copy(vItr+1, end(), vItr);
        resize(size()-1);
        return vItr;
    }
    
    
private:
    int theSize;
    int theCapacity;
    Object * objects;
};

//print_if functor

template <class Itr, class UnaryPred>
void print_if(Itr begin, Itr end, UnaryPred pred){
    for (Itr itr = begin; itr != end; itr++) {
        if (pred(*itr)){
            std::cout << *itr << std::endl;
        }
    }
}

//GPA_in_range functor

template <class Object>
class GPA_in_range {
    
public:
    GPA_in_range(double l, double h){
        low = l;
        high = h;
    }
    bool operator() (Object student){
        if (student.gpa() <= high && student.gpa() >= low)
            return true;
        else
            return false;
    }
private:
    double low;
    double high;
};

//Student class

class student{
public:
    student(double gpa = 0.0, std::string name = "") : gpa_student(gpa), name_student(name) {}
    double gpa(){
        return gpa_student;
    }
    std::string name(){
        return name_student;
    }
private:
    double gpa_student;
    std::string name_student;
};

//cout operator

std::ostream &operator<<(std::ostream &os, student &student) {
    return os << student.name();
}
//Testing for written part 4
/*
template< class Itr >
void subtractOne( Itr start, Itr end )
{
    for (Itr itr = start; itr != end; itr++) {
        *itr = *itr - 1;
    }
}*/

int main(int argc, const char * argv[]) {
    // insert code here...
    
    //Test case for Programming part 2 and 3
    Vector<student> a;
    for (int i = 0; i < 100; i++) {
        student b((rand()%40)/10.0+1, "student" + std::to_string(i));
        a.push_back(b);
    }
    
    print_if(a.begin(), a.end(), GPA_in_range<student>(3, 4));
    
    
    //Testing
    /*
    
    Vector<int> c;
    for (int i = 0 ; i < 13; i++){
        c.push_back(i);//{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    }
    Vector<int>::iterator itr1 = c.begin()+2;f
    Vector<int>::iterator itr2 = c.begin()+4;
    Vector<int>::iterator itr3 = c.begin()+8;
    std::cout << *(c.begin( ) + ( c.end( ) - c.begin( ) )/2 ) << std::endl;
    c.erase(itr2);
    std::cout << *itr1 << std::endl;
    std::cout << *itr2 << std::endl;
    std::cout << *itr3 << std::endl;
    std::cout << *(c.begin( ) + ( c.end( ) - c.begin( ) )/2 ) << std::endl;
    
    Vector< int > d;
    d.push_back(144);
    d.push_back(524);
    d.push_back(230);
    d.push_back(8);
    subtractOne( d.begin( ), d.end( ) );
    for (int i = 0; i < d.size(); i++) {
        std::cout << d[i] << std:: endl;;
    }
     */

    return 0;
}
