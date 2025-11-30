#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "members.dat"

typedef struct {
    int id;
    char fullName[100];
    char batch[20]; 
    char memType[10];
    char regDate[12];
    char dob[12];
    char interest[10];
} Student;

Student *studentDB = NULL;
int studentCount = 0;  
int dbCapacity = 0; 

void loadDatabase(const char *filename);
void saveDatabase(const char *filename);
void addStudent(Student s, const char *filename);
void updateStudent(int studentID);
void deleteStudent(int studentID);
void viewAllStudents();
void generateReports();
void freeMemory();
int isIdUnique(int id);
void inputString(char *buffer, int size);
void seedTestData();

int main() {
    loadDatabase(DATA_FILE);

    int choice, id;
    Student newStudent;

    do {
        printf("\n=== IEEE / ACM Registration Manager ===\n");
        printf("1. Register New Student\n");
        printf("2. Update Student Info\n");
        printf("3. Delete Student Record\n");
        printf("4. View All Records\n");
        printf("5. Generate Batch-wise Reports\n");
        printf("6. Generate Test Data (Stress Test)\n");
        printf("7. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n');

        switch (choice) {
            case 1:
                printf("\n--- Register Student ---\n");
                printf("Enter ID: ");
                scanf("%d", &newStudent.id);
                while(getchar() != '\n');

                if (!isIdUnique(newStudent.id)) {
                    printf("Error: Student ID %d already exists!\n", newStudent.id);
                    break;
                }

                printf("Full Name: ");
                inputString(newStudent.fullName, 100);
                
                printf("Batch (CS, SE, Cyber, AI): ");
                inputString(newStudent.batch, 20);

                printf("Membership Type (IEEE/ACM): ");
                inputString(newStudent.memType, 10);

                printf("Registration Date (YYYY-MM-DD): ");
                inputString(newStudent.regDate, 12);

                printf("Date of Birth (YYYY-MM-DD): ");
                inputString(newStudent.dob, 12);

                printf("Interest (IEEE/ACM/Both): ");
                inputString(newStudent.interest, 10);

                addStudent(newStudent, DATA_FILE);
                break;

            case 2:
                printf("Enter Student ID to Update: ");
                scanf("%d", &id);
                updateStudent(id);
                break;

            case 3:
                printf("Enter Student ID to Delete: ");
                scanf("%d", &id);
                deleteStudent(id);
                break;

            case 4:
                viewAllStudents();
                break;

            case 5:
                generateReports();
                break;
            
            case 6:
                seedTestData();
                break;

            case 7:
                printf("Exiting... Data saved.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 7);

    freeMemory();
    return 0;
}


void loadDatabase(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("[Info] No existing database found. Starting fresh.\n");
        return;
    }

    Student temp;
    while (fread(&temp, sizeof(Student), 1, fp)) {
        if (studentCount == dbCapacity) {
            dbCapacity = (dbCapacity == 0) ? 10 : dbCapacity * 2;
            studentDB = realloc(studentDB, dbCapacity * sizeof(Student));
            if (!studentDB) {
                printf("Memory allocation failed during load!\n");
                exit(1);
            }
        }
        studentDB[studentCount++] = temp;
    }
    fclose(fp);
    printf("[Success] Loaded %d records.\n", studentCount);
}

void saveDatabase(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Error opening file for saving");
        return;
    }

    size_t written = fwrite(studentDB, sizeof(Student), studentCount, fp);
    if (written != studentCount) {
        printf("Warning: Only wrote %zu of %d records.\n", written, studentCount);
    } else {
        printf("[Success] Database saved successfully.\n");
    }
    fclose(fp);
}

void addStudent(Student s, const char *filename) {
    if (studentCount == dbCapacity) {
        dbCapacity = (dbCapacity == 0) ? 10 : dbCapacity * 2;
        studentDB = realloc(studentDB, dbCapacity * sizeof(Student));
        if (!studentDB) {
            printf("Memory allocation failed!\n");
            return;
        }
    }
    studentDB[studentCount++] = s;

    FILE *fp = fopen(filename, "ab");
    if (fp == NULL) {
        perror("Error opening file for appending");
        return;
    }
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("[Success] Student added.\n");
}

void updateStudent(int studentID) {
    int index = -1;
    for (int i = 0; i < studentCount; i++) {
        if (studentDB[i].id == studentID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Student ID %d not found.\n", studentID);
        return;
    }

    printf("Updating Record for %s...\n", studentDB[index].fullName);

    printf("1. Update Batch\n2. Update Membership Type\nChoice: ");
    int choice;
    scanf("%d", &choice);
    while(getchar() != '\n');

    if (choice == 1) {
        printf("Enter new Batch: ");
        inputString(studentDB[index].batch, 20);
    } else if (choice == 2) {
        printf("Enter new Membership Type (IEEE/ACM): ");
        inputString(studentDB[index].memType, 10);
    } else {
        printf("Invalid choice. Update cancelled.\n");
        return;
    }

    saveDatabase(DATA_FILE); 
}

void deleteStudent(int studentID) {
    int index = -1;
    for (int i = 0; i < studentCount; i++) {
        if (studentDB[i].id == studentID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Student ID %d not found.\n", studentID);
        return;
    }

    if (index < studentCount - 1) {
        memmove(&studentDB[index], &studentDB[index + 1], 
                (studentCount - index - 1) * sizeof(Student));
    }
    studentCount--;

    printf("[Success] Student deleted from memory.\n");
    saveDatabase(DATA_FILE);
}

void viewAllStudents() {
    if (studentCount == 0) {
        printf("No records found.\n");
        return;
    }
    printf("\n%-5s %-20s %-10s %-10s %-12s\n", "ID", "Name", "Batch", "Type", "Reg Date");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%-5d %-20s %-10s %-10s %-12s\n", 
               studentDB[i].id, 
               studentDB[i].fullName, 
               studentDB[i].batch, 
               studentDB[i].memType, 
               studentDB[i].regDate);
    }
}

void generateReports() {
    char targetBatch[20];
    char targetInterest[10];
    
    printf("\n--- Generate Report ---\n");
    printf("Enter Batch to filter (CS, SE, AI, Cyber): ");
    inputString(targetBatch, 20);
    
    printf("Enter Interest (IEEE/ACM/Both) or 'All': ");
    inputString(targetInterest, 10);

    printf("\nReport for Batch: %s, Interest: %s\n", targetBatch, targetInterest);
    printf("%-5s %-20s %-10s\n", "ID", "Name", "Interest");
    printf("--------------------------------------\n");

    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strstr(studentDB[i].batch, targetBatch) != NULL) {
            if (strcasecmp(targetInterest, "All") == 0 || 
                strcasecmp(studentDB[i].interest, targetInterest) == 0) {
                
                printf("%-5d %-20s %-10s\n", 
                    studentDB[i].id, studentDB[i].fullName, studentDB[i].interest);
                found++;
            }
        }
    }
    if (found == 0) printf("No matching students found.\n");
}

int isIdUnique(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (studentDB[i].id == id) return 0;
    }
    return 1;
}

void inputString(char *buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

void freeMemory() {
    if (studentDB) free(studentDB);
}

void seedTestData() {
    printf("Seeding 20 test records...\n");
    Student dummies[5] = {
        {0, "Test User", "CS", "IEEE", "2023-01-01", "2002-01-01", "Both"},
        {0, "AI Student", "AI", "ACM", "2023-02-01", "2003-05-05", "ACM"},
        {0, "SE Student", "SE", "IEEE", "2023-03-01", "2001-12-12", "IEEE"},
        {0, "Cyber Guy", "Cyber", "ACM", "2023-04-01", "2002-08-20", "Both"},
        {0, "Dev Ops", "CS", "IEEE", "2023-05-01", "2003-01-01", "IEEE"}
    };

    for (int i = 1000; i < 1020; i++) {
        Student s = dummies[i % 5];
        s.id = i;
        if (isIdUnique(s.id)) {
            addStudent(s, DATA_FILE);
        }
    }
    printf("Stress test data added! View All to verify.\n");
}