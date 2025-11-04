#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_WORD_COUNT 15000
#define MAX_SUCCESSOR_COUNT (MAX_WORD_COUNT / 2)

/*
 This program expects a plaintext copy of Frankenstein saved as "pg84.txt"
 in the program's working directory. It reads the file at runtime into the
 `book` buffer and builds tokens & successor tables pointing into that buffer.
*/

char *book = NULL; /* will point to loaded book buffer */

/// Array of tokens registered so far.
/// No duplicates are allowed.
char *tokens[MAX_WORD_COUNT];
/// `tokens`'s current size
size_t tokens_size = 0;

/// Array of successor tokens
char *succs[MAX_WORD_COUNT][MAX_SUCCESSOR_COUNT];
/// `succs`'s current size
size_t succs_sizes[MAX_WORD_COUNT];

/// Overwrites non-printable characters in `book` with a space.
/// Non-printable characters may lead to duplicates like
/// `"\xefthe" and "the"` even both print `the`.
void replace_non_printable_chars_with_space() {
  // YOUR CODE HERE
  if (book == NULL)
    return;
  for (size_t i = 0; book[i] != '\0'; ++i) {
    unsigned char c = (unsigned char)book[i];
    if (!isprint(c)) {
      book[i] = ' ';
    }
  }
}

/// Returns the id (index) of the token, creating it if necessary.
///
/// Returns token id if token exists in \c tokens, otherwise creates a new entry
/// in \c tokens and returns its token id.
///
/// \param token token to look up (or insert)
/// \return Index of `token` in \c tokens array
size_t token_id(char *token) {
  size_t id;
  for (id = 0; id < tokens_size; ++id) {
    if (strcmp(tokens[id], token) == 0) {
      return id;
    }
  }
  tokens[id] = token;
  ++tokens_size;
  return id;
}

/// Appends the token \c succ to the successors list of \c token.
void append_to_succs(char *token, char *succ) {
  auto next_empty_index_ptr = &succs_sizes[token_id(token)];

  if (*next_empty_index_ptr >= MAX_SUCCESSOR_COUNT) {
    printf("Successor array full.");
    exit(EXIT_FAILURE);
  }

  succs[token_id(token)][(*next_empty_index_ptr)++] = succ;
}

/// Creates tokens on \c book and fills \c tokens and \c succs using
/// the functions \c token_id and \c append_to_succs.
void tokenize_and_fill_succs(char *delimiters, char *str) {
  // YOUR CODE HERE
  if (str == NULL)
    return;

  char *saveptr = NULL;
  char *prev = NULL;

  /* strtok_r will replace delimiter characters with '\0' and return pointers
     into the original buffer (no copies). This matches the program's design. */
  char *tok = strtok_r(str, delimiters, &saveptr);
  while (tok != NULL) {
    /* register token (ensures uniqueness in tokens array) */
    token_id(tok);

    /* if there was a previous token, add current as its successor */
    if (prev != NULL) {
      append_to_succs(prev, tok);
    }

    prev = tok;
    tok = strtok_r(NULL, delimiters, &saveptr);
  }
}

/// Returns last character of a string
char last_char(char *str) {
  // YOUR CODE HERE
  if (str == NULL || str[0] == '\0')
    return '\0';
  size_t len = strlen(str);
  return str[len - 1];
}

/// Returns whether the token ends with `!`, `?` or `.`.
bool token_ends_a_sentence(char *token) {
  // YOUR CODE HERE
  if (token == NULL || token[0] == '\0')
    return false;
  char c = last_char(token);
  return (c == '!' || c == '?' || c == '.');
}

/// Returns a random `token_id` that corresponds to a `token` that starts with a
/// capital letter.
/// Uses \c tokens and \c tokens_size.
size_t random_token_id_that_starts_a_sentence() {
  // YOUR CODE HERE
  if (tokens_size == 0) {
    fprintf(stderr, "No tokens available\n");
    exit(EXIT_FAILURE);
  }

  /* Try some random samples to find an uppercase-starting token quickly */
  for (int attempts = 0; attempts < 1000; ++attempts) {
    size_t r = (size_t)rand() % tokens_size;
    char *t = tokens[r];
    if (t != NULL && t[0] != '\0' && isupper((unsigned char)t[0])) {
      return r;
    }
  }

  /* Fall back to deterministic linear scan */
  for (size_t i = 0; i < tokens_size; ++i) {
    char *t = tokens[i];
    if (t != NULL && t[0] != '\0' && isupper((unsigned char)t[0])) {
      return i;
    }
  }

  /* If none start with uppercase, return any random token id */
  return (size_t)rand() % tokens_size;
}

/// Generates a random sentence using \c tokens, \c succs, and \c succs_sizes.
/// The sentence array will be filled up to \c sentence_size-1 characters using
/// random tokens until:
/// - a token is found where \c token_ends_a_sentence
/// - or more tokens cannot be concatenated to the \c sentence anymore.
/// Returns the filled sentence array.
///
/// @param sentence array what will be used for the sentence.
//
//                  Will be overwritten. Does not have to be initialized.
/// @param sentence_size
/// @return input sentence pointer
char *generate_sentence(char *sentence, size_t sentence_size) {
  size_t current_token_id = random_token_id_that_starts_a_sentence();
  auto token = tokens[current_token_id];

  sentence[0] = '\0';
  strcat(sentence, token);
  if (token_ends_a_sentence(token))
    return sentence;

  // Calculated sentence length for the next iteration.
  // Used to stop the loop if the length exceeds sentence size
  size_t sentence_len_next;
  // Concatenates random successors to the sentence as long as
  // `sentence` can hold them.
  do {
    // YOUR CODE HERE
    size_t succ_count = succs_sizes[current_token_id];
    if (succ_count == 0) {
      /* no successors, cannot continue */
      break;
    }

    size_t idx = (size_t)rand() % succ_count;
    char *next_token = succs[current_token_id][idx];

    /* compute next length: current length + 1 for space + next token length */
    sentence_len_next = strlen(sentence) + 1 + strlen(next_token);

    /* ensure we have room for terminating NUL */
    if (sentence_len_next >= sentence_size)
      break;

    strcat(sentence, " ");
    strcat(sentence, next_token);

    if (token_ends_a_sentence(next_token))
      break;

    current_token_id = token_id(next_token);
  } while (sentence_len_next < sentence_size - 1);
  return sentence;
}

/* Helper: load book file into memory and return pointer (malloc'd) */
#define BOOK_BUF_SIZE (7 * 1024 * 1024) /* 7MB - increase if needed */
char *load_book_file(const char *filename) {
  FILE *f = fopen(filename, "rb");
  if (!f) {
    perror("fopen");
    return NULL;
  }
  char *buf = malloc(BOOK_BUF_SIZE);
  if (!buf) {
    fclose(f);
    fprintf(stderr, "Out of memory\n");
    return NULL;
  }
  size_t read = fread(buf, 1, BOOK_BUF_SIZE - 1, f);
  buf[read] = '\0';
  fclose(f);
  return buf;
}

int main() {
  /* Load the book into memory from pg84.txt in working directory */
  book = load_book_file("pg84.txt");
  if (book == NULL) {
    fprintf(stderr, "Please place the Project Gutenberg Frankenstein text in pg84.txt\n");
    return EXIT_FAILURE;
  }

  replace_non_printable_chars_with_space();

  char *delimiters = " \t\n\r";
  tokenize_and_fill_succs(delimiters, book);



  char sentence[1000];
  srand((unsigned int)time(NULL)); /* Be random each time we run the program */

  /* Generate sentences until we find a question sentence. */
  do {
    generate_sentence(sentence, sizeof sentence);
  } while (last_char(sentence) != '?');
  puts(sentence);
  puts("");

  /* Initialize `sentence` and then generate sentences until we find a sentence
     ending with an exclamation mark. */
  do {
    generate_sentence(sentence, sizeof sentence);
  } while (last_char(sentence) != '!');
  puts(sentence);

  /* cleanup */
  free(book);
  return 0;
}