#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
// Commit Test why are you gay?
// SECTION A: Recursive Palindrome Check
int is_palindrome_recursive(char* str, int start, int end) {
    // TODO: Implement the logic for recursive palindrome check
    // First Check if First/Last is alpha - if not cut First or Last
    // Stop Condition #1 - If First letter != Last Letter
    // Stop Condtion #2 - If '' or Single Letter
    // Cut both ways


    return 0; // Placeholder return value
}

// SECTION B: Iterative Palindrome Check
int is_palindrome_iterative(char* str) {
    // TODO: Implement the logic for iterative palindrome check
    // Run from both ends
    // If alpha start++ or end--
    // If not equal - break
    // if start >= end - return True
    // loop that count untill \0
    int length = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        length++;
    }
    int end = length, start = 0;
    for (int start = 0; start < end; start++) {
        for (int end = length; start < end; end--) {
            if (isalpha(str[start]) != 0)
            {
                start++;
            }
            else if (isalpha(str[end] != 0))
            {
                end--;
            }
            else if (isalpha(str[end] == 0) && isalpha(str[start]) == 0)
            {
                if (str[start] != str[end]) {
                    return 0;
                }
                else {
                    start++;
                    end--;
                }

            }
        }
    }
    return 1; // Placeholder return value
}


// Driver Program
int main() {
    char str[1000];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character
    str[strcspn(str, "\n")] = '\0';

    printf("\nResults:\n");
    printf("Recursive Palindrome Check: %s\n", is_palindrome_recursive(str, 0, strlen(str) - 1) ? "Palindrome" : "Not a Palindrome");
    printf("Iterative Palindrome Check: %s\n", is_palindrome_iterative(str) ? "Palindrome" : "Not a Palindrome");

    return 0;
}
