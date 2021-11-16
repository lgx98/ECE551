#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (this->sym != NO_SYM) {
    assert((this->left == NULL) && (this->right == NULL));
    theMap.insert(std::pair<unsigned, BitString>(this->sym, b));
  }
  else {
    assert((this->left != NULL) && (this->right != NULL));
    this->left->buildMap(b.plusZero(), theMap);
    this->right->buildMap(b.plusOne(), theMap);
  }
}
