#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// item struct
typedef struct {
    char code[7];
    char name[50];
    float value;
    int available;
} Item;

// order sctruct
typedef struct {
    int unsigned id;
    char itemCode[7];
    int unsigned quantity;
    float orderTotal;
} Order;

// function to register new orders
int addOrder(int index, Order *ordPointer, Item *item, long unsigned int itemLen) {
    char fkItemCode[7]; // input for item code
    int orderQuantity; // input for item quantity
    int itemFound = 0; // flag to indicate if item was found
    int itemIndex; // will store the index of the matched item
    
    // item code input
    printf("====== Order Registration ======\n");
    printf("Enter item code: ");
    fgets(fkItemCode, 7, stdin);
    
    // clears fgets leftover buffer to make string comparison work correctly
    if (fkItemCode[strlen(fkItemCode) - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    // checks if item exists by comparing codes
    for (int i = 0; i <= itemLen; i++) {
        if (strcmp(item[i].code, fkItemCode) == 0) {
            itemFound = 1;
            itemIndex = i;
            break;
        }
    }
    
    // if item not found, inform the user and cancel the order
    if (!itemFound) {
        system("clear");
        printf("====== Order Registration ======\n");
        printf("Invalid item code. Please try again.\n");
        return 0;
    }
    
    // input for the order quantity
    printf("Enter the quantity: ");
    int t;
    
    // checks if the input is an integer number
    if (!scanf("%d", &t) || t <= 0) {
        system("clear");
        printf("====== Order Registration ======\n");
        printf("You must enter a positive number.\n");
        getchar();
        return 0;
    }
    orderQuantity = t;
    getchar();
    
    // check if there’s enough stock to fulfill the order
    if ((item[itemIndex].available - orderQuantity) < 0) {
        system("clear");
        printf("====== Order Registration ======\n");
        printf("Not enough items in stock.\n\n");
        printf("%s - %s\n", item[itemIndex].code, item[itemIndex].name);
        printf("Requested: %d\nAvailable: %d\n", orderQuantity, item[itemIndex].available);
        return 0;
    }
    
    // if all validations pass, save the order
    strcpy(ordPointer[index].itemCode, fkItemCode); // item code
    ordPointer[index].id = index; // order id
    item[itemIndex].available -= orderQuantity; // update stock
    ordPointer[index].quantity = orderQuantity; // order quantity
    ordPointer[index].orderTotal = item[itemIndex].value * orderQuantity; // order total
    
    // success message
    system("clear");
    printf("====== Order Registration ======\n");
    printf("Order registered successfully!\n");
    printf("Order ID: %d\n", index);
    return 1;
};

// item registration
int registerItem(int index, Item *item) {
    char code[50]; // input for the item code
    float value = 0; // item price
    char name[50]; // item name

    // get item code
    printf("====== Item Registration =======\n");
    printf("Note: Item code must have 6 characters and be unique.\n\n");
    printf("Enter item code: ");
    
    fgets(code, 50, stdin);
    
    // removes new line
    size_t len = strlen(code);
        if (len > 0 && code[len - 1] == '\n') {
            code[len - 1] = '\0';
    }
    
    // checks the code length
    if (strlen(code) != 6) {
        system("clear");
        printf("====== Item Registration =======\n");
        printf("Item code must have exactly 6 characters.\n");
        return 0;
    }
    
    // checks if the code already exists
    for (int i = 0; i <= index; i++) {
        if (strcmp(item[i].code, code) == 0) {
            system("clear");
            printf("====== Item Registration =======\n");
            printf("This code already exists. Please try again.\n");
            return 0;
        }
    }
    
    // gets the item name
    printf("Enter item name: ");
    fgets(name, 50, stdin);

    len = strlen(name);
        if (len > 0 && name[len - 1] == '\n') {
            name[len - 1] = '\0';
    }
    
    // validate name length
    if (strlen(code) > 50) {
        system("clear");
        printf("====== Item Registration =======\n");
        printf("Name is too long. Please try again.\n");
        return 0;
    }
    
    // gets item price
    printf("Enter item price: ");
    int valueReturn = scanf("%f", &value); // valueReturn validates if the input is a number
    getchar();

    // checks if the input is a positive number
    if (!valueReturn || value <= 0) {
        system("clear");
        printf("====== Item Registration =======\n");
        printf("Price must be a positive number.\n");
        return 0;
    }
    
    // registers the item
    strcpy(item[index].code, code);
    strcpy(item[index].name, name);
    item[index].value = value;

    system("clear");
    printf("======= Registro de Item =======\n");
    printf("Item registered successfully!\n");
    return 1; // returns 1 for true
}

// function to add stock to an existing item
int addItems(int itemLen, Item **itemPointer) {
    Item *item = *itemPointer;
    char fkItemCode[7];
    int itemFound = 0;
    int itemIndex;
    
    // gets the item code
    printf("=========== Add Stock ==========\n");
    printf("Enter the item code: ");
    
    fgets(fkItemCode, 7, stdin);
    
    // removes new line so string compare works properly
    if (fkItemCode[strlen(fkItemCode) - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    // checks if the item exists
    for (int i = 0; i <= itemLen; i++) {
        if (strcmp(item[i].code, fkItemCode) == 0) {
            itemFound = 1;
            itemIndex = i;
            break;
        }
    }
    
    // if the item is not found, cancel operation
    if (!itemFound) {
        system("clear");
        printf("=========== Add Stock ==========\n");
        printf("Invalid item code. Please try again.\n");
        return 0;
    }
    
    // how many items are being added to stock
    int amount;
    system("clear");
    printf("=========== Add Stock ==========\n");
    printf("Item: %s\nAvailable: %d\n", item[itemIndex].name, item[itemIndex].available);
    printf("Enter the quantity to add: ");
    int scanfReturn = (scanf("%d", &amount));
    getchar();
    
    // checks if the input is a positive integer
    if (!scanfReturn || amount <= 0) {
        system("clear");
        printf("=========== Add Stock ==========\n");
        printf("You must enter a positive number.\n");
        return 0;
    }
    
    // add to stock
    item[itemIndex].available += amount;
    
    system("clear");
    printf("=========== Add Stock ==========\n");
    printf("Stock updated successfully!\n");
    return 1;
}

// registration menu
void registerMenu(int *orderCount, Order **order, Item **item, int *itemCount) {
    int input;
    int funcReturn; // checks if a function returned true of false
    int ord = *orderCount; // order count casting
    int itm = *itemCount; // item count casting
    
    do {
        printf("============= Menu =============\n");
        printf("Choose an option:\n");
        printf("1. Add new order\n");
        printf("2. Add new item\n");
        printf("3. Back\n");
        scanf("%d", &input);
        getchar();
        system("clear");
        
       switch (input) {
            case 1:
                    *order = (Order *) realloc(*order, (*orderCount + 1) * sizeof(Order)); // reallocates memory
                    funcReturn = addOrder(ord, *order, *item, itm);
                    *orderCount += funcReturn; // add to the order count the function return (0 if false; 1 if true)
                    ord = *orderCount;
                break;
            case 2:
                    *item = (Item *) realloc(*item, (*itemCount + 1) * sizeof(Item));
                    funcReturn = registerItem(itm, *item);
                    *itemCount += funcReturn;
                    itm = *itemCount;
                break;
            case 3:
                break;
            default:
                printf("Invalid Option.\n");
                break;
        }
    } while (input != 3);
}

// list of the registered orders
void viewOrder(int orderCount, Order *order) {
    printf("============= Order List =============\n");
    printf("%-8s %-8s %-12s %-12s\n\n", "ID", "Item", "Quantity", "Total");
    for (int i = 0; i < orderCount; i++) {
        printf("%-8d %-8s %-12d $%-12.2f\n", order[i].id, order[i].itemCode, order[i].quantity, order[i].orderTotal);
    }
    printf("\nPress ENTER to continue...");
    getchar();
    system("clear");
    
}

// list of the registered items
void viewItem(int itemCount, Item *item) {
    printf("====================== Item List =======================\n");
    printf("%-8s %-25s %-11s %-6s\n\n", "Code", "Item", "Price", "Stock");
    for (int i = 0; i < itemCount; i++) {
        printf("%-8s %-25s $%-10.2f %-6d\n", item[i].code, item[i].name, item[i].value, item[i].available);
    }
    printf("\nPress ENTER to continue...");
    getchar();
    system("clear");
}

// item search
int searchItem(int itemCount, Item *item) {
    int found = 0;
    int itemIndex; // gets the found item index
    char input[7];
    
    // item code input
    printf("=========== Item Search ========\n");
    printf("Enter the item code: ");
    fgets(input, 7, stdin);
    
    // clears \n
    if (input[strlen(input) - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    // code search
    for (int i = 0; i <= itemCount; i++) {
        if (strcmp(item[i].code, input) == 0) {
            found = 1;
            itemIndex = i;
            break;
        }
    }

    // result
    system("clear");
    if (!found) {
        printf("=========== Item Search ========\n");
        printf("Invalid item code. Please try again.\n");
    } else {
        printf("=========== Item Search ========\n");
        printf("%-15s %s\n", "Code:", item[itemIndex].code);
        printf("%-15s %s\n", "Item:", item[itemIndex].name);
        printf("%-15s $%.2f\n", "Price:", item[itemIndex].value);
        printf("%-15s %d\n", "Stock:", item[itemIndex].available);
    }
    
    printf("\nPress ENTER to continue...");
    getchar();
    system("clear");
}

// order search
int searchOrder(int orderCount, Order *order) {
    int found = 0;
    int orderIndex;
    int input; 
    
    // input do ID do pedido
    printf("========== Order Search ========\n");
    printf("Enter the order ID: ");
    int t;
    
    // checks if the input is an integer number
    if (!scanf("%d", &t)) {
        system("clear");
        printf("========== Order Search ========\n");
        printf("You must enter an integer number.\n");
    } else {
        getchar();
        input = t;
        
        // order search
        for (int i = 0; i <= orderCount; i++) {
            if (order[i].id == input) {
                found = 1;
                orderIndex = i;
                break;
            }
        }
    
        system("clear");
        
        // result
        if (!found) {
            printf("========== Order Search ========\n");
            printf("Invalid order ID. Please try again.\n");
        } else {
            printf("========== Order Search ========\n");
            printf("%-15s %d\n", "Order ID:", order[orderIndex].id);
            printf("%-15s %s\n", "Item Code:", order[orderIndex].itemCode);
            printf("%-15s %d\n", "Quantity:", order[orderIndex].quantity);
            printf("%-15s $%.2f\n", "Total:", order[orderIndex].orderTotal);
        }
    }
    
    printf("\nPress ENTER to continue...");
    getchar();
    system("clear");
}

// consult menu
void consultMenu(int *orderCount, Order **order, Item **item, int *itemCount) {
    int input;
    int ord = *orderCount;
    int itm = *itemCount;
    
    do {
        printf("============= Menu =============\n");
        printf("Choose an option:\n");
        printf("1. List orders\n");
        printf("2. List items\n");
        printf("3. Search order\n");
        printf("4. Search item\n");
        printf("5. Back\n");
        scanf("%d", &input);
        getchar();
        system("clear");
        
       switch (input) {
            case 1:
                viewOrder(ord, *order);
                break;
            case 2:
                viewItem(itm, *item);
                break;
            case 3:
                searchOrder(ord, *order);
                break;
            case 4:
                searchItem(itm, *item);
                break;
            case 5:
                break;
            default:
                printf("Invalid Option.\n");
                break;
        }
    } while (input != 5);
}

int main()
{
    // item vector memory allocation
    Item *item = NULL;
    item = (Item *) malloc(2 * sizeof(Item));
    int itemCount = 0;
    int *pItmCount = &itemCount;
    
    // order vector memory allocation
    Order *order = NULL;
    order = (Order *) malloc(sizeof(Order));
    int orderCount = 0;
    int *pOrdCount = &orderCount;
    
    int input;
    do {
        printf("============= Menu =============\n");
        printf("Choose an option:\n");
        printf("1. Resgister menu\n");
        printf("2. Add stock to existing item\n");
        printf("3. Consult Menu\n");
        printf("4. Quit\n");
        scanf("%d", &input);
        getchar();
        system("clear");
        
        switch (input) {
            case 1:
                registerMenu(pOrdCount, &order, &item, pItmCount);
                break;
            case 2:
                addItems(itemCount, &item);
                break;
            case 3:
                consultMenu(pOrdCount, &order, &item, pItmCount);
                break;
            case 4:
                break;
            default:
                printf("Invalid Option.\n");
                break;
        }
    } while (input != 4);

    printf("System shutdown.");
    
    free(order);
    free(item);
    
    return 0;
}
