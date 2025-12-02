#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int counts[13] = {0};   // indices 2–12 will be used
    int N = 50000;

    srand(time(NULL));      // seed the random number generator

    for (int i = 0; i < N; i++) {
        int die1 = rand() % 6 + 1;
        int die2 = rand() % 6 + 1;
        int sum = die1 + die2;
        counts[sum]++;
    }

    // Print the results
    for (int s = 2; s <= 12; s++) {
        printf("%2d: %d\n", s, counts[s]);
    }

    return 0;
}
