#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int unsigned id;
    char item[50];
    float value;
    int unsigned count;
} Order;

int addOrder(int index, Order *ordPointer) {
    ordPointer->id = index;
    printf("Digite o item do pedido: ");
    fgets(ordPointer->item , 50, stdin);
};

int main()
{
    Order *order = NULL;
    order = (Order *) malloc(sizeof(Order));
    Order *p = order;
    int orderCount = 0;
    
    addOrder(orderCount, &order[orderCount]);
    printf("Id: %d\nItem: %s\n", order[0].id, order[0].item);
    
    return 0;
}