#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

void displayEmployees(struct Employee emp[], int n) {
    printf("\n              ------ Employee Records ------\n");
    printf("\n");
    printf("%-5s %-20s %-20s %-10s\n", "ID", "Name", "Designation", "Salary");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-5d %-20s %-20s %-10.2f\n", emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
    }
    printf("\n");
}

void findHighestSalary(struct Employee emp[], int n) {
    if (n <= 0) {
        printf("No employees to check.\n");
        return;
    }

    float maxSalary = emp[0].salary;
    
    for (int i = 1; i < n; i++) {
        if (emp[i].salary > maxSalary) {
            maxSalary = emp[i].salary;
        }
    }
    
    printf("--- Highest Paid Employee(s) ---\n");
    for (int i = 0; i < n; i++) {
        if (emp[i].salary == maxSalary) {
            printf("ID: %d\nName: %s\nSalary: %.2f\n\n", 
                   emp[i].id, emp[i].name, emp[i].salary);
        }
    }
}

void searchEmployee(struct Employee emp[], int n) {
    int choice;
    printf("Search by:\n1. ID\n2. Name\nEnter choice: ");
    scanf("%d", &choice);
    
    int found = 0;
    
    if (choice == 1) {
        int targetId;
        printf("Enter Employee ID: ");
        scanf("%d", &targetId);
        
        for (int i = 0; i < n; i++) {
            if (emp[i].id == targetId) {
                printf("Found: %s (Designation: %s, Salary: %.2f)\n", 
                       emp[i].name, emp[i].designation, emp[i].salary);
                found = 1;
                break;
            }
        }
    } 
    else if (choice == 2) {
        char targetName[50];
        printf("Enter Employee Name: ");
        scanf("%s", targetName); 
        
        for (int i = 0; i < n; i++) {
            if (strcmp(emp[i].name, targetName) == 0) {
                printf("Found: ID %d (Designation: %s, Salary: %.2f)\n", 
                       emp[i].id, emp[i].designation, emp[i].salary);
                found = 1;
            }
        }
    } 
    else {
        printf("Invalid choice.\n");
        return;
    }
    
    if (!found) {
        printf("Employee not found.\n");
    }
}

void giveBonus(struct Employee emp[], int n, float threshold) {
    if (n <= 0) {
        printf("No employees to give bonus to.\n");
        return;
    }
    printf("--- Applying 10%% Bonus to salaries < %.2f ---\n", threshold);
    for(int i = 0; i < n; i++) {
        if(emp[i].salary < threshold) {
            float oldSalary = emp[i].salary;
            emp[i].salary *= 1.10; 
            printf("Updated %s's salary from %.2f to %.2f\n", emp[i].name, oldSalary, emp[i].salary);
        }
    }
    printf("\n");
}

int main() {
    int n;
    
    printf("Enter number of employees: ");
    scanf("%d", &n);
    
    struct Employee employees[n];
    
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Employee %d:\n", i + 1);
        
        printf("ID: ");
        scanf("%d", &employees[i].id);
        
        printf("Name: ");
        scanf("%s", employees[i].name);
        
        printf("Designation: ");
        scanf("%s", employees[i].designation);
        
        printf("Salary: ");
        scanf("%f", &employees[i].salary);
    }
    
    displayEmployees(employees, n);
    
    searchEmployee(employees, n);
    
    giveBonus(employees, n, 50000);
    
    displayEmployees(employees, n);
    
    findHighestSalary(employees, n);
    
    return 0;
}