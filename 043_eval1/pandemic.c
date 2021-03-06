#include "pandemic.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

// macro to enable printf debugging
//#define PRTDBG 1

// print the error message to stderr, then exit with failure.
void error(const char * msg) {
  fprintf(stderr, "Error: %s, Exiting!\n", msg);
  exit(EXIT_FAILURE);
}

// takes a null-terminating string, parse a string and a unsigned number seperated by ','.
country_t parseLine(char * line) {
#ifdef PRTDBG
  for (size_t i = 0; i < 80; ++i)
    putchar('=');
  printf("\nTesting Following Line:\n%s", line);
#endif

  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  // Sanity checks:
  // line should not be a NULL pointer.
  if (line == NULL)
    error("NULL Input: line");

  // If line is empty, this should be invalid
  if ((*line) == '\0')
    error("Empty Input");

  // Parse the country name.
  size_t i = 0;
  while (*(line + i) != ',') {
#ifdef PRTDBG
    printf("char@%02ld: %c\n", i, line[i]);
#endif

    // if the string is terminating without a ',', it is incomplete.
    if (*(line + i) == '\0')
      error("Line Incomplete, Missing ','");
    // if the name has 64 chars already, no space for trailing '\0'.
    if (i == 63)
      error("Country Name Too Long(>63 chars)");
    ans.name[i] = *(line + i);
    ++i;
  }

  // Empty country name is VALID
  //if (i == 1)
  //  error("Empty Country Name");

  // Append null char to ans.name.
  ans.name[i] = '\0';
  // At this time, *(line + i) should be pointing at char ',', so move it number section.
  line += (i + 1);

  char * endptr = NULL;
  // Parse the number.
  uint64_t num = strtoull(line, &endptr, 10);
  if (errno == ERANGE)
    error("Number Out of Range");

  // The following errno will not be set by trtoull in C99
  //if (errno_backup == EINVAL)
  //  error("No Number Found");

  // So if the result is 0, but last valid char is not '0', the number is missing.
  if (num == 0 && *(endptr - 1) != '0')
    error("No Number Found");

  ans.population = num;

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  const size_t period = 7;

  // Sanity checks:
  // data should not be a NULL pointer.
  if (data == NULL)
    error("NULL Input: data");

  // The right behavior should be quitting without doing anything.
  // n_days should be at least 7.
  if (n_days < period)
    return;
  //  error("Data Length Less Than Averging Period");

  // avg should not be a NULL pointer.
  if (data == NULL)
    error("NULL Input: avg");

  // Not the fastest solution, but very straightforward.
  for (size_t i = 0; i < n_days - (period - 1); ++i) {
    // This should prevent any overflow.
    uint64_t sum = 0;
    for (size_t j = 0; j < period; ++j) {
      sum += *(data + i + j);
    }
    *(avg + i) = (double)sum / (double)period;
  }

  return;
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  // Sanity checks:
  // data should not be a NULL pointer.
  if (data == NULL)
    error("NULL Input: data");

  // cum should not be a NULL pointer.
  if (cum == NULL)
    error("NULL Input: cum");

  uint64_t sum = 0;

  // If n_days==0, it will not enter the loop, and return without doing anything.
  for (size_t i = 0; i < n_days; ++i) {
    sum += *(data + i);
    *(cum + i) = (double)sum * 1e5 / pop;
  }

  return;
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  // Sanity checks:
  // countries should not be a NULL pointer.
  if (countries == NULL)
    error("NULL pointer: countries");

  // data should not be a NULL pointer.
  if (data == NULL)
    error("NULL pointer: data");

  // n_countries should not be 0, if that happens, return whitout doing anything
  if (n_countries == 0)
    return;

  // new feature in C99
  unsigned max_cases[n_countries];
  // Initialize the array with 0.
  for (size_t i = 0; i < n_countries; ++i)
    max_cases[i] = 0;

  // Find the most daily cases for every country.
  for (size_t j = 0; j < n_days; ++j) {
    for (size_t i = 0; i < n_countries; ++i) {
      max_cases[i] = data[i][j] > max_cases[i] ? data[i][j] : max_cases[i];
    }
  }

  // Find the country with most cases.
  size_t max_i = 0;
  bool tie = 0;
  for (size_t i = 1; i < n_countries; ++i) {
    // If there is another country that has the same cases, set tie to 1
    tie |= (max_cases[i] == max_cases[max_i]);
    if (max_cases[i] > max_cases[max_i]) {
      max_i = i;
      tie = 0;
    }
  }

  if (tie)
    printf("There is a tie between at least two countries\n");
  else
    printf(
        "%s has the most daily cases with %u\n", countries[max_i].name, max_cases[max_i]);

  return;
}
