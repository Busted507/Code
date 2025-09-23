#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    const char *inventory[] = {"hydraulic pump", "PLC module", "servo motor"};
    int inventory_size = 3;
    char input[100];

    printf("Hej. Welcome to the spare parts inventory!\n");

    while (1) {
        printf("Which part do you need? ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // exit if input fails
        }

        // Remove newline at the end if present
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        // Convert to lowercase for special queries
        char lowered[100];
        for (int i = 0; input[i]; i++) {
            lowered[i] = (char)tolower((unsigned char)input[i]);
            lowered[i + 1] = '\0';
        }

        if (strcmp(lowered, "do you actually have any parts?") == 0 ||
            strcmp(lowered, "is there anything in stock at all?") == 0) {
            printf("We have %d part(s)!\n", inventory_size);
            for (int i = 0; i < inventory_size; i++) {
                printf("%s\n", inventory[i]);
            }
            continue;
        }

        // Check inventory (case-sensitive)
        int found = 0;
        for (int i = 0; i < inventory_size; i++) {
            if (strcmp(input, inventory[i]) == 0) {
                printf("I've got %s here for you. Bye!\n", input);
                found = 1;
                break;
            }
        }

        if (found) {
            break; // exit program after confirming availability
        } else {
            printf("I am afraid we don't have any %s in the inventory \n", input);
        }
    }

    return 0;
}
