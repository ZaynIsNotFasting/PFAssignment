#include <stdio.h>

#define ROWS 3
#define COLS 3

#define POWER_FLAG 1
#define OVERLOAD_FLAG 2
#define MAINTENANCE_FLAG 4

void querySector(int grid[ROWS][COLS]);
void updateSector(int grid[ROWS][COLS]);
void runDiagnostics(int grid[ROWS][COLS]);
void clearInputBuffer();

int main()
{
    int powerGrid[ROWS][COLS] = {
        {1, 3, 0},
        {5, 7, 2},
        {4, 0, 6}};
    int choice = 0;

    printf("--- IESCO Power Grid Monitor ---\n");

    do
    {
        printf("\n--- Operator Menu ---\n");
        printf("1. Query Sector Status\n");
        printf("2. Update Sector Status\n");
        printf("3. Run System Diagnostics\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            querySector(powerGrid);
            break;
        case 2:
            updateSector(powerGrid);
            break;
        case 3:
            runDiagnostics(powerGrid);
            break;
        case 4:
            printf("Exiting system.\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}

void querySector(int grid[ROWS][COLS])
{
    int r, c;
    printf("\nEnter sector coordinates (row col): ");
    scanf("%d %d", &r, &c);
    clearInputBuffer();

    if (r < 0 || r >= ROWS || c < 0 || c >= COLS)
    {
        printf("Error: Coordinates outside grid.\n");
        return;
    }

    int status = grid[r][c];
    printf("\n--- Status Report for Sector (%d, %d) [Value: %d] ---\n", r, c, status);

    printf("Power Status:         %s\n", (status & POWER_FLAG) ? "ON" : "OFF");
    printf("Overload Warning:     %s\n", (status & OVERLOAD_FLAG) ? "OVERLOADED" : "Normal");
    printf("Maintenance Required: %s\n", (status & MAINTENANCE_FLAG) ? "YES" : "No");
    printf("----------------------------------------\n");
}

void updateSector(int grid[ROWS][COLS])
{
    int r, c, flagChoice, action;

    printf("\nEnter sector coordinates (row col): ");
    scanf("%d %d", &r, &c);
    clearInputBuffer();

    if (r < 0 || r >= ROWS || c < 0 || c >= COLS)
    {
        printf("Error: Coordinates outside grid.\n");
        return;
    }

    printf("Which flag? (1=Power, 2=Overload, 3=Maintenance): ");
    scanf("%d", &flagChoice);
    clearInputBuffer();

    printf("Action? (1=Turn ON, 0=Turn OFF): ");
    scanf("%d", &action);
    clearInputBuffer();

    int flagToChange = 0;
    if (flagChoice == 1)
        flagToChange = POWER_FLAG;
    else if (flagChoice == 2)
        flagToChange = OVERLOAD_FLAG;
    else if (flagChoice == 3)
        flagToChange = MAINTENANCE_FLAG;
    else
    {
        printf("Error: Invalid flag.\n");
        return;
    }

    if (action == 1)
    {
        grid[r][c] = grid[r][c] | flagToChange;
        printf("Success: Flag SET. New status is %d\n", grid[r][c]);
    }
    else if (action == 0)
    {
        grid[r][c] = grid[r][c] & ~flagToChange;
        printf("Success: Flag CLEARED. New status is %d\n", grid[r][c]);
    }
    else
    {
        printf("Error: Invalid action.\n");
    }
}

void runDiagnostics(int grid[ROWS][COLS])
{
    int overloadCount = 0;
    int maintenanceCount = 0;

    printf("\n--- Running System Diagnostics ---\n");

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (grid[i][j] & OVERLOAD_FLAG)
            {
                overloadCount++;
            }
            if (grid[i][j] & MAINTENANCE_FLAG)
            {
                maintenanceCount++;
            }
        }
    }

    printf("--- Diagnostic Report ---\n");
    printf("Total sectors OVERLOADED: %d\n", overloadCount);
    printf("Total sectors REQUIRING MAINTENANCE: %d\n", maintenanceCount);
    printf("-------------------------\n");
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}