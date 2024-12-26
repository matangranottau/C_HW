#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

// Structure Definitions
typedef struct point {
    double x, y, z;
} Point;

typedef struct triangle {
    Point p, q, r;
} Triangle;

// Asks for (x,y,z) -> Returns a New Point
Point create_point(int point_num) {
    double x, y, z;
    printf("Point %d (x y z): ", point_num);
    scanf("%lf %lf %lf", &x, &y, &z);
    Point point = { x, y, z };
    return point;
}

// Creates 3 Points -> Returns a New Triangle
Triangle create_triangle() {
    Point p = create_point(1), q = create_point(2), r = create_point(3);
    Triangle triangle = { p, q, r };
    return triangle;
}

// y = x^2
double sq(double x) {
    return x * x;
}

// Distance Between Two Points
double distance(const Point p1, const Point p2) {
    return sqrt(sq(p1.x - p2.x) + sq(p1.y - p2.y) + sq(p1.z - p2.z));
}

// Function to calculate the perimeter of a triangle in 3 D
double perimeter(const Triangle* t) {
    return (distance(t->p, t->q) + distance(t->q, t->r) + distance(t->r, t->p));
}

// Function to calculate the area of a triangle in 3D 
double area(const Triangle* t) {
}

int main() {
    Triangle triangle;
    
    printf("Enter the coordinates of the 3 points of the triangle (x, y, z) format:\n");
    triangle = create_triangle();
    // Print the results
    printf("Perimeter: %.6f\n", perimeter(&triangle));
    printf("Area: %.6f\n", area(&triangle));

    return 0;
}
