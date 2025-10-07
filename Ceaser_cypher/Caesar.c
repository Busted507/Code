

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MSG 4096

char shift_char(char c, int key) {
    if (isupper((unsigned char)c)) {
        return (char)(((c - 'A') + key + 26) % 26 + 'A');
    } else if (islower((unsigned char)c)) {
        return (char)(((c - 'a') + key + 26) % 26 + 'a');
    } else {
        return c; // unchanged
    }
}

void caesar(const char *in, char *out, int key) {
    size_t i;
    for (i = 0; i < strlen(in) && i < MAX_MSG-1; ++i) {
        out[i] = shift_char(in[i], key);
    }
    out[i] = '\0';
}

void prompt_and_run() {
    char mode[8];
    char msg[MAX_MSG];
    char out[MAX_MSG];
    int key;

    printf("Choose mode: (e)ncrypt or (d)ecrypt: ");
    if (!fgets(mode, sizeof(mode), stdin)) return;

    printf("Enter numeric key (e.g. 3): ");
    if (scanf("%d", &key) != 1) return;
    while (getchar() != '\n'); 

    printf("Enter message (max %d chars):\n", MAX_MSG-1);
    if (!fgets(msg, sizeof(msg), stdin)) return;
   
    size_t ln = strlen(msg);
    if (ln > 0 && msg[ln-1] == '\n') msg[ln-1] = '\0';

    if (mode[0] == 'd' || mode[0] == 'D') key = -key;

    caesar(msg, out, key);
    if (mode[0] == 'e' || mode[0] == 'E')
        printf("\nEncrypted: %s\n", out);
    else
        printf("\nDecrypted: %s\n", out);
}

int main(int argc, char *argv[]) {
    if (argc == 4) {
     
        char mode = argv[1][0];
        int key = atoi(argv[2]);
        char out[MAX_MSG];
        if (mode == 'd' || mode == 'D') key = -key;
        caesar(argv[3], out, key);
        if (mode == 'e' || mode == 'E')
            printf("%s\n", out);
        else
            printf("%s\n", out);
        return 0;
    }

    printf("Simple Caesar cipher (C)\n");
    printf("------------------------\n");
    prompt_and_run();

    return 0;
}
