#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int main(void)
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

