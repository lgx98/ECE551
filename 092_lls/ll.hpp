#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#define NDEBUG
#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE

class itemNotExistException : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "The requested item does not exist\n";
  }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(const T & data) : data(data), next(NULL), prev(NULL){};
    Node(const T & data, Node * next, Node * prev) : data(data), next(next), prev(prev){};
  };

  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0){};

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * s = rhs.head;
    while (s != NULL) {
      addBack(s->data);
      s = s->next;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList tmp(rhs);
      Node * original_head = head;
      head = tmp.head;
      tmp.head = original_head;
      Node * original_tail = tail;
      tail = tmp.tail;
      tmp.tail = original_tail;
      size = tmp.size;
    }
    return *this;
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }

  int getSize() const { return size; }

  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (size == 0) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }

  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (size == 0) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }

  bool remove(const T & item) {
    Node ** curr = &head;
    for (int i = 0; *curr != NULL && (*curr)->data != item; i++) {
      curr = &(*curr)->next;
      assert(i < this->size);  //In case of loop or unterminated tail.
    }

    //item not found
    if (*curr == NULL) {
      return false;
    }

    Node * rmNode = *curr;
    // Reconnect: forward direction
    *curr = rmNode->next;
    // Reconnect: backward direction
    if (rmNode->next != NULL) {
      rmNode->next->prev = rmNode->prev;
    }
    // Edge case: update this->tail
    if (this->tail == rmNode) {
      this->tail = rmNode->prev;
    }
    delete rmNode;
    this->size--;
    return true;
  }

  T & operator[](int index) {
    if (index < 0 && index >= size) {
      //throw new itemNotExistException();
    }
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      assert(curr != NULL);
      curr = curr->next;
    }
    return curr->data;
  }

  const T & operator[](int index) const {
    if (index < 0 && index >= size) {
      //throw new itemNotExistException();
    }
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      assert(curr != NULL);
      curr = curr->next;
    }
    return curr->data;
  }

  int find(const T & item) const {
    Node * p = head;
    for (int i = 0; p != NULL; i++) {
      if (p->data == item) {
        return i;
      }
      p = p->next;
    }
    return -1;
  }
  //friend class Tester;
};
#endif
