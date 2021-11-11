#ifndef __BSET_H__
#define __BSET_H__
#include "bstmap.h"
#include "set.h"
template<typename K>
class BstSet : public Set<K> {
 private:
  BstMap<K, bool> map;

 public:
  void add(const K & key) { map.add(key, true); }
  bool contains(const K & key) const {
    try {
      map.lookup(key);
    }
    catch (const std::invalid_argument & e) {
      return false;
    }
    return true;
  }
  void remove(const K & key) { map.remove(key); }
};
#endif
