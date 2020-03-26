#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //Default Constructor
  List() {
    first = nullptr;
    last = nullptr;
  }

  //Destructor
  ~List() {
    clear();
  }

  //Copy Constructor
  //EFFECTS creates list, itterates through old list and pushes back
  //all data in old list onto new list, which creates new nodes
  //Not sure that the <T> is necessary tbh, but I think it prevents
  //copying of two lists that aren't the same type
    List<T> (const List<T>& l) {
        first = nullptr;
        last = nullptr;
        push_all(l);
        
    }
    List & operator=(const List &rhs) {
        if(this == &rhs) {
            return *this;
        }
        clear();
        first = nullptr;
        last = nullptr;
        push_all(rhs);
        
        return *this;
    }
    

  //EFFECTS:  returns true if the list is empty
  bool empty() const{
    if(size() != 0)
      return false;
    return true;   
  }

  //EFFECTS: returns the number of elements in this List
    int size() const {
        int count = 0;
        for(Iterator it = this->begin(); it != this->end(); ++it) {
            ++count;
        }
        return count;
    }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
    T & front() {
        return first->datum;
    }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    return last->datum; 
  }

  //EFFECTS:  inserts datum into the front of the list
    void push_front(const T &datum) {
        if(empty()) {
            Node *added = new Node;
            added->datum = datum;
            added->next = nullptr;
            added->prev = nullptr;
            first = added;
            last = added;
            return;
        }
        //Creates node with data in it
        Node *added = new Node;
        added->datum = datum;
        
        added->prev = nullptr;
        added->next = first;
        first->prev = added;
        first = added;
        
    }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    //Populate data in end node
    Node *added = new Node;
    added->datum = datum;
    added->next = nullptr;
    added->prev = last;
    
    if(empty())
      first = added;

    //Set next node of current end to be new end only if pointer isn't null
    if(last)
      last->next = added;

    //Set end to be the new node
    last = added;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
    void pop_front() {
        if(size() == 1) {
            delete first;
            first = nullptr;
            last = nullptr;
            return;
        }
        Iterator it = begin();
        Iterator second = ++it;
        Node *secondNode = second.node_ptr;
        delete first;
        first = secondNode;
        secondNode->prev = nullptr;
    }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    if(last->prev){
      Node *newEnd =  last->prev;
      newEnd->next = nullptr;
      delete last;
      last = newEnd;
    }
    else{
      delete last;
      last = nullptr;
        first = nullptr;
    }
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){
    Node *ptr = last;
    while(ptr) {
      pop_back();
      ptr = last;
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
    
    //added function to help in copy and assignment
    void push_all(const List<T> &other) {
        for(Node *np = other.first; np; np = np->next) {
            push_back(np->datum);
        }
    }
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other);

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
      Iterator() {
          node_ptr = nullptr;
      }
      Iterator& operator --() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

  //Probably won't use these since no api, but just added them for fun
    //Operator++
    Iterator& operator ++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    //Operator*
    T & operator *() {
      assert(node_ptr);
      return node_ptr->datum;
    }


    //Operator ==
    bool operator ==(const Iterator& i) const{
      if(node_ptr == i.node_ptr)
        return true;
      return false;
    }

    //Operator !=
    bool operator != (const Iterator& i) const{
      if(node_ptr != i.node_ptr)
        return true;
      return false;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;
    // construct an Iterator at a specific position
    Iterator(Node *p){
      node_ptr = p;
    }

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator(nullptr);
  };

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){
      assert(*i);
    Node *victim = i.node_ptr;
    
    //Check to see if it's the first or last element
    bool front = false;
    bool end = false;
    
//      if(this->end() == i) {
//          end = true;
//      }
//      if(this->begin() == i) {
//          front = true;
//      }
    if(!victim->prev)
      front = true;
    if(!victim->next)
      end = true;

    //If it isn't first and last
    if(!front && !end){
      (victim->prev)->next = (victim->next);
      (victim->next)->prev = (victim->prev);
    }
    //If it is first but not last
    else if(front && !end) {
      (victim->next)->prev = nullptr;
      first = victim->next;
    }
    //If it is last but not first
    else if(!front && end) {
      (victim->prev)->next = nullptr;
      last = victim->next;
    }
    //If it is the last element
    else {
      first = nullptr;
      last = nullptr;
    }
  
    delete victim;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
    void insert(Iterator i, const T &datum) {
        //Empty list
        if(size() == 0) {
            push_back(datum);
            return;
        }
        //Iterator at end
        if(i == end()) {
            push_back(datum);
            return;
        }
        //Iterator is first element
        if(i == begin()) {
            push_front(datum);
            return;
        }
        //Creates new Node in List and initializes its values
        Node *second = i.node_ptr;
        Node *first = ((--i).node_ptr);
        
        
        Node *newNode = new Node;
        newNode->datum = datum;
        newNode->next = second;
        newNode->prev = first;
        
        //Changes next and previous Nodes pointers
        first->next = newNode;
        second->prev = newNode;
        
    }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.
