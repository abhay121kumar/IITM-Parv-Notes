#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    float salary;
};

// Function to add a new employee
void addEmployee() {
    struct Employee emp;
    FILE *fp = fopen("employee.dat", "ab"); // append in binary
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    getchar(); // clear newline

    printf("Enter Employee Name: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = '\0'; // remove newline

    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(emp), 1, fp);
    fclose(fp);
    printf("Employee added successfully!\n");
}

// Function to display all employees
void displayEmployees() {
    struct Employee emp;
    FILE *fp = fopen("employee.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Employee List ---\n");
    while (fread(&emp, sizeof(emp), 1, fp)) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
    }
    fclose(fp);
}

// Function to search for an employee by ID
void searchEmployee() {
    int id;
    struct Employee emp;
    FILE *fp = fopen("employee.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    int found = 0;
    while (fread(&emp, sizeof(emp), 1, fp)) {
        if (emp.id == id) {
            printf("Employee Found!\n");
            printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
    fclose(fp);
}

// Main menu
int main() {
    int choice;

    while (1) {
        printf("\n--- Employee Management System ---\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
