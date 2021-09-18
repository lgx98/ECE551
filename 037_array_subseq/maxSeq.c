#include <stdlib.h>
size_t maxSeq(int * array, size_t n) {
  if (n <= 1)  // n==0 or n==1
    return n;
  size_t maxLen = 0;
  // lptr points to the start of the sequence
  // rptr points to the next possible position
  int * lptr = array;
  int * rptr = array + 1;
  while (rptr < (array + n)) {
    if (*rptr > *(rptr - 1)) {
      rptr++;
    }
    else {
      maxLen = ((rptr - lptr) > maxLen) ? (rptr - lptr) : maxLen;
      lptr = rptr;
      rptr++;
    }
  }
  maxLen = ((rptr - lptr) > maxLen) ? (rptr - lptr) : maxLen;
  return maxLen;
}
