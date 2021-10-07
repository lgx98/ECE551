#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * suffix = ".counts";
  size_t len = strlen(inputName) + strlen(suffix) + 1;
  char * outputName = malloc(len * sizeof(*outputName));
  memcpy(outputName, inputName, strlen(inputName));
  memcpy(outputName + strlen(inputName), suffix, strlen(suffix) + 1);
  return outputName;
}
