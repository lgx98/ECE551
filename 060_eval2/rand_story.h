#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

// any functions you want your main to use
void exit_error(char * message);

// Basic operations on category and catarray
void category_init(category_t * cat, char * name);

void category_free(category_t * cat);

void category_push_back(category_t * cat, char * word);

void category_erase(category_t * cat, char * word);

catarray_t * catarray_new(void);

void catarray_delete(catarray_t * cats);

void catarray_expand_end(catarray_t * cats);

category_t * catarray_find(catarray_t * cats, char * name);

void catarray_add_pair(catarray_t * cats, char * name, char * word);

// Definition and basic operations on token
// Inspired by the definition of Lua TValue.
//(I learned this even before coming to Durham, so no academic misconduct.)
typedef enum _tokenType_t {
  STRING,    // plain string
  CATEGORY,  // category name of a blank
  NUMBER,    // an integer that decides which previous word should be used
  POINTER    // pointer to another token
} tokenType_t;

typedef union _tokenValue_t {
  char * str;
  char * name;
  size_t num;
  void * token;
} tokenValue_t;

typedef struct _token_t {
  tokenType_t type;
  tokenValue_t value;
} token_t;

token_t * token_new(tokenType_t type);

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
FILE * open_file(char * filename, char * mode);

void close_file(FILE * file);

catarray_t * parseCat(FILE * f);

tokenArr_t * parseStory(FILE * f);

typedef enum _stroyOption_t {
  DEFAULT = 0,
  ALWAYS_CAT = 1 << 0,
  NO_REUSE = 1 << 1
} storyOption_t;

int hasOption(uint options, storyOption_t interested_option);

void makeStory(tokenArr_t * story, catarray_t * cats, uint storyOptions);

void writeStory(FILE * f, tokenArr_t * story);

/* Some designs of flexible word choosing
  a. Callback function with void * argument.
  * int tellStory(FILE *cat, FILE *story, FILE *out,
  *   const char *(*chooseWord)(char *category, catarray_t *cats, void *arg),
  *   void *arg);
  b. Keep track of previous blanks in static variables.
  * const char *chooseWord_numbers(char *category, catarray_t *cats) {
  *   static tokenArr_t *prev_tokens = tokenArr_new();
  *   if (cats == NULL) { // Using NULL as reset signal
  *     tokenArr_delete(prev_tokens);
  *     return NULL;
  *   }
  *   // Other Code
  * }
->c. Let users stitch up their own code with whatever they want.
  * tokenArr_t *tokens = parseStory(story);
  * // manipulating tokens
  * void writeStory(stdout, tokens);
 */
#endif
