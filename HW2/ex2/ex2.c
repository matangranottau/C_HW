#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
// check check
// SECTION A: Recursive Subsequences Generation
void generate_subsequences(char* str, char* current, int index) {
    // TODO: Implement the recursive logic for generating subsequences
    int current_len = strlen(current);
    if (strlen(str) == index + 1) {
        if (current_len > 0) {
            printf("%s\n", current);
            printf("%s%c\n", current, str[index]);
        }
        else {
            printf("%c\n", str[index]);
        }
        
    }   
    else {
        generate_subsequences(str, current, index + 1);
        current[current_len] = str[index];
        current[current_len + 1] = '\0';
        generate_subsequences(str, current, index + 1);

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
