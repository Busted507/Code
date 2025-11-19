#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define WINNING_SCORE 5

static const char *SHAPE_LINE = "0🪨  || 1🦎  || 2✂️  || 3🗒️  || 4🖖 : ";

int beats(int a, int b) {
    /* Returns 1 if a beats b, 0 otherwise.
       Mapping:
       0 Rock    -> beats 1 Lizard, 2 Scissors
       1 Lizard  -> beats 4 Spock, 3 Paper
       2 Scissors-> beats 3 Paper, 1 Lizard
       3 Paper   -> beats 0 Rock, 4 Spock
       4 Spock   -> beats 2 Scissors, 0 Rock
    */
    if (a == 0 && (b == 1 || b == 2)) return 1;
    if (a == 1 && (b == 4 || b == 3)) return 1;
    if (a == 2 && (b == 3 || b == 1)) return 1;
    if (a == 3 && (b == 0 || b == 4)) return 1;
    if (a == 4 && (b == 2 || b == 0)) return 1;
    return 0;
}

void print_welcome(void) {
    puts("Welcome to 🪨  ✂️  🗒️  🖖  🦎 !");
    puts("(s) Single player");
    puts("(e) Exit");
}

void play_single_player(void) {
    int player_score = 0;
    int agent_score = 0;
    char buf[128];

    srand((unsigned int)time(NULL));

    puts("Starting game 🎉");
    while (player_score < WINNING_SCORE && agent_score < WINNING_SCORE) {
        int choice;
        printf("\nSelect a shape:\n%s", SHAPE_LINE);
        if (!fgets(buf, sizeof buf, stdin)) {
            /* Per spec: no need to handle EOF specially */
            puts("Input error. Exiting.");
            return;
        }

        /* Try parse integer; allow whitespace */
        char *p = buf;
        while (isspace((unsigned char)*p)) p++;
        if (*p == '\0') {
            puts("❌ Invalid input. Try again.");
            continue;
        }

        /* Use sscanf to parse integer, but also handle stray chars */
        if (sscanf(p, "%d", &choice) != 1) {
            puts("❌ Invalid input. Try again.");
            continue;
        }

        if (choice < 0 || choice > 4) {
            printf("❌ Shape key %d does not exist. Try again.\n", choice);
            continue;
        }

        int agent = rand() % 5;
        printf("Agent: %d\n", agent);

        if (choice == agent) {
            /* tie */
        } else if (beats(choice, agent)) {
            player_score++;
        } else {
            agent_score++;
        }

        printf("👫:🤖  %d:%d\n", player_score, agent_score);
    }

    if (player_score >= WINNING_SCORE) {
        puts("🎉 You won!");
    } else {
        puts("🤖 Agent won!");
    }
}

int main(void) {
    char buf[64];

    print_welcome();

    while (1) {
        printf("Select an item: ");
        if (!fgets(buf, sizeof buf, stdin)) {
            /* EOF or error - exit */
            puts("\nGoodbye.");
            return 0;
        }

        /* find first non-space */
        char *p = buf;
        while (isspace((unsigned char)*p)) p++;
        if (*p == '\0') {
            puts("❌ Invalid menu choice. Try again.");
            continue;
        }

        char c = tolower((unsigned char)*p);
        if (c == 's') {
            play_single_player();
            return 0;
        } else if (c == 'e') {
            puts("Goodbye.");
            return 0;
        } else {
            puts("❌ Invalid menu choice. Try again.");
        }
    }

    return 0;
}
