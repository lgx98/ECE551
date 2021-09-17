#include <stdio.h>
#include <stdlib.h>
extern size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t expected_ans) {
  if (maxSeq(array, n) == expected_ans)
    return;
  exit(EXIT_FAILURE);
  return;
}

int main(void) {
  int arr0[] = {1, 1, 1, 1, 1};
  int arr1[] = {0, 0, 1, 1, 0};
  int arr2[] = {1, 2, 3};
  int arr3[] = {0};
  int * arr4 = NULL;
  int arr5[] = {-2147483648, 2147483647};
  run_check(arr0, 5, 1);
  run_check(arr1, 5, 2);
  run_check(arr2, 3, 3);
  run_check(arr3, 1, 1);
  run_check(arr4, 0, 0);
  run_check(arr5, 2, 2);
  return EXIT_SUCCESS;
}
