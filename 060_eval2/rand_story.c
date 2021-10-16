#include "rand_story.h"

#include <string.h>

/* This function erases a word from the given category.
 */
void category_erase(category_t * cat, char * word) {
  // Sanity check.
  if (cat == NULL || word == NULL)
    return;

  // Find the word.
  size_t i = 0;
  while ((i < cat->n_words) && (strcmp(cat->words[i], word) != 0))
    i++;

  // Word not found.
  if (i == cat->n_words)
    return;

  // Delete the word and move the rest.
  free(cat->words[i - 1]);
  for (; i < (cat->n_words - 1); ++i)
    cat->words[i] = cat->words[i + 1];

  // Resize the pointer array.
  (cat->n_words)--;
  cat->words = realloc(cat->words, cat->n_words * sizeof(cat->words));

  return;
}

/* This function finds a category in the catarray by its name, and returns a pointer to it;
   returns NULL if not found.
 */
category_t * catarray_find(catarray_t * cats, const char * name) {
  // Sanity check.
  if (cats == NULL || name == NULL)
    return NULL;

  // Find the category.
  size_t i = 0;
  while ((i < cats->n) && (strcmp(cats->arr[i].name, name) != 0))
    i++;

  // Category not found.
  if (i == cats->n)
    return NULL;

  return &(cats->arr[i]);
}

/* This function constructs a new empty token struct, and returns a pointer to it.
 */
token_t * token_new(const tokenType_t type) {
  token_t * token = malloc(sizeof(*token));
  token->type = type;

  return token;
}

/* This function destructs a token struct.
 */
void token_delete(token_t * token) {
  if (token->type == STRING)
    free(token->value.str);
  if (token->type == CATEGORY)
    free(token->value.name);
  free(token);
}

/* This function constructs a new empty tokenArr struct, and returns a pointer to it.
 */
tokenArr_t * tokenArr_new(void) {
  tokenArr_t * arr = malloc(sizeof(*arr));
  arr->n_tokens = 0;
  arr->tokens = malloc(16 * sizeof(*arr->tokens));
  arr->n_avail = 16;
  return arr;
}

/* This function destructs a takenArr struct.
 */
void tokenArr_delete(tokenArr_t * arr) {
  for (size_t i = 0; i < arr->n_tokens; ++i)
    token_delete(arr->tokens[i]);
  free(arr->tokens);
  free(arr);
}

/* This function appends a token at the end of a tokenArr, resize it if needed.
 */
void tokenArr_push_back(tokenArr_t * arr, token_t * token) {
  // Sanity check.
  if (arr == NULL || token == NULL)
    return;

  // Resize if full.
  if (arr->n_avail == arr->n_tokens) {
    arr->n_avail *= 2;
    arr->tokens = realloc(arr->tokens, arr->n_avail * sizeof(*arr->tokens));
  }

  // Insert the token.
  arr->tokens[arr->n_tokens] = token;
  arr->n_tokens++;

  return;
}

/* This function parses a category file and returns the result.
 */
catarray_t * parseCat(FILE * f) {
}
