#include <stdio.h>
#include <string.h>

#define TOGGLE_MASK 18

void reverseString(char str[]);
void toggleBits(char str[]);
void encode(char str[]);
void decode(char str[]);
void clearInputBuffer();

int main()
{
    int choice = 0;
    char message[256];

    printf("--- TCS Secure Message Utility ---\n");

    do
    {
        printf("\n--- Main Menu ---\n");
        printf("1. Encode a Message\n");
        printf("2. Decode a Message\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (choice == 1 || choice == 2)
        {
            printf("Enter your message: ");
            fgets(message, sizeof(message), stdin);
            message[strcspn(message, "\n")] = '\0';
        }

        switch (choice)
        {
        case 1:
            encode(message);
            printf("\nEncoded Message: %s\n", message);
            break;
        case 2:
            decode(message);
            printf("\nDecoded Message: %s\n", message);
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please select from 1-3.\n");
        }
    } while (choice != 3);

    return 0;
}

void reverseString(char str[])
{
    int start = 0;
    int end = strlen(str) - 1;
    char temp;

    while (start < end)
    {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void toggleBits(char str[])
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        str[i] = str[i] ^ TOGGLE_MASK;
    }
}

void encode(char str[])
{
    printf("Encoding... (Reversing, then Toggling)");
    reverseString(str);
    toggleBits(str);
}

void decode(char str[])
{
    printf("Decoding... (Toggling, then Reversing)");
    toggleBits(str);
    reverseString(str);
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}