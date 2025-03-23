#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char code[7];
    char name[50];
    float value;
    int available;
} Item;

typedef struct {
    int unsigned id;
    char itemCode[7];
    float orderTotal;
    int unsigned quantity;
} Order;

int addOrder(int index, Order *ordPointer, Item *itemPointer, long unsigned int itemLen) {
    char fkItemCode[7];
    int orderQuantity;
    int itemFound = 0;
    int itemIndex;
    
    ordPointer->id = index;
    printf("Type the item code: ");
    fgets(fkItemCode, 7, stdin);
    
    for (int i = 0; i < (itemLen / sizeof(Item)); i++) {
        if (strcmp(itemPointer[i].code, fkItemCode) == 0) {
            strcpy(ordPointer->itemCode, fkItemCode);
            itemFound = 1;
            itemIndex = i;
            break;
        }
    }
    
    if (!itemFound) {
        printf("Item code is invalid. Try again");
        return 0;
    }
    
    printf("Type the ordered amount: ");
    scanf("%d", &orderQuantity);
    
    if ((itemPointer[itemIndex].available - orderQuantity) < 0) {
        printf("There are not enough items in the storage. Please check:\n");
        printf("%s - %s\n", itemPointer[itemIndex].code, itemPointer[itemIndex].name);
        printf("Ordered amount: %d\nAvailable amount: %d\n", orderQuantity, itemPointer[itemIndex].available);
    }
    
};

int main()
{
    Item item[2];
    Item *itemPointer = item;
    
    strcpy(item[0].code, "ST0001");
    strcpy(item[0].name, "Blue Shirt");
    item[0].value = 32.99;
    item[0].available = 4;
    
    strcpy(item[1].code, "ST0002");
    strcpy(item[1].name, "Yellow Shirt");
    item[1].value = 29.99;
    item[1].available = 10;
    
    
    Order *order = NULL;
    order = (Order *) malloc(sizeof(Order));
    int orderCount = 0;
    
    addOrder(orderCount, &order[orderCount], itemPointer, sizeof(item));
    
    free(order);
    
    return 0;
}