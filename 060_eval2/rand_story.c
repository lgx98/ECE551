#include "rand_story.h"

#include <string.h>

/* This function prints error message and exit with failure.
 */
void exit_error(char * message) {
  fprintf(stderr, "Error: %s, Exitting!", message);
  exit(EXIT_FAILURE);
}

/* This function initializes a category struct.
 * The memory for category struct is allocated by catarray_push_back
 */
void category_init(category_t * cat, char * name) {
  // Sanity check.
  if (name == NULL)
    return;

  cat->name = name;
  cat->words = NULL;
  cat->n_words = 0;
  return;
}

/* This function frees dynamically allocated memory inside category struct
 */
void category_free(category_t * cat) {
  // Sanity check.
  if (cat == NULL)
    return;

  for (size_t i = 0; i < cat->n_words; ++i)
    free(cat->words[i]);
  free(cat->words);
  free(cat->name);
}

/* This function appends a word at the end of a category.
 */
void category_push_back(category_t * cat, char * word) {
  // Sanity check.
  if (cat == NULL || word == NULL)
    return;

  cat->n_words++;
  cat->words = realloc(cat->words, cat->n_words * sizeof(*cat->words));
  cat->words[cat->n_words - 1] = word;
  return;
}

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

  // Delete the word and move the rest forward.
  free(cat->words[i]);
  for (; i < (cat->n_words - 1); ++i)
    cat->words[i] = cat->words[i + 1];

  // Resize the pointer array.
  (cat->n_words)--;
  // No need to shrink the array.
  // cat->words = realloc(cat->words, cat->n_words * sizeof(cat->words));

  return;
}

/* This function constructs a new empty catarray struct, and returns a pointer
 * to it.
 */
catarray_t * catarray_new(void) {
  catarray_t * cats = malloc(sizeof(*cats));
  cats->n = 0;
  cats->arr = NULL;
  return cats;
}

/* This function destructs a catarray struct.
 */
void catarray_delete(catarray_t * cats) {
  // Sanity check.
  if (cats == NULL)
    return;

  for (size_t i = 0; i < cats->n; ++i)
    category_free(&(cats->arr[i]));
  free(cats->arr);
  free(cats);
}

/* This function expands the catarray at the end by one element.
 */
void catarray_expand_end(catarray_t * cats) {
  // Sanity check.
  if (cats == NULL)
    return;

  cats->n++;
  cats->arr = realloc(cats->arr, cats->n * sizeof(*cats->arr));
}

/* This function finds a category in the catarray by its name, and returns a
 * pointer to it; returns NULL if not found.
 */
category_t * catarray_find(catarray_t * cats, char * name) {
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

/* This function adds a name-word pair to the catarray.
 */
void catarray_add_pair(catarray_t * cats, char * name, char * word) {
  // Sanity check.
  if (cats == NULL || name == NULL || word == NULL)
    return;

  category_t * cat = catarray_find(cats, name);
  if (cat == NULL) {
    catarray_expand_end(cats);
    cat = &cats->arr[cats->n - 1];
    category_init(cat, name);
    category_push_back(cat, word);
  }
  else {
    free(name);
    category_push_back(cat, word);
  }
  return;
}

/* This function constructs a new empty token struct, and returns a pointer to
 * it.
 */
token_t * token_new(tokenType_t type) {
  token_t * token = malloc(sizeof(*token));
  token->type = type;
  return token;
}

/* This function destructs a token struct.
 */
void token_delete(token_t * token) {
  if (token->type == STRING) {
    free(token->value.str);
  }
  if (token->type == CATEGORY)
    free(token->value.name);
  free(token);
}

/* This function constructs a new empty tokenArr struct, and returns a pointer
 * to it.
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

/* This function wraps around fopen and handles exception.
 */
FILE * open_file(char * filename, char * mode) {
  FILE * f = fopen(filename, mode);
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  return f;
}

/* This function wraps around fclose and handles exception.
 */
void close_file(FILE * f) {
  if (fclose(f)) {
    perror("Could not close file");
    exit(EXIT_FAILURE);
  }
}

/* This function parses a category file and returns the result.
 */
catarray_t * parseCat(FILE * f) {
  catarray_t * cats = catarray_new();

  char * line = NULL;
  size_t len = 0;
  ssize_t nread;
  while ((nread = getline(&line, &len, f)) != -1) {
    char * ptr_delim = strchr(line, ':');
    if (ptr_delim == NULL)
      exit_error("Delimeter Not Found");
    catarray_add_pair(cats,
                      strndup(line, ptr_delim - line),
                      strndup(ptr_delim + 1, line + nread - ptr_delim - 2));
  }
  free(line);
  return cats;
}

/* This function parses a story file and returns the result.
 */
tokenArr_t * parseStory(FILE * f) {
  tokenArr_t * tokens = tokenArr_new();

  char * line = NULL;
  size_t len = 0;
  ssize_t nread;
  /* ptr points to the first unparsed char;
   * ptr_left and prt_right points to the left and right underlines of
   * the first unparsed blank.
   * parsed _text_, string _next blank_ ... \n\0
   *              ^        ^          ^
   *             ptr   ptr_left   ptr_right
   */
  while ((nread = getline(&line, &len, f)) != -1) {
    char * ptr = line;
    while (*ptr != '\0') {
      char * ptr_left;
      char * ptr_right;
      ptr_left = strchr(ptr, '_');

      // Only a string left in the line.
      if (ptr_left == NULL) {
        token_t * token = token_new(STRING);
        token->value.str = strdup(ptr);
        tokenArr_push_back(tokens, token);
        break;
      }

      // Parse the string before the blank, if it exists.
      if (ptr_left > ptr) {
        token_t * token = token_new(STRING);
        token->value.str = strndup(ptr, ptr_left - ptr);
        tokenArr_push_back(tokens, token);
      }

      ptr_right = strchr(ptr_left + 1, '_');
      if (ptr_right == NULL)
        exit_error("Unmatched '_' in a Line");

      // Parse the blank.
      char * blank = strndup(ptr_left + 1, ptr_right - ptr_left - 1);
      if (atoi(blank) > 0) {
        // Valid integer.
        token_t * token = token_new(NUMBER);
        token->value.num = (size_t)atoi(blank);
        free(blank);
        tokenArr_push_back(tokens, token);
      }
      else {
        // A category name.
        token_t * token = token_new(CATEGORY);
        token->value.name = blank;
        tokenArr_push_back(tokens, token);
      }
      ptr = ptr_right + 1;
    }
  }
  free(line);
  return tokens;
}

/* This function wraps around bitwise AND, making it more readable.
 */
int hasOption(uint options, storyOption_t interested_option) {
  return (options & interested_option) != 0;
}

/* This function takes the parsed story and fill in the blanks in place.
 */
void makeStory(tokenArr_t * story, catarray_t * cats, uint storyOptions) {
  // Sanity check.
  if (story == NULL)
    return;
  if ((!hasOption(storyOptions, ALWAYS_CAT)) && (cats == NULL))
    return;

  tokenArr_t * prev_tokens = NULL;
  if (!hasOption(storyOptions, ALWAYS_CAT))
    prev_tokens = tokenArr_new();

  for (size_t i = 0; i < story->n_tokens; ++i) {
    token_t * token = story->tokens[i];
    switch (token->type) {
      case CATEGORY:
        if (!hasOption(storyOptions, ALWAYS_CAT)) {
          category_t * cat = catarray_find(cats, token->value.name);
          // Sanity check.
          if (cat == NULL)
            exit_error("Category Not Found");
          if (cat->n_words == 0)
            exit_error("Words Used Up in Category");

          char * word = strdup(chooseWord(token->value.name, cats));
          token->type = STRING;
          free(token->value.name);
          token->value.str = word;
          if (hasOption(storyOptions, NO_REUSE))
            category_erase(cat, word);
          tokenArr_push_back(prev_tokens, token);
        }
        else {
          char * word = strdup(chooseWord(token->value.name, NULL));
          token->type = STRING;
          free(token->value.name);
          token->value.str = word;
        }
        break;

      case NUMBER:
        if (!hasOption(storyOptions, ALWAYS_CAT)) {
          // Sanity check.
          if (token->value.num > prev_tokens->n_tokens)
            exit_error("Not Enough Previous Words");

          token_t * prev_token =
              prev_tokens->tokens[prev_tokens->n_tokens - token->value.num];
          token->type = POINTER;
          if (prev_token->type == POINTER)
            token->value.token = prev_token->value.token;
          else
            token->value.token = prev_token;
          tokenArr_push_back(prev_tokens, token);
        }
        else {
          char * word = strdup(chooseWord("", NULL));
          token->type = STRING;
          token->value.str = word;
        }
        break;

      default:
        break;
    }
  }
  // prev_tokens->tokens[i] are pointers to tokens in story->tokens[i]
  // so they are not freed at this time.
  if (!hasOption(storyOptions, ALWAYS_CAT)) {
    free(prev_tokens->tokens);
    free(prev_tokens);
  }
  return;
}

/* This function takes the filled story and prints out the text.
 */
void writeStory(FILE * f, tokenArr_t * story) {
  // Sanity check.
  if (story == NULL)
    return;

  for (size_t i = 0; i < story->n_tokens; ++i) {
    token_t * token = story->tokens[i];
    switch (token->type) {
      case STRING:
        fputs(token->value.str, f);
        break;

      case POINTER:
        fputs(((token_t *)token->value.token)->value.str, f);
        break;

      default:
        break;
    }
  }
  return;
}
