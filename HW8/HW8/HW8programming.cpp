//
//  main.cpp
//  HW8
//
//  Created by Student on 4/7/16.
//  Copyright © 2016 Ting-Che Lin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

//----- Question 1 ------//

vector<int> findPointValue (){
    vector<int> pointValue(26);
    string line;
    ifstream letterPointValueText;
    letterPointValueText.open("/Users/student/Desktop/DataStruct&Algo/HW8/HW8/Letter_point_value.txt");
    if (letterPointValueText.is_open()) {
        while (getline(letterPointValueText, line)) {
            string number;
            string character;
            bool space = false;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ' '){
                    space = true;
                    continue;
                }
                if (space) {
                    character+=line[i];
                }
                else{
                    number+=line[i];
                }
            }
            pointValue[int (character[0])-65] = stoi(number);
        }
        letterPointValueText.close();
    }
    return pointValue;
}

int wordPoinValue (string word, const vector<int>& pointValue){
    int wordValue = 0;
    for (int i = 0; i < word.length(); i++) {
        if (int (word[i]) >64 && int (word[i]) < 91) {
            wordValue += pointValue[int(word[i])-65];
        }
        if (int (word[i]) >96 && int (word[i]) < 123) {
            wordValue += pointValue[int(word[i])-97];
        }
    }
    return wordValue;
}

map<string, int> createWordValueMap (const vector<int>& pointValue){
    string word;
    map<string, int> valueMap;
    ifstream words;
    words.open("/Users/student/Desktop/DataStruct&Algo/HW8/HW8/ENABLE.txt");
    if (words.is_open()) {
        while (getline(words, word)) {
            valueMap[word] = wordPoinValue(word, pointValue);
        }
        words.close();
    }

    return valueMap;
}

//------ Question 2 --------//

//
//  Binary Search Tree Class
//
//  Modified code from Weiss
//
#include <string>
#include <vector>
using namespace std;

template<class Comparable>
struct BinaryNode
{
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;
    
    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
    : element{ theElement }, left{ lt }, right{ rt }{ }
    
    BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
    : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
};


// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// bool contains( x )     --> Return true if x is present
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************


template <typename Comparable>
class BinarySearchTree
{
public:
    typedef BinaryNode<Comparable> Node;
    
    BinarySearchTree( ) : root{ nullptr }
    {
    }
    
    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }
    
    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }
    
    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }
    
    
    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }
    
    
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }
    
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    void printAllLowHigh (Comparable & high, Comparable & low){
        printAllLowHigh(high, low, root);
    }
    
    void sringy (){
        Node * t;
        t = root;
        
    }
    
private:
    
    BinaryNode<Comparable> *root;
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, Node * & t )
    {
        if( t == nullptr )
            t = new Node{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, Node * & t )
    {
        if( t == nullptr )
            t = new Node{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing
        
    }
    
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( Node * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }
    
    
    /**
     * Internal method to clone subtree.
     */
    Node * clone( Node *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new Node{ t->element, clone( t->left ), clone( t->right ) };
    }
    
    //Contains Recursive Call
    bool contains(const Comparable & x, Node *t ) const
    {
        if ( t == nullptr){
            return false;
        }
        if ( x < t -> element) {
            contains(x, t -> left);
        }
        else if ( t -> element < x){
            contains(x, t -> right);
        }
        else {
            return true;
        }
        return false;
    }
    
    //printAllLowHigh private call
    void printAllLowHigh (const Comparable & high, const Comparable & low, Node *t ) const{
        if ( t == nullptr ){
            return;
        }
        if (low <= t-> element && t -> element <= high) {
            cout << t -> element;
            printAllLowHigh(high, low, t -> right);
            printAllLowHigh(high, low, t -> left);
        }
        return;
    }
    
};


int main(int argc, const char * argv[]) {
//    vector<int> pointValue;
//    pointValue = findPointValue();
//    
//    cout << wordPoinValue("CAT",pointValue);
//    map<string, int> valueMap;
//    valueMap = createWordValueMap(pointValue);// insert code here...
    
    BinarySearchTree<int> t;
    
    int NUMS = 10;
    const int GAP = 3;
    int i;
    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        t.insert( i );
    cout << t.contains(11);
    
    int low, high;
    low = 3;
    high = 8;
    
    t.printAllLowHigh(high, low);
    
    return 0;
}
