

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MSG 4096

char shift_vigenere(char c, char key_char, int decrypt) {
    if (!isalpha((unsigned char)c)) return c;
    int offset = isupper((unsigned char)c) ? 'A' : 'a';
    int key = tolower((unsigned char)key_char) - 'a';
    if (decrypt) key = -key;
    return (char)(((c - offset + key + 26) % 26) + offset);
}

void vigenere(const char *in, const char *key, char *out, int decrypt) {
    size_t msg_len = strlen(in);
    size_t key_len = strlen(key);
    size_t j = 0;

    for (size_t i = 0; i < msg_len && i < MAX_MSG-1; ++i) {
        if (isalpha((unsigned char)in[i])) {
            out[i] = shift_vigenere(in[i], key[j % key_len], decrypt);
            j++;
        } else {
            out[i] = in[i];
        }
    }
    out[msg_len] = '\0';
}

void prompt_and_run() {
    char mode[8];
    char key[256];
    char msg[MAX_MSG];
    char out[MAX_MSG];

    printf("Choose mode: (e)ncrypt or (d)ecrypt: ");
    if (!fgets(mode, sizeof(mode), stdin)) return;

    printf("Enter keyword (letters only): ");
    if (!fgets(key, sizeof(key), stdin)) return;
    size_t kl = strlen(key);
    if (kl > 0 && key[kl-1] == '\n') key[kl-1] = '\0';

    printf("Enter message (max %d chars):\n", MAX_MSG-1);
    if (!fgets(msg, sizeof(msg), stdin)) return;
    size_t ln = strlen(msg);
    if (ln > 0 && msg[ln-1] == '\n') msg[ln-1] = '\0';

    int decrypt = (mode[0] == 'd' || mode[0] == 'D');

    vigenere(msg, key, out, decrypt);

    if (!decrypt)
        printf("\nEncrypted: %s\n", out);
    else
        printf("\nDecrypted: %s\n", out);
}

int main(int argc, char *argv[]) {
    if (argc == 4) {
    
        char mode = argv[1][0];
        const char *key = argv[2];
        const char *msg = argv[3];
        char out[MAX_MSG];
        int decrypt = (mode == 'd' || mode == 'D');
        vigenere(msg, key, out, decrypt);
        printf("%s\n", out);
        return 0;
    }

    printf("Simple Vigenère cipher (C)\n");
    printf("---------------------------\n");
    prompt_and_run();

    return 0;
}
