//
//  Modified from Weiss' linked list class

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <stack>

using namespace std;

template <typename Object>
class List
{
private:
    
    struct Node
    {
        Object  data;
        Node   *next;
        
        Node( const Object & d = Object{ },  Node * n = nullptr )
        : data{ d },  next{ n } { }
        
        Node( Object && d, Node * n = nullptr )
        : data{ std::move( d ) }, next{ n } { }
    };
    
public:
    class iterator
    {
    public:
        
        iterator( ): current( nullptr )
        { }
        
        Object & operator* ( )
        { return current->data; }
        
        const Object & operator* ( ) const
        { return  current->data; }
        
        iterator & operator++ ( )
        {
            this->current = this->current->next;
            return *this;
        }
        
        iterator operator++ ( int )
        {
            iterator old = *this;
            ++( *this );
            return old;
        }
        
        bool operator== ( const iterator & rhs ) const
        { return current == rhs.current; }
        
        bool operator!= ( const iterator & rhs ) const
        { return !( *this == rhs ); }
        
    private:
        Node * current;
        
        iterator( Node *p ) : current{ p }
        { }
        
        friend class List<Object>;
    };
    
public:
    List( )
    { header = new Node; }
    
    ~List( )
    {
        clear( );
        delete header;
    }
    
    List( const List & rhs );
    
    List & operator= ( const List & rhs )
    {
        List copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    List( List && rhs ):header{ new Node }
    {
        header->next = rhs.header->next;
        rhs.header->next = nullptr;
    }
    
    List & operator= ( List && rhs )
    {
        std::swap( header, rhs.header );
        return *this;
    }
    
    iterator begin( ) const
    { return iterator( header->next ); }
    
    iterator end( ) const
    { return iterator( nullptr ); }
    
    iterator before_begin( ) const
    { return iterator( header ); }
    
    bool empty( ) const
    { return header->next == nullptr; }
    
    void clear( )
    {
        while( !empty( ) )
            pop_front( );
    }
    
    void pop_front( )
    { erase_after( before_begin( ) ); }
    
    iterator insert_after( iterator itr, const Object & x )
    {
        Node *p = itr.current;
        p->next = new Node{ x, p->next };
        
        return iterator(p->next);
    }
    
    void remove( const Object & x )
    {
        Node * prev = header;
        
        while ( prev->next != nullptr )
        {
            if ( prev->next->data == x )
                erase_after( iterator(prev) );
            else
                prev = prev->next;
        }
    }
    
    iterator erase_after( iterator itr )
    {
        Node *p = itr.current;
        Node *oldNode = p->next;
        
        p->next = oldNode->next;
        delete oldNode;
        
        return iterator( p->next );
    }
    
    Object & front( );
    
    const Object & front( ) const;
    
    void merge( List & alist );
    
    void reverse( );
    
    void remove_adjacent_duplicate();
    
    template<class Predicate>
    void remove_if( Predicate pred );
    
    iterator insert_after( iterator itr, Object && x );
    
private:
    Node *header;
    
};
template <typename Object>
List<Object>::List( const List & rhs ){
    {
        header = new Node;
        Node *p = header;
        List::iterator itr = rhs.begin();
        for(; itr != rhs.end(); itr++){
            p->next = new Node {*itr, nullptr};
            p = p->next;
        }
    }
}

template <typename Object>
Object& List<Object>::front( ){
    return header->next->data;
}

template <typename Object>
void List<Object>::merge( List & alist ){
    Node *prevAlist = alist.header;
    Node *prev = header;
    while ( prev->next != nullptr ){
        if (prevAlist -> next == nullptr) {
            break;
        }
        while (prev->next->data > prevAlist->next->data) {
            Node *tmp = prevAlist->next;
            prevAlist -> next = prevAlist -> next -> next;
            tmp -> next = prev -> next;
            prev->next = tmp;
            if (prevAlist -> next == nullptr) {
                break;
            }
        }
        prev = prev->next;
    }
    if (!alist.empty()) {
        prev->next = alist.header->next;
        alist.header -> next = nullptr;
    }
}

template <typename Object>
void List<Object>::remove_adjacent_duplicate(){
    Node *current = header -> next;
    while (current != nullptr) {
        while (current->next!= nullptr && current->data == current->next->data ) {
            erase_after(iterator(current));
        }
        current = current->next;
    }
}

template <typename Object>
typename List<Object>::iterator List<Object>::insert_after( iterator itr, Object && x ){
    Node *p = itr.current;
    p->next = new Node{ move(x), p->next };
    
    return iterator(p->next);
};

bool single_digit (const int& value) { return (value<10); }

template <typename Object>
template <class Predicate>
void List<Object>::remove_if( Predicate pred ){
    Node *prev = header;
    while (prev->next != nullptr) {
        if (pred(prev->next->data)) {
            erase_after(iterator(prev));
        }
        else{
            prev = prev -> next;
        }
    }
};

//----------- Question 2 --------------
//Implement the following methdos front, back, empty, enqueue, dequeue.

template <typename Object>
class Queue
{
private:
    
    struct Node
    {
        Object  data;
        Node   *next;
        
        Node( const Object & d = Object{ },  Node * n = nullptr )
        : data{ d },  next{ n } { }
        
        Node( Object && d, Node * n = nullptr )
        : data{ std::move( d ) }, next{ n } { }
    };
    
public:
    Queue(){
        frontOfQueue = nullptr;
        backOfQueue = nullptr;
    }
    
    Object& front();
    Object& back();
    void enqueue(Object& x);
    void dequeue();
    
    
private:
    Node *frontOfQueue;
    Node *backOfQueue;
    
};

template <typename Object>
Object& Queue<Object>::front(){
    return frontOfQueue->data;
}

template <typename Object>
Object& Queue<Object>::back(){
    return backOfQueue->data;
}

template <typename Object>
void Queue<Object>::enqueue(Object& x){
    Node *tmp = new Node{x,nullptr};
    if (frontOfQueue == nullptr) {
        frontOfQueue = tmp;
    }
    else{
        backOfQueue->next = tmp;
    }
    backOfQueue = tmp;
}

template <typename Object>
void Queue<Object>::dequeue(){
    Node *tmp = frontOfQueue;
    frontOfQueue = frontOfQueue->next;
    delete tmp;
}

//------Extra Credit -----//

// Code simplified from Weiss's doubly linked list class.  This code was less modular than I would have liked because I wanted you to write more code.
template <typename Object>
class DList
{
private:
    // The basic doubly linked list node.
    // Nested inside of List, can be public
    // because the Node is itself private
    struct Node
    {
        Object  data;
        Node   *prev;
        Node   *next;
        
        Node( const Object & d = Object{ }, Node * p = nullptr, Node * n = nullptr )
        : data{ d }, prev{ p }, next{ n } { }
        
        Node( Object && d, Node * p = nullptr, Node * n = nullptr )
        : data{ std::move( d ) }, prev{ p }, next{ n } { }
    };
    
    class iterator
    {
    public:
        
        iterator( ):current(nullptr)
        { }
        
        Object & operator* ( )
        { return current->data; }
        
        iterator & operator++ ( )
        {
            this->current = this->current->next;
            return *this;
        }
        
        iterator operator++ ( int )
        {
            iterator old = *this;
            ++( *this );
            return old;
        }
        
        iterator & operator-- ( )
        {
            this->current = this->current->prev;
            return *this;
        }
        
        iterator operator-- ( int )
        {
            iterator old = *this;
            --( *this );
            return old;
        }
        
    private:
        Node *current;
        // Protected constructor for iterator.
        // Expects the current position.
        iterator( Node *p ) : current{ p }
        { }
        
        friend class DList<Object>;
    };
    
public:
    DList( )
    { init( ); }
    
    ~DList( )
    {
        clear( );
        delete head;
        delete tail;
    }
    
    // Return iterator representing beginning of list.
    iterator begin( )
    { return iterator( head->next ); }
    
    
    // Return iterator representing endmarker of list.
    iterator end( )
    { return iterator( tail ); }
    
    // Return number of elements currently in the list.
    int size( ) const
    { return theSize; }
    
    // Return true if the list is empty, false otherwise.
    bool empty( ) const
    { return size( ) == 0; }
    
    void clear( )
    {
        while( !empty( ) )
        {
            Node* deleteNode = head->next;
            head->next = deleteNode->next;
            deleteNode->next->prev = head;
            --theSize;
        }
    }
    
    // front, back, push_front, push_back, pop_front, and pop_back
    // are the basic double-ended queue operations.
    Object & front( )
    { return *begin( ); }
    
    const Object & front( ) const
    { return *begin( ); }
    
    Object & back( )
    { return *--end( ); }
    
    const Object & back( ) const
    { return *--end( ); }
    
    void push_front( const Object & x )
    { insert( begin( ), x ); }
    
    void push_back( const Object & x )
    { insert( end( ), x ); }
    
    void push_front( Object && x )
    { insert( begin( ), std::move( x ) ); }
    
    void push_back( Object && x )
    { insert( end( ), std::move( x ) ); }
    
    // Insert x before itr.
    iterator insert( iterator itr, const Object & x )
    {
        Node *p = itr.current;
        ++theSize;
        return iterator( p->prev = p->prev->next = new Node{ x, p->prev, p } );
    }
    
    // Insert x before itr.
    iterator insert( iterator itr, Object && x )
    {
        Node *p = itr.current;
        ++theSize;
        return iterator( p->prev = p->prev->next = new Node{ std::move( x ), p->prev, p } );
    }
    void remove(const Object & x);
    
private:
    int   theSize;
    Node *head;
    Node *tail;
    
    void init( )
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};

template<class Object>
void DList<Object>::remove(const Object & x){
    Node * prev = head;
    while ( prev->next != tail )
    {
        if ( prev->next->data == x ){
            Node *oldNode = prev -> next;
            prev -> next = oldNode -> next;
            delete oldNode;
            --theSize;
        }
        else
            prev = prev->next;
    }
}


int main( int argc, const char * argv[] ) {
    List<int> linkedList;
    List<int>::iterator theItr = linkedList.before_begin();
    int i;
    for (i = 0; i < 12; i++) {
        linkedList.insert_after(theItr, i);
        theItr++;
    }
    
    for (i = 0; i < 4; i++) {
        linkedList.insert_after(theItr, i);
        theItr++;
    }
    
    List<int> copyList(linkedList);
    
    for (List<int>::iterator copyItr = copyList.begin(); copyItr != copyList.end(); copyItr++) {
        cout << *copyItr << endl;
    }
    
    linkedList.front() = 12;
    
    cout<< linkedList.front()<< endl;
    
    linkedList.merge(copyList);
    linkedList.remove_adjacent_duplicate();
    
    cout<< "removed"<<endl;
    
    cout<< "removed single" << endl;
    
    linkedList.remove_if(single_digit);
    
    for (List<int>::iterator Itr = linkedList.begin(); Itr != linkedList.end(); Itr++) {
        cout << *Itr << endl;
    }
    
    Queue<int> testQueue;
    for (int i = 0; i < 10; i++) {
        testQueue.enqueue(i);
    }
    cout << testQueue.front();
    
    cout << testQueue.back();
    
    testQueue.dequeue();
    
    cout<< testQueue.front();
    
    cout<<testQueue.back();
    
    DList<int> testDoubleList;
    
    for (int i = 0; i < 10; i++) {
        testDoubleList.push_back(i);
    }
    
    testDoubleList.remove(5);

}

