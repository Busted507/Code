// main.c
#include <stdio.h>

// sort.h
#ifndef SORT_H
#define SORT_H

#include <stdbool.h>

// Function prototypes
void swap(char *a, char *b);
bool letters_in_order(char a, char b);
bool numbers_in_ascending_order(char a, char b);
void bubble_sort(char arr[], int n, bool (*pair_is_in_order)(char a, char b));

#endif

// sort.c
#include <ctype.h> // for tolower

// Swap two elements
void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

// Compare two letters ignoring case (a-z, A-Z)
bool letters_in_order(char a, char b) {
    return tolower(a) <= tolower(b);
}

// Compare two numeric chars (but we’ll use them as numbers)
bool numbers_in_ascending_order(char a, char b) {
    return a <= b;
}

// Bubble sort implementation
void bubble_sort(char arr[], int n, bool (*pair_is_in_order)(char a, char b)) {
    bool swapped;

    do {
        swapped = false;
        for (int i = 1; i < n; i++) {
            if (!pair_is_in_order(arr[i - 1], arr[i])) {
                swap(&arr[i - 1], &arr[i]);
                swapped = true;
            }
        }
    } while (swapped);
}


int main() {
    char letter_arr1[] = {'z', 'S', 's', 'a'};
    int n_letters = sizeof(letter_arr1) / sizeof(letter_arr1[0]);

    printf("Before sorting letters: ");
    for (int i = 0; i < n_letters; i++)
        printf("%c ", letter_arr1[i]);
    printf("\n");

    bubble_sort(letter_arr1, n_letters, letters_in_order);

    printf("After sorting letters:  ");
    for (int i = 0; i < n_letters; i++)
        printf("%c ", letter_arr1[i]);
    printf("\n\n");


    char number_arr1[] = {4, -1, 2, 9};
    int n_numbers = sizeof(number_arr1) / sizeof(number_arr1[0]);

    printf("Before sorting numbers: ");
    for (int i = 0; i < n_numbers; i++)
        printf("%d ", number_arr1[i]);
    printf("\n");

    bubble_sort(number_arr1, n_numbers, numbers_in_ascending_order);

    printf("After sorting numbers:  ");
    for (int i = 0; i < n_numbers; i++)
        printf("%d ", number_arr1[i]);
    printf("\n");

    return 0;
}
