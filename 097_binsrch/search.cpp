#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  // base case: only 1 possible number
  if (low + 1 >= high) {
    return low;
  }
  int mid = (low + high) >> 1;
  int f_mid = f->invoke(mid);
  if (f_mid > 0) {
    return binarySearchForZero(f, low, mid);
  }
  else if (f_mid < 0) {
    return binarySearchForZero(f, mid, high);
  }
  else {
    return mid;
  }
}
