#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INTIAL_SIZE 10

// Define a struct for Student
typedef struct Student {
    int ID;
    char name[50];
    int age;
    float GPA;
    struct Student* next;  // Pointer to the next student in the list
} Student;

// Helper function to get string with unknown size
char* readline() {
    int index = 0, c, capacity = INTIAL_SIZE;
    char* buffer = (char*)malloc(capacity * sizeof(char));

    if (buffer == NULL) {
        return NULL;
    }

    for (c = getchar(); c != '\n'; c = getchar()) {
        if (index == capacity - 1) {
            buffer = (char*)realloc(buffer, capacity * 2 * sizeof(char));
            if (buffer == NULL) {
                return NULL;
            }
            capacity *= 2;
        }
        buffer[index++] = c;
    }
    buffer[index] = '\0';
    return buffer;
}


// Function to create a new student
Student* createStudent(int ID, const char* name, int age, float GPA) {
    // initialize everything
    Student* new_student = (Student*)malloc(sizeof(Student));
    new_student->ID = ID;
    strcpy(new_student->name, name);
    new_student->age = age;
    new_student->GPA = GPA;
    return new_student;
}


// Function to create a linked list of students
Student* createStudentList() {
    int ID, age, student_num;
    float GPA;
    char* name = readline();
    printf("Enter number of students: ");
    scanf("%d", &student_num); // NEED CHECK ABOUT SPACES AND WHEN INPUT VALID
    // to be continued

}

// Function to find the student with the highest GPA
Student* findTopStudent(Student* head) {
    // run  the list and return the student with highest GPA
    Student* curr = head;
    Student* top = head;
    while (curr != NULL) {
        if (curr->GPA > top->GPA) {
            top = curr;
        }
        curr = curr -> next;
    }
    return top;
}

// Function to delete the student with the lowest GPA
Student* deleteLowestGPA(Student* head) {
    // run  the list and Delete the student with lowest GPA
    Student* curr = head, *prev = NULL, *minprev = NULL, *minStudent = head;
    while(curr != NULL){
        if (curr->GPA < minStudent->GPA) {
            minStudent = curr;
            minprev = prev;
        }
        prev = curr;
        curr = curr->next;
    }
    if (minprev == NULL) {
        head = head->next;
    }
    else {
        minprev->next = minStudent->next;
    }
    free(minStudent);
    return head;
}

// Function to print all students
void printAllStudents(Student* head) {
    Student* curr = head;
    while (curr != NULL) {
        printf("ID: %d\nName: %s\nAge: %d\nGPA: %.2f\n", curr->ID, curr->name, curr->age, curr->GPA);
        curr = curr->next;
    }
}

// Function to free the memory of the entire student list
void freeStudentList(Student* head) {
    Student* curr = head;
    while (curr != NULL) {
        Student* temp = curr;
        curr = curr->next;
        free(temp);
    }
}

int main() {
    // Create the student list
    Student* head = createStudentList();

    // Print all students
    printf("\nAll Students:\n");
    printAllStudents(head);

    // Find and print the top student with the highest GPA
    Student* topStudent = findTopStudent(head);
    if (topStudent != NULL) {
        printf("\nTop Student:\n");
        printStudent(topStudent);
    }

    // Delete the student with the lowest GPA and print the updated list
    head = deleteLowestGPA(head);
    printf("\nAfter deleting the student with the lowest GPA:\n");
    printAllStudents(head);

    // Free the memory of the student list
    freeStudentList(head);

    return 0;
}
