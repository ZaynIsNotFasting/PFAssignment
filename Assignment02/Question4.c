#include <stdio.h>

#define MAX_SIZE 5

int stack[MAX_SIZE];
int top = -1;

void push();
void pop();
void peek();
void display();
void clearInputBuffer();

int main()
{
    int choice = 0;

    printf("--- Welcome to the Stack Program ---\n");

    do
    {
        printf("\n--- Main Menu ---\n");
        printf("1. PUSH (Insert an element)\n");
        printf("2. POP (Remove an element)\n");
        printf("3. PEEK (View the top element)\n");
        printf("4. DISPLAY (Show all elements)\n");
        printf("5. EXIT\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            push();
            break;
        case 2:
            pop();
            break;
        case 3:
            peek();
            break;
        case 4:
            display();
            break;
        case 5:
            printf("Exiting the program. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please select from 1 to 5.\n");
        }
    } while (choice != 5);

    return 0;
}

void push()
{
    int value;

    if (top == MAX_SIZE - 1)
    {
        printf("!!! Stack Overflow! Cannot push any more items.\n");
        return;
    }

    printf("Enter the value to push: ");
    if (scanf("%d", &value) != 1)
    {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    top++;
    stack[top] = value;

    printf("Success: %d was pushed onto the stack.\n", value);
}

void pop()
{
    if (top == -1)
    {
        printf("!!! Stack Underflow! Cannot pop from an empty stack.\n");
        return;
    }

    int poppedValue = stack[top];
    top--;

    printf("Success: %d was popped from the stack.\n", poppedValue);
}

void peek()
{
    if (top == -1)
    {
        printf("Stack is empty. There is nothing to peek.\n");
        return;
    }

    printf("The top element on the stack is: %d\n", stack[top]);
}

void display()
{
    if (top == -1)
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("--- Stack (Top to Bottom) ---\n");
    for (int i = top; i >= 0; i--)
    {
        printf("%d\n", stack[i]);
    }
    printf("------------------------------\n");
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}