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
  List<T> (const List<T>& l);

  //EFFECTS:  returns true if the list is empty
  bool empty() const{
    if(first == nullptr && last == nullptr)
      return true;
    return false;   
  }

  //EFFECTS: returns the number of elements in this List
  int size() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front();

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    return last->datum; 
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum);

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    //Populate data in end node
    Node *added = new Node;
    added->datum = datum;
    added->next = nullptr;
    added->prev = last;

    //Set next node of current end to be new end
    last->next = added;

    //Set end to be the new node
    last = added;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    Node *newEnd =  last->prev;
    newEnd->next = nullptr;
    delete last;
    last = newEnd;
  };

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){
    Node *ptr = last;
    while(ptr->prev != nullptr) {
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

    //Operator +
    Iterator& operator +(int i) {
      for(int j = 0; j < i; j++){
        ++this;
      }
      return this;
    }

    //Operator ==
    bool operator ==(const Iterator& i) const;

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
    return Iterator(last);
  };

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){
    Node *victim = i.node_ptr;
    (victim->prev)->next = (victim->next);
    (victim->next)->prev = (victim->prev);
    delete victim;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum);

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
