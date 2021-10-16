#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "provided.h"

//any functions you want your main to use

// Basic operations on category and catarray
void category_erase(category_t * cat, char * word);

category_t * catarray_find(catarray_t * cat, const char * name);

// Definition and basic operations on token
// Inspired by the definition of Lua TValue.
//(I learned the code even before coming to Durham, so no academic misconduct.)
typedef enum _tokenType_t {
  STRING,    // plain string
  CATEGORY,  // category name of a blank
  NUMBER     // an integer that decides which previous word should be used
} tokenType_t;

typedef union _tokenValue_t {
  char * str;
  char * name;
  size_t num;
} tokenValue_t;

typedef struct _token_t {
  tokenType_t type;
  tokenValue_t value;
} token_t;

token_t * token_new(const tokenType_t type);

void token_delete(token_t * token);

// Definition and basic operations on token array
typedef struct _tokenArr_t {
  token_t ** tokens;
  size_t n_tokens;
  size_t n_avail;  // actual size, grows by 2 each time.
} tokenArr_t;

tokenArr_t * tokenArr_new(void);

void tokenArr_delete(tokenArr_t * arr);

void tokenArr_push_back(tokenArr_t * arr, token_t * token);

// Sub-tasks needed in the 4 steps
catarray_t * parseCat(FILE * f);

void parseLine(const char * line, tokenArr_t * arr);

typedef enum _stroyOption_t { ALWAYS_CAT = 0x01, NO_REUSE = 0x02 } storyOption_t;

void tellStory(FILE * in, FILE * out, catarray_t * cats, uint8_t storyOptions);

#endif
