#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTS 4
#define PROMOCODE "Eid2025"
#define DISCOUNT 0.25

int productCodes[MAX_PRODUCTS] = {101, 102, 103, 104};
char productNames[MAX_PRODUCTS][50] = {"Milk", "Bread", "Eggs", "Butter"};
float prices[MAX_PRODUCTS] = {100.0, 200.0, 300.0, 150.0};
int inventoryQuantity[MAX_PRODUCTS] = {50, 10, 20, 8};

char customerName[50] = "N/A";
long long customer_cnic = 0;
int customerInfoEntered = 0;

int cartQuantities[MAX_PRODUCTS] = {0, 0, 0, 0};

float subTotal = 0.0;
float finalBill = 0.0;
int discountApplied = 0;
int billCalculated = 0;

void displayMenu();
void getCustomerInfo();
void displayInventory();
void addToCart();
void displayTotalBill();
void showInvoice();
void clearCart();
void clearInputBuffer();
int findProductIndex(int productCode);

int main()
{
    int choice;
    printf("Welcome to the Supermarket Management System\n");

    do
    {
        displayMenu();
        printf("Enter your choice(1-7): ");

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
            getCustomerInfo();
            break;
        case 2:
            displayInventory();
            break;
        case 3:
            addToCart();
            break;
        case 4:
            displayTotalBill();
            break;
        case 5:
            showInvoice();
            break;
        case 6:
            clearCart();
            break;
        case 7:
            printf("Exiting the program. Thank you!\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
        printf("\n----------------------------------------\n");

    } while (choice != 7);

    return 0;
}

void displayMenu()
{
    printf("\n--- Supermarket Menu ---\n");
    printf("1. Enter Customer Information\n");
    printf("2. Display Inventory\n");
    printf("3. Add Product to Cart\n");
    printf("4. Calculate and Display Total Bill\n");
    printf("5. Show Invoice\n");
    printf("6. Clear Cart\n");
    printf("7. Exit\n");
}

void getCustomerInfo()
{
    printf("Enter Customer Name: ");
    fgets(customerName, sizeof(customerName), stdin);
    customerName[strcspn(customerName, "\n")] = 0;

    printf("Enter Customer CNIC: ");
    while (scanf("%lld", &customer_cnic) != 1)
    {
        printf("Invalid CNIC. Please enter numbers only: ");
        clearInputBuffer();
    }
    clearInputBuffer();

    customerInfoEntered = 1;
    printf("Customer information recorded successfully.\n");
}

void displayInventory()
{
    printf("\n--- Inventory ---\n");
    printf("Code\tName\t\tPrice\t\tStock\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < MAX_PRODUCTS; i++)
    {

        printf("%d\t%-10s\t%-10.2f\t%d\n",
               productCodes[i],
               productNames[i],
               prices[i],
               inventoryQuantity[i]);
    }
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void addToCart()
{
    int code, quantity, index;
    displayInventory();

    printf("Enter Product Code to add to cart: ");
    if (scanf("%d", &code) != 1)
    {
        printf("Invalid code.\n");
        clearInputBuffer();
        return;
    }

    index = findProductIndex(code);

    if (index == -1)
    {
        printf("Product code %d not found in inventory.\n", code);
        clearInputBuffer();
        return;
    }

    printf("Enter Quantity for %s (Available: %d): ",
           productNames[index], inventoryQuantity[index]);
    if (scanf("%d", &quantity) != 1 || quantity <= 0)
    {
        printf("Invalid quantity.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (quantity > inventoryQuantity[index])
    {
        printf("Error: Not enough stock. Only %d units available.\n", inventoryQuantity[index]);
        return;
    }

    inventoryQuantity[index] -= quantity;

    cartQuantities[index] += quantity;

    billCalculated = 0;

    printf("Added %d of %s to cart.\n", quantity, productNames[index]);
    printf("Remaining stock: %d\n", inventoryQuantity[index]);
}

void displayTotalBill()
{
    printf("\n--- 4. Calculate Total Bill ---\n");
    subTotal = 0.0;
    discountApplied = 0;

    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        if (cartQuantities[i] > 0)
        {
            subTotal += cartQuantities[i] * prices[i];
        }
    }

    if (subTotal == 0.0)
    {
        printf("Your cart is empty.\n");
        billCalculated = 0;
        finalBill = 0.0;
        return;
    }

    printf("Current Subtotal: %.2f\n", subTotal);

    char promoCode[20];
    printf("Enter Promo Code (or press Enter to skip): ");
    fgets(promoCode, sizeof(promoCode), stdin);
    promoCode[strcspn(promoCode, "\n")] = 0;

    if (strcmp(promoCode, PROMOCODE) == 0)
    {
        float discountAmount = subTotal * DISCOUNT;
        finalBill = subTotal - discountAmount;
        discountApplied = 1;
        printf("Promo code applied! You saved %.2f\n", discountAmount);
    }
    else
    {
        finalBill = subTotal;
        discountApplied = 0;
        if (strlen(promoCode) > 0)
        {
            printf("Invalid promo code. No discount applied.\n");
        }
    }

    printf("----------------------------------\n");
    printf("Total Amount Payable: %.2f\n", finalBill);
    printf("----------------------------------\n");
    billCalculated = 1;
}

void showInvoice()
{
    if (customerInfoEntered == 0)
    {
        printf("Please enter customer information (Option 1) first.\n");
        return;
    }

    if (billCalculated == 0)
    {
        printf("Please calculate the total bill (Option 4) first.\n");
        printf("Your cart may have changed.\n");
        return;
    }

    printf("\n--- Invoice ---\n");
    printf("Customer Name: %s\n", customerName);
    printf("Customer CNIC: %lld\n", customer_cnic);
    printf("--------------------------------------------------\n");
    printf("Items Purchased:\n");
    printf("Code\tName\t\tQty\tPrice\t\tTotal\n");
    printf("--------------------------------------------------\n");

    int itemsInCart = 0;
    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        if (cartQuantities[i] > 0)
        {
            itemsInCart = 1;
            float itemTotal = prices[i] * cartQuantities[i];
            printf("%d\t%-10s\t%d\t%-10.2f\t%.2f\n",
                   productCodes[i],
                   productNames[i],
                   cartQuantities[i],
                   prices[i],
                   itemTotal);
        }
    }

    if (itemsInCart == 0)
    {
        printf("No items in cart.\n");
    }

    printf("--------------------------------------------------\n");
    printf("Subtotal: \t\t\t\t\t%.2f\n", subTotal);

    if (discountApplied)
    {
        float discountAmount = subTotal * DISCOUNT;
        printf("Discount (25%%): \t\t\t\t-%.2f\n", discountAmount);
    }

    printf("--------------------------------------------------\n");
    printf("Total Amount Paid: \t\t\t\t%.2f\n", finalBill);
    printf("--------------------------------------------------\n");
    printf("Thank you for shopping!\n");
}

void clearCart()
{

    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        if (cartQuantities[i] > 0)
        {
            inventoryQuantity[i] += cartQuantities[i];
            cartQuantities[i] = 0;
        }
    }

    subTotal = 0.0;
    finalBill = 0.0;
    billCalculated = 0;
    discountApplied = 0;

    printf("Cart cleared and items returned to stock.\n");
}

int findProductIndex(int productCode)
{
    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        if (productCodes[i] == productCode)
        {
            return i;
        }
    }
    return -1;
}