#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "function.h"

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int n = log2(high - low) + 2;
  CountedIntFn f_count(n, f, mesg);
  int ans = binarySearchForZero(&f_count, low, high);
  if (expected_ans != ans) {
    printf("ans: %d, exp: %d\n", ans, expected_ans);
    fprintf(stderr, "Falied with %s\n", mesg);
    exit(EXIT_FAILURE);
  }
}

class Function_identity : public Function<int, int> {
 public:
  int invoke(int arg) { return arg; }
};

class Function_lin : public Function<int, int> {
 public:
  int invoke(int arg) { return arg - 10; }
};

int main(void) {
  Function_lin myfunc;
  check(&myfunc, -8192, -4098, -4099, "all negative\n");
  check(&myfunc, 4096, 8191, 4096, "all positive\n");
  check(&myfunc, 1, 8191, 10, "inclusive zero\n");
  check(&myfunc, -8191, 0, -1, "exclusive zero\n");
  check(&myfunc, 0, 8191, 10, "normal\n");
  srand((unsigned)time(0));
  while (0) {
    int x = rand();
    int y = rand();
    if (x > y) {
      int temp = y;
      y = x;
      x = temp;
    }
    int ans = 0;
    if (x > 0)
      ans = x;
    if (y <= 0)
      ans = y - 1;
    //if (((~(x + y) & x & y) | ((x + y) & ~x & ~y)) & (1 << 31))
    //  continue;
    char buffer[50];
    sprintf(buffer, "rand: %d, %d\n", x, y);
    check(&myfunc, x, y, ans, buffer);
  }
  return EXIT_SUCCESS;
}
