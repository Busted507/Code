#include <stdio.h>
enum {Rock, Paper, Scissors, Lizard, Spock} p1,p2
const char *shape_strings[] = {"🪨", "🗒️", "✂️", "🖖", "🦎"}
int main() {
  for (size_t p1 = 0; p1 < SHAPE_COUNT; ++p1) {
    for (size_t p2 = 0; p2 < SHAPE_COUNT; ++p2) {
      printf("If p1: %s  and p2: %s  => ", SHAPE_STRINGS[p1],
             SHAPE_STRINGS[p2]);

