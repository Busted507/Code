#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE_MAX 100
#define DELIM "," // CSV delimiter

char *ifile, *ofile;
unsigned filter_age_max;
FILE *istream, *ostream;

const char USAGE[] =
    R"(Filters CSV rows, keeping only those with provided maximum age
%1$s max-age [input-file] [output-file]

Example: 
%1$s max-age 17 input.csv output.csv
%1$s max-age 10 input.csv (outputs to stdout)
%1$s max-age 54           (inputs from stdin, outputs to stdout)
)";

void filter_stream(FILE *istream, FILE *ostream) {
  char line[LINE_MAX];
  char orig_line[LINE_MAX];
  char *fgets_return;
  char *name, *age_str;
  size_t line_no = 0;

  while (
      // Read a line from `istream` and assign the return value to
      // `fgets_return`
      (fgets_return = fgets(line, LINE_MAX, istream)) != NULL
  ) {
    ++line_no;

    // keep a copy of the original line so we can forward it unchanged
    strncpy(orig_line, line, LINE_MAX);
    orig_line[LINE_MAX - 1] = '\0';

    if (fgets_return && *fgets_return != '\n') {
      if (strlen(line) > 1) {
        // Assign `name` and `age_str` using `strtok`
        name = strtok(line, DELIM);
        age_str = strtok(NULL, DELIM);

        // Alternative to strtok:
        // sscanf(line, "%*[^,],%d", &age);

        if (!age_str) {
          // Error message
          fprintf(stderr, "Line %zu: age missing\n", line_no);
          continue;
        }
      } else {
        // treat very short lines as blank
        fprintf(stderr, "Line %zu: blank line\n", line_no);
        continue;
      }
    } else {
      // Error message for a blank line
      fprintf(stderr, "Line %zu: blank line\n", line_no);
      continue;
    }

    // Trim leading and trailing whitespace from age_str
    while (*age_str && isspace((unsigned char)*age_str)) age_str++;
    char *end = age_str + strlen(age_str) - 1;
    while (end > age_str && isspace((unsigned char)*end)) {
      *end = '\0';
      end--;
    }

    // Age processing
    unsigned age;
    int recognized_count = sscanf(age_str, "%u", &age);
    if (recognized_count == 1) {
      if (age <= filter_age_max) {
        // Forward input line to `ostream`
        fputs(orig_line, ostream);
      }
    } else {
      // Error message
      fprintf(stderr, "Line %zu: age not recognized: '%s'\n", line_no, age_str);
    }
  }
}

int main(int argc, char *argv[]) {
  switch (argc) {
  case 4:
    // max-age ifile ofile
    ofile = argv[3];
  case 3:
    // max-age ifile
    ifile = argv[2];
  case 2:
    // max-age
    if (!sscanf(argv[1], "%d", &filter_age_max)) {
      puts("First argument is not an age.");
      exit(EXIT_FAILURE);
    }
    break;
  default:
    printf(USAGE, argv[0]);
    return EXIT_SUCCESS;
  }

  if (ifile) {
    // Open `ifile` and assign it to `istream`
    istream = fopen(ifile, "r");

    // Exit program with an error message if file cannot be opened
    if (!istream) {
      fprintf(stderr, "Failed to open input file: %s\n", ifile);
      exit(EXIT_FAILURE);
    }
  } else {
    // Set `istream` if no file provided
    istream = stdin;
  }

  if (ofile) {
    // Open `ofile` and assign it to `ostream`
    ostream = fopen(ofile, "w");

    // Exit program with an error message if file cannot be opened
    if (!ostream) {
      fprintf(stderr, "Failed to open output file: %s\n", ofile);
      exit(EXIT_FAILURE);
    }
  } else {
    // Set `ostream` if no file provided
    ostream = stdout;
  }

  filter_stream(istream, ostream);

  if (istream && istream != stdin) fclose(istream);
  if (ostream && ostream != stdout) fclose(ostream);

  return EXIT_SUCCESS;
}