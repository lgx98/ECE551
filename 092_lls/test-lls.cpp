#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.hpp"

typedef LinkedList<int> IntList;

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    IntList dut;

    // First addFront
    dut.addFront(1);
    IntList::Node * N1 = dut.head;
    // Check list
    assert(dut.head != NULL);
    assert(dut.tail == dut.head);
    assert(dut.getSize() == 1);
    assert(dut[0] == 1);
    // Check N1
    assert(N1->data == 1);
    assert(N1->next == NULL);
    assert(N1->prev == NULL);

    // Second addFront
    dut.addFront(2);
    IntList::Node * N2 = dut.head;
    // Check list
    assert(dut.head != NULL);
    assert(dut.tail == N1);
    assert(dut.getSize() == 2);
    assert(dut[0] == 2);
    assert(dut[1] == 1);
    // Check N1
    assert(N1->data == 1);
    assert(N1->next == NULL);
    assert(N1->prev == N2);
    // Check N2
    assert(N2->data == 2);
    assert(N2->next == N1);
    assert(N2->prev == NULL);
  }

  void testAddBack() {
    IntList dut;
    // First addBack
    dut.addBack(1);
    IntList::Node * N1 = dut.tail;
    // Check list
    assert(dut.head != NULL);
    assert(dut.tail == dut.head);
    assert(dut.getSize() == 1);
    assert(dut[0] == 1);
    // Check N1
    assert(N1->data == 1);
    assert(N1->next == NULL);
    assert(N1->prev == NULL);

    // Second addBack
    dut.addBack(2);
    IntList::Node * N2 = dut.tail;
    // Check list
    assert(dut.head == N1);
    assert(dut.tail != NULL);
    assert(dut.getSize() == 2);
    assert(dut[0] == 1);
    assert(dut[1] == 2);
    // Check N1
    assert(N1->data == 1);
    assert(N1->next == N2);
    assert(N1->prev == NULL);
    // Check N2
    assert(N2->data == 2);
    assert(N2->next == NULL);
    assert(N2->prev == N1);

    // Third addFront
    dut.addFront(3);
    IntList::Node * N3 = dut.head;
    // Check list
    assert(dut.head != NULL);
    assert(dut.tail == N2);
    assert(dut.getSize() == 3);
    assert(dut[0] == 3);
    assert(dut[1] == 1);
    assert(dut[2] == 2);
    // Check N1
    assert(N1->data == 1);
    assert(N1->next == N2);
    assert(N1->prev == N3);
    // Check N2
    assert(N2->data == 2);
    assert(N2->next == NULL);
    assert(N2->prev == N1);
    // Check N3
    assert(N3->data == 3);
    assert(N3->next == N1);
    assert(N3->prev == NULL);
  }

  void testCopy() {
    IntList * dut1 = new IntList();
    dut1->addFront(1);
    IntList * dut2 = new IntList(*dut1);
    assert(dut1->head != dut2->head);
    assert(dut1->tail != dut2->tail);
    delete dut2;
    dut1->addBack(2);
    IntList * dut3 = new IntList(*dut1);
    delete dut1;
    dut3->remove(1);
    delete dut3;
  }

  void testAssign() {
    IntList * dut1 = new IntList();
    dut1->addBack(1);
    dut1->addBack(2);
    IntList * dut2 = new IntList();
    dut2->addFront(1);
    dut2->addFront(2);
    dut2->addFront(3);
    *dut2 = *dut1;
    assert(dut2->getSize() == 2);
    assert(dut1->head != dut2->head);
    assert(dut1->tail != dut2->tail);
    assert(dut2->tail->next == NULL);
    delete dut1;
    delete dut2;
  }

  void testRemove() {
    IntList dut;
    /* First addBack
     * ht
     *  1
     */
    dut.addBack(1);
    IntList::Node * N1 = dut.tail;
    /* Second addBack
     *  h t
     *  1 2
     */
    dut.addBack(2);
    /* Third addBack
     *  h   t
     *  1 2 3
     */
    dut.addBack(3);
    IntList::Node * N3 = dut.tail;
    /* Third addBack
     *  h     t
     *  1 2 3 2
     */
    dut.addBack(2);
    IntList::Node * N2 = dut.tail;

    // Zeroth invalid remove
    assert(dut.remove(0) == false);

    /* First remove
     *  h   t
     *  1 3 2
     */
    assert(dut.remove(2) == true);
    // Check list
    assert(dut.head == N1);
    assert(dut.tail == N2);
    assert(dut.getSize() == 3);
    assert(dut[0] == 1);
    assert(dut[1] == 3);
    assert(dut[2] == 2);
    // Check N1
    assert(N1->data == 1);
    assert(N1->next == N3);
    assert(N1->prev == NULL);
    // Check N2
    assert(N2->data == 2);
    assert(N2->next == NULL);
    assert(N2->prev == N3);
    // Check N3
    assert(N3->data == 3);
    assert(N3->next == N2);
    assert(N3->prev == N1);

    /* Second remove
     *  h t
     *  1 3
     */
    assert(dut.remove(2) == true);
    // Check list
    assert(dut.head == N1);
    assert(dut.tail == N3);
    assert(dut.getSize() == 2);
    assert(dut[0] == 1);
    assert(dut[1] == 3);
    // Check N1
    assert(N1->data == 1);
    assert(N1->next == N3);
    assert(N1->prev == NULL);
    // Check N3
    assert(N3->data == 3);
    assert(N3->next == NULL);
    assert(N3->prev == N1);

    /* Third remove
     * ht
     *  3
     */
    assert(dut.remove(1) == true);
    // Check list
    assert(dut.head == N3);
    assert(dut.tail == N3);
    assert(dut.getSize() == 1);
    assert(dut[0] == 3);
    // Check N3
    assert(N3->data == 3);
    assert(N3->next == NULL);
    assert(N3->prev == NULL);

    // Fourth remove
    assert(dut.remove(3) == true);
    // Check list
    assert(dut.head == NULL);
    assert(dut.tail == NULL);
    assert(dut.getSize() == 0);

    assert(dut.remove(1) == false);
  }
  // many more tester methods
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopy();
  t.testAssign();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
