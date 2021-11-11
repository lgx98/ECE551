#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V val;
    Node * lNode;
    Node * rNode;
    Node() : lNode(NULL), rNode(NULL) {}
    Node(K key, V val) : key(key), val(val), lNode(NULL), rNode(NULL) {}
    ~Node() {}
    friend std::ostream & operator<<(std::ostream & s, const Node & rhs) {
      s << "<" << rhs.key << ": " << rhs.val << ">";
      return s;
    }
  };
  Node * root;
  static void tree_assign(Node *& lhs, const Node * const rhs) {
    // with branch prediction, there would not be too much overhead
    // when using this function as copy constructor or destructor
    if (rhs == NULL) {
      if (lhs == NULL) {
        // Base case: both sides are NULL.
        return;
      }
      else {
        // LHS is not NULL, but RHS is: delete LHS.
        tree_assign(lhs->lNode, NULL);
        tree_assign(lhs->rNode, NULL);
        delete lhs;
        lhs = NULL;
      }
    }
    else {
      if (lhs == NULL) {
        // LHS is NULL, but RHS is not: make a new LHS.
        lhs = new Node(rhs->key, rhs->val);
        tree_assign(lhs->lNode, rhs->lNode);
        tree_assign(lhs->rNode, rhs->rNode);
      }
      else {
        // Both sides are not NULL: assign the k v pair directly.
        lhs->key = rhs->key;
        lhs->val = rhs->val;
        tree_assign(lhs->lNode, rhs->lNode);
        tree_assign(lhs->rNode, rhs->rNode);
      }
    }
  }

  static Node * const & tree_search(Node * const & root, const K key) {
    if (root == NULL) {
      // Base case: not found, return the place where the key should be added
      return root;
    }
    if (key < root->key) {
      return tree_search(root->lNode, key);
    }
    else if (key > root->key) {
      return tree_search(root->rNode, key);
    }
    else {
      return root;
    }
  }

  static Node *& tree_search(Node *& root, const K key) {
    return const_cast<Node *&>(tree_search(const_cast<Node * const &>(root), key));
  }

  static void tree_print(std::ostream & s, const Node * const root, int depth = 0) {
    if (root == NULL)
      return;
    tree_print(s, root->lNode, depth + 1);
    for (int i = 0; i < depth; ++i) {
      s << "        ";
    }
    s << (*root) << std::endl;
    //tree_print(s, root->lNode, depth + 1);
    tree_print(s, root->rNode, depth + 1);
    return;
  }

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs) : root(NULL) { tree_assign(this->root, rhs.root); }
  BstMap & operator=(const BstMap & rhs) {
    tree_assign(this->root, rhs.root);
    return *this;
  }
  ~BstMap() { tree_assign(this->root, NULL); }

  void add(const K & key, const V & value) {
    Node *& n_insert = tree_search(this->root, key);
    if (n_insert == NULL) {
      n_insert = new Node(key, value);
    }
    else {
      n_insert->val = value;
    }
    return;
  }
  const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * const & n_found = tree_search(this->root, key);
    if (n_found == NULL) {
      throw std::invalid_argument("key not find\n");
    }
    return n_found->val;
  }
  void remove(const K & key) {
    Node *& n_found = tree_search(this->root, key);
    if (n_found == NULL) {
      throw std::invalid_argument("key not find\n");
    }
    if (n_found->lNode == NULL) {
      Node * temp = n_found->rNode;
      delete n_found;
      n_found = temp;
    }
    else if (n_found->rNode == NULL) {
      Node * temp = n_found->lNode;
      delete n_found;
      n_found = temp;
    }
    else {
      Node * findnode = n_found->lNode;
      while (findnode->rNode != NULL) {
        findnode = findnode->rNode;
      }
      K tempkey = findnode->key;
      remove(findnode->key);
      n_found->key = tempkey;
      return;
    }
  }
  friend std::ostream & operator<<(std::ostream & s, const BstMap & rhs) {
    tree_print(s, rhs.root);
    return s;
  }
};

#endif
