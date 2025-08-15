// We want to make a console-based employee management system that can:

// Add new employees

// Display all employees

// Search employees by ID

// Store employee data permanently in a file (so that data is available 
// even after the program exits)
#include <stdio.h>

struct Employee{
    char name[50];
    int id;
    float salary;
};


