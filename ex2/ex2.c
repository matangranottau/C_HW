#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
// check check
// SECTION A: Recursive Subsequences Generation
void generate_subsequences(char* str, char* current, int index) {
    // TODO: Implement the recursive logic for generating subsequences
    if (strlen(str) == index + 1) { // If only letter:
        printf("");                     // Print nothing
        printf(str[index]);             // Print the char itself
    }   
    else {

    }
    // Print only rest of char
    // Print first char + rest of char
}

// Driver Program
int main() {
    char str[100];
    char current[100] = "";

    printf("Enter a string: ");
    scanf("%s", str);

    printf("Subsequences:\n");
    generate_subsequences(str, current, 0);

    return 0;
}
