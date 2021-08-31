#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Age  27 month  3 you have $21345.00
Age  27 month  4 you have $22425.04
Age  27 month  5 you have $23509.14
Age  27 month  6 you have $24597.30
Age  27 month  7 you have $25689.54
Age  27 month  8 you have $26785.87
Age  27 month  9 you have $27886.32
Age  27 month 10 you have $28990.89
Age  27 month 11 you have $30099.61
Age  28 month  0 you have $31212.48
*/
typedef struct _retire_info
{
  int months;
  double contribution;
  double rate_of_return;
} retire_info;

static inline bool printAndUpdate(
    int *age,
    double *balance,
    retire_info *info)
{
  if (info->months == 0)
    return false;
  printf("Age %3d month %2d you have $%.2lf\n",
         (*age) / 12, (*age) % 12, (*balance));
  (*balance) = (*balance) * (1 + info->rate_of_return) + info->contribution;
  (*age)++;
  (info->months)--;
  return true;
}

void retirement(
    int startAge,
    double initial,
    retire_info working,
    retire_info retired)
{
  while (printAndUpdate(&startAge, &initial, &working))
    ;
  while (printAndUpdate(&startAge, &initial, &retired))
    ;
}

int main(int argc, char const *argv[])
{
  int age = 327;
  float balance = 21345.0;
  retire_info working = {
      .months = 489,
      .contribution = 1000,
      .rate_of_return = 0.045 / 12};
  retire_info retired = {
      .months = 384,
      .contribution = -4000,
      .rate_of_return = 0.01 / 12};
  retirement(age, balance, working, retired);
  return EXIT_SUCCESS;
}

