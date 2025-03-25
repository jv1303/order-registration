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

// order struct
typedef struct {
    int unsigned id;
    char itemCode[7];
    int unsigned quantity;
    float orderTotal;
} Order;

// function to register new orders
int addOrder(int index, Order *ordPointer, Item *item, long unsigned int itemLen) {
    char fkItemCode[7];
    int orderQuantity;
    int itemFound = 0;
    int itemIndex;

    ordPointer[index].id = index;
    
    printf("====== Order registration ======\n");
    printf("Type the item code: ");
    fgets(fkItemCode, 7, stdin);
    
    if (fkItemCode[strlen(fkItemCode) - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    for (int i = 0; i <= itemLen; i++) {
        if (strcmp(item[i].code, fkItemCode) == 0) {
            strcpy(ordPointer[index].itemCode, fkItemCode);
            itemFound = 1;
            itemIndex = i;
            
            break;
        }
    }
    
    if (!itemFound) {
        system("clear");
        printf("====== Order registration ======\n");
        printf("Item code is invalid. Please, try again.\n");
        return 0;
    }
    
    printf("Type the ordered amount: ");
    int t;
    if (!scanf("%d", &t)) {
        system("clear");
        printf("====== Order registration ======\n");
        printf("You must enter a integer number.");
    }

    orderQuantity = t;
    getchar();
    
    if ((item[itemIndex].available - orderQuantity) < 0) {
        system("clear");
        printf("====== Order registration ======\n");
        printf("There are not enough items in the storage. Please check:\n\n");
        printf("%s - %s\n", item[itemIndex].code, item[itemIndex].name);
        printf("Ordered amount: %d\nAvailable amount: %d\n", orderQuantity, item[itemIndex].available);
        return 0;
    }
    
    item[itemIndex].available -= orderQuantity;
    ordPointer[index].quantity = orderQuantity;
    ordPointer[index].orderTotal = item[itemIndex].value * orderQuantity;
    
    system("clear");
    printf("====== Order registration ======\n");
    printf("Order registered successfully!\n");
    
    return 1;
};

int registerItem(int index, Item *item) {
    char code[1000];
    float value = 0;
    char name[50];
    
    printf("======= Item registration ======\n");
    printf("!! The item code must have 6 characters !!\n");
    printf("!!       and cannot be duplicated       !!\n\n");
    printf("Type the new item code: ");
    
    fgets(code, 1000, stdin);
    
    size_t len = strlen(code);
        if (len > 0 && code[len - 1] == '\n') {
            code[len - 1] = '\0';
    }
    
    if (strlen(code) != 6) {
        system("clear");
        printf("======= Item registration ======\n");
        printf("The item code must have 6 characters.\n");
        printf("Please, try again.\n");
        return 0;
    }
    
    for (int i = 0; i <= index; i++) {
        if (strcmp(item[i].code, code) == 0) {
            system("clear");
            printf("======= Item registration ======\n");
            printf("Item code already exists. Please, try again.\n");
            return 0;
        }
    }
    
    printf("Type the item name: ");
    fgets(name, 50, stdin);
    
    len = strlen(name);
        if (len > 0 && name[len - 1] == '\n') {
            name[len - 1] = '\0';
    }
    
    if (strlen(code) > 50) {
        system("clear");
        printf("======= Item registration ======\n");
        printf("Name too long! Please, try again.\n");
        return 0;
    }
    
    printf("Type the value per unit: ");
    
    int valueReturn = scanf("%f", &value);
    getchar();
    
    if (!valueReturn || value <= 0) {
        system("clear");
        printf("======= Item registration ======\n");
        printf("The item value must be a positive number. Please, try again.\n");
        return 0;
    }
    
    strcpy(item[index].code, code);
    strcpy(item[index].name, name);
    item[index].value = value;

    system("clear");
    printf("======= Item registration ======\n");
    printf("Item registered successfully!\n");
    return 1;
}


void registerMenu(int *orderCount, Order **order, Item **item, int *itemCount) {
    int input;
    int funcReturn;
    int ord = *orderCount;
    int itm = *itemCount;
    
    do {
        printf("============= Menu =============\n");
        printf("Choose an option:\n");
        printf("1. New order\n");
        printf("2. New Item\n");
        printf("3. Back\n");
        scanf("%d", &input);
        getchar();
        system("clear");
        
       switch (input) {
            case 1:
                    *order = (Order *) realloc(*order, (*orderCount + 1) * sizeof(Order));
                    funcReturn = addOrder(ord, *order, *item, itm);
                    *orderCount += funcReturn;
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
                break;
        }
    } while (input != 3);
}

int addItems(int itemLen, Item **itemPointer) {
    Item *item = *itemPointer;
    char fkItemCode[7];
    int itemFound = 0;
    int itemIndex;
    
    printf("========== Add Items ===========\n");
    printf("Type the item code: ");
    
    fgets(fkItemCode, 7, stdin);
    
    if (fkItemCode[strlen(fkItemCode) - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    for (int i = 0; i <= itemLen; i++) {
        if (strcmp(item[i].code, fkItemCode) == 0) {
            itemFound = 1;
            itemIndex = i;
            break;
        }
    }
    
    if (!itemFound) {
        system("clear");
        printf("========== Add Items ===========\n");
        printf("Item code is invalid. Please, try again.\n");
        return 0;
    }
    
    int amount;
    printf("Item: %s\n Available: %d\n", item[itemIndex].name, item[itemIndex].available);
    printf("Type how many items are being added to the storage: ");
    int scanfReturn = (scanf("%d", &amount));
    getchar();
    
    if (!scanfReturn || amount <= 0) {
        system("clear");
        printf("========== Add Items ===========\n");
        printf("You must enter a positive integer. Operation failed.\n");
        return 0;
    }
    
    item[itemIndex].available += amount;
    
    system("clear");
    printf("========== Add Items ===========\n");
    printf("Success!\n");
    return 1;
}

int main()
{
    Item *item = NULL;
    item = (Item *) malloc(2 * sizeof(Item));
    int itemCount = 0;
    int *pItmCount = &itemCount;
    //Item *item = item;
    
    //strcpy(item[0].code, "ST0001");
    //strcpy(item[0].name, "Blue Shirt");
    //item[0].value = 32.99;
    //item[0].available = 4;
    
    //strcpy(item[1].code, "ST0002");
    //strcpy(item[1].name, "Yellow Shirt");
    //item[1].value = 29.99;
    //item[1].available = 10;
    
    Order *order = NULL;
    order = (Order *) malloc(sizeof(Order));
    int orderCount = 0;
    int *pOrdCount = &orderCount;
    
    int input;
    do {
        printf("============= Menu =============\n");
        printf("Choose an option:\n");
        printf("1. Register\n");
        printf("2. Add items\n");
        printf("3. Quit\n");
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
                break;
            default:
                break;
        }
    } while (input != 3);
    
    for (int i = 0; i < itemCount; i++) {
        printf("\nCodigo: %s\nItem: %s\nValor: %.2f\nEstoque: %d\n", item[i].code, item[i].name, item[i].value, item[i].available);
    }
    
    for (int i = 0; i < orderCount; i++) {
        printf("\nId: %d\nItem: %s\nQuantidade: %d\nValor total: %.2f\n", order[i].id, order[i].itemCode, order[i].quantity, order[i].orderTotal);
    }
    
    return 0;
    
    free(order);
    free(item);
    
    return 0;
}



