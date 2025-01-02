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

int is_ID_Unique(const int ID, const Student* head) {
    while (head != NULL) {
        if (head->ID == ID) {
            printf("ID already exists, try again!\n");
            return 0;
        }
        head = head->next;
    }
    return 1;
}

// Function to create a new student
Student* createStudent(int ID, const char* name, int age, float GPA) {
    // initialize everything
    Student* new_student = (Student*)malloc(sizeof(Student));
    if (new_student == NULL) {
        printf("Memory Allocation Failure.\n");
        return NULL;
    }
    new_student->ID = ID;
    strcpy(new_student->name, name);
    new_student->age = age;
    new_student->GPA = GPA;
    new_student->next = NULL;
    return new_student;
}


// Function to create a linked list of students
Student* createStudentList() {
    int ID, age, student_num;
    float GPA;
    char name[50];
    Student *p_head = NULL, *p_last = NULL;
    printf("Enter number of students: ");
    scanf("%d", &student_num); // NEED CHECK ABOUT SPACES AND WHEN INPUT VALID
    for (int i = 0; i < student_num; i++) {
        printf("Enter details for student %d:\n", i + 1);

        do {
            printf("ID: ");
            scanf("%d", &ID);
        } while (!is_ID_Unique(ID, p_head));
      
        printf("Name: ");
        scanf("%s", name);

        printf("Age: ");
        scanf("%d", &age);

        do {
            printf("GPA: ");
            scanf("%f", &GPA);

            if (GPA <= 0) {
                printf("GPA must be positive, try again!\n");
            }
        } while (GPA <= 0);

        

        Student *new_student = createStudent(ID, name, age, GPA);
        
        if (p_head == NULL){  // If List Empty
            p_head = new_student;
        }
        else {
            (*p_last).next = new_student;
        }
        p_last = new_student;
    }
    return p_head;
}

// Function to find the student with the highest GPA
Student* findTopStudent(Student* head) {
    // run  the list and return the student with highest GPA
    printf("\n");
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
        if (curr->GPA < minStudent->GPA || curr->GPA == minStudent->GPA && strcmp(curr->name, minStudent->name) < 0) { // strcmp returns negative value if curr.name is smaller
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

// Function to print given student
void printStudent(Student* student) {
    printf("ID: %d\nName: %s\nAge: %d\nGPA: %.2f", student->ID, student->name, student->age, student->GPA);
    if (student->next != NULL) {
        printf("\n");
    }
}

// Function to print all students
void printAllStudents(Student* head) {
    Student* curr = head;
    while (curr != NULL) {
        printStudent(curr);
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
