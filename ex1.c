#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
// SECTION A: Recursive Palindrome Check
int is_palindrome_recursive(char* str, int start, int end) {
    char first = str[start], last = str[end];
    if (start >= end) {        // Stop Condtion #1 - True If '' or Single Letter
        return 1;
    }
    if (!isalpha(first)) {     // Check if first is not alpha
        return is_palindrome_recursive(str, start + 1, end); // Cut first only
    }
    if (!isalpha(last)) {      // Check if last is not alpha
        return is_palindrome_recursive(str, start, end - 1); // Cut last only
    }
    if (tolower(first) == tolower(last)) {
        return is_palindrome_recursive(str, start + 1, end - 1); // Cut both ways
    }
    return 0;                  // Stop Condition #2 - False if not equal
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
    for (int start = 0; start < end; ) {
        
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
