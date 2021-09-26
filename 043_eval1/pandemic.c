#include "pandemic.h"

#include "stdio.h"

// print the error message to stderr, then exit with failure.
void error(const char * msg) {
  fprintf(stderr, "Error: %s, Exiting!\n", msg);
  exit(EXIT_FAILURE);
}

// takes a null-terminating string, parse a string and a unsigned number seperated by ','.
country_t parseLine(char * line) {
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  // Sanity checks:
  // line should not be a NULL pointer.
  if (line == NULL)
    error("NULL Input: line");

  // If line is empty, this should be invalid?
  if ((*line) == '\0')
    error("Empty Input");

  // Parse the country name.
  size_t i = 0;
  while (*(line + i) != ',') {
    // if the string is terminated without a ',', it is incomplete.
    if (*(line + i) == '\0')
      error("Line Incomplete, Missing ','");
    // if the name has 64 chars already, no space for trailing '\0'.
    if (i == 63)
      error("Country Name Too Long(>63 chars)");
    ans.name[i] = *(line + i);
    ++i;
  }
  // Empty country name is invalid
  if (i == 1)
    error("Empty Country Name");
  ans.name[i] = '\0';
  // At this time, *(line + i) should be pointing at char ',', so move it number section.
  line += (i + 1);

  // Parse the number.
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  const size_t period = 7;

  // Sanity checks:
  // data should not be a NULL pointer.
  if (data == NULL)
    error("NULL Input: data");
  // n_days should be at least 7.
  if (n_days < period)
    error("Data Length Less Than Averging Period");
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
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  uint64_t sum = 0;

  // Sanity checks:
  // data should not be a NULL pointer.
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
