#include <stdio.h>

#define MAX_BOOKS 100

int isbn[MAX_BOOKS];
char titles[MAX_BOOKS][50];
float prices[MAX_BOOKS];
int quantities[MAX_BOOKS];
int bookCount = 0;

void display();
void addBook();
void processSale();
void low_stock_report();

int main()
{
    int choice;

    do
    {
        printf("\n--- Bookstore Inventory Management ---\n");
        printf("1. Display Inventory\n");
        printf("2. Add New Book\n");
        printf("3. Process Sale\n");
        printf("4. Low Stock Report\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            display();
            break;
        case 2:
            addBook();
            break;
        case 3:
            processSale();
            break;
        case 4:
            low_stock_report();
            break;
        case 5:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void display()
{
    printf("\n--- Inventory ---\n");
    printf("ISBN\tTitle\t\tPrice\tQuantity\n");
    for (int i = 0; i < bookCount; i++)
    {
        printf("%d\t%s\t%.2f\t%d\n", isbn[i], titles[i], prices[i], quantities[i]);
    }
}

void addBook()
{
    if (bookCount >= MAX_BOOKS)
    {
        printf("Inventory full. Cannot add more books.\n");
        return;
    }

    printf("Enter ISBN: ");
    scanf("%d", &isbn[bookCount]);
    printf("Enter Title: ");
    scanf(" %[^\n]", titles[bookCount]);
    printf("Enter Price: ");
    scanf("%f", &prices[bookCount]);
    printf("Enter Quantity: ");
    scanf("%d", &quantities[bookCount]);

    bookCount++;
    printf("Book added successfully.\n");
}

void processSale()
{
    int saleIsbn, saleQuantity;
    printf("Enter ISBN of the book to sell: ");
    scanf("%d", &saleIsbn);
    printf("Enter quantity to sell: ");
    scanf("%d", &saleQuantity);

    for (int i = 0; i < bookCount; i++)
    {
        if (isbn[i] == saleIsbn)
        {
            if (quantities[i] >= saleQuantity)
            {
                quantities[i] -= saleQuantity;
                printf("Sale processed. Remaining stock: %d\n", quantities[i]);
            }
            else
            {
                printf("Insufficient stock. Available quantity: %d\n", quantities[i]);
            }
            return;
        }
    }
    printf("Book with ISBN %d not found.\n", saleIsbn);
}
void low_stock_report()
{
    int threshold;
    printf("Enter stock threshold: ");
    scanf("%d", &threshold);

    printf("\n--- Low Stock Report (Threshold: %d) ---\n", threshold);
    printf("ISBN\tTitle\t\tPrice\tQuantity\n");
    for (int i = 0; i < bookCount; i++)
    {
        if (quantities[i] < threshold)
        {
            printf("%d\t%s\t%.2f\t%d\n", isbn[i], titles[i], prices[i], quantities[i]);
        }
    }
}