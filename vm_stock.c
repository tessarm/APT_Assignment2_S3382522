/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/
/** linked list code from module 9 **/
#include "vm_stock.h"
#include <stdbool.h>
#include <stdlib.h>
#include "vm_system.h"

/**
 * vm_stock.c this is the file where you will implement the
 * interface functions for managing the stock list.
 **/

/**
 * Some example functions:
 * create list, free list, create node, free node, insert node, etc...
 */

 
 List * initialiselist()
{
    List * list = malloc(sizeof(*list));
    if(list != NULL)
    {
        list->head = NULL;
        list->size = 0;
    }

    return list;
}

bool addToList(List * list, Stock * stock)
{
    Node * previousNode, * currentNode;

    Node * newNode = malloc(sizeof(*newNode));
    if(newNode == NULL)
    {
        return false;
    }
    newNode->data = malloc(sizeof(*newNode->data));
    if(newNode->data == NULL)
    {
        free(newNode);
        return false;
    }

    *newNode->data = *stock;

    newNode->next = NULL;

    previousNode = NULL;
    currentNode = list->head;
    while(currentNode != NULL)
    {
        if(strcmp(stock->id, currentNode->data->id) < 0)
        {
            break;
        }

        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if(list->head == NULL)
    {
        /* Empty list. */
        list->head = newNode;
    }
    else if(previousNode == NULL)
    {
        /* Inserting at the head. */
        newNode->next = list->head;
        list->head = newNode;
    }
    else
    {
        previousNode->next = newNode;
        newNode->next = currentNode;
    }
    list->size++;

    return true;
}

void printList(List * list)
{
	int nameMax = 0, availMax = 0, len = 0, i;	
	
    Node * node = list->head;
	
	while(node != NULL)
    {	
		len = strlen(node->data->name);
		if(len > nameMax){
			nameMax = len;}
		node = node->next;
		
	}
	
	Node * nodec = list->head;
	while(nodec != NULL)
    {	
		len = lenHelper(nodec->data->onHand);
		if(len > availMax){
			availMax = len;}
		nodec = nodec->next;
	}
	printf("Items Menu\n\n");
	printf("ID    | Name");
	i = nameMax - 4;
	while(i >= 0){
		printf(" ");
		i = i-1;
		}
	printf("| Available | Price\n");

	printf("-----------");
	i = nameMax - 5;
	while(i >= 0){
		printf("-");
		i = i-1;
		}
	printf("---------------------\n");

	Node * nodeb = list->head;
    while(nodeb != NULL)
    {

		printf("%s | %s",nodeb->data->id, nodeb->data->name);
		i = nameMax - strlen(nodeb->data->name);
		while(i >= 0){
			printf(" ");
			i = i-1;}
		printf("| %u", nodeb->data->onHand);
		i = 9 - lenHelper(nodeb->data->onHand);
		while(i >= 0){
			printf(" ");
			i = i-1;}
		printf("| $%d.%d\n", nodeb->data->price.dollars,nodeb->data->price.cents);
		
        nodeb = nodeb->next;
    }
    printf("\n");
}

List * freeList(List * list)
{
    Node * node = list->head;
    while(node != NULL)
    {
        Node * temp = node;
        node = node->next;

        free(temp->data);
        free(temp);
    }
    free(list);

    return NULL;
}


int lenHelper(unsigned x) {
    if(x>=1000000000) return 10;
    if(x>=100000000) return 9;
    if(x>=10000000) return 8;
    if(x>=1000000) return 7;
    if(x>=100000) return 6;
    if(x>=10000) return 5;
    if(x>=1000) return 4;
    if(x>=100) return 3;
    if(x>=10) return 2;
    return 1;
}


int purchaseItem(List * list){
	
	int centsOwed;
	struct stock tempStockB;
	char user_inputA[6], *tokenA[6];
    user_inputA[0] = 0;

	printf("Purchase Item\n");
	printf("-------------\nPlease enter the id of the item you wish to purchase:");

	while (strlen(user_inputA) <= 1 || strlen(user_inputA) > 82) {
        fgets(user_inputA, sizeof(user_inputA), stdin); /* fgets statement to start the menu*/
        size_t len = strlen(user_inputA);
        if (len > 0 && user_inputA[len-1] == '\n') {
        user_inputA[--len] = '\0';} /* shaves off the /n at the ends of the stdin stream input*/
	}
	
	

	tokenA[0] = strtok(user_inputA, "\n");

	
    Node * node = list->head;
    while(node != NULL)
    {
		if(strcmp(tokenA[0], node->data->id) == 0){
		if(node->data->onHand <= 0){
			printf("not enough stock\n");
			return 0;}
		/*exit function*/
		tempStockB = *node->data;}

		node = node->next;
    }
	centsOwed = tempStockB.price.dollars * 100;
	centsOwed = centsOwed + tempStockB.price.cents;
	printf("You have selected \"%s\". This will cost you $%d.%d.\n", tempStockB.desc, tempStockB.price.dollars, tempStockB.price.cents);
	printf("Please hand over the money - type in the value of each note/coin in cents.\n");
	printf("Press enter on a new and empty line to cancel this purchase:\n");
	
	while(centsOwed > 0){
	printf("You still need to give us %d\n", centsOwed);
	int number = 0;	
	scanf("%i", &number);
	centsOwed = centsOwed - number;	
	}

	
	centsOwed = abs(centsOwed);
	if(centsOwed == 0){
		printf("Thank you.");}
		
	else{
		printf("Thank you. Here is your %s, and your change of %d cents.\n", tempStockB.name, centsOwed);
	}
	tempStockB.onHand = tempStockB.onHand - 1;
	Node * noded = list->head;
    while(noded != NULL)
    {
		if(strcmp(tempStockB.name, noded->data->name) == 0){
		*noded->data = tempStockB;}

		noded = noded->next;
    }
	

	

	return 1;
}

void removeItem(List * list){

	Node * node = list->head;
	Node * prev = NULL;
 	char user_inputA[6], *tokenA[6];
    user_inputA[0] = 0;
	
	
	
 	printf("Remove Item\n");
	printf("-------------\nPlease enter the id of the item you wish to remove:\n");
 	while (strlen(user_inputA) <= 1 || strlen(user_inputA) > 82) {
        fgets(user_inputA, sizeof(user_inputA), stdin); /* fgets statement to start the menu*/
        size_t len = strlen(user_inputA);
        if (len > 0 && user_inputA[len-1] == '\n') {
        user_inputA[--len] = '\0';} /* shaves off the /n at the ends of the stdin stream input*/
	}
	
	tokenA[0] = strtok(user_inputA, "\n");
    while(node != NULL)
    {
		if(strcmp(tokenA[0], node->data->id) == 0){
			if(prev){
			prev->next = node->next;	
			printf("%s deleted!\n\n", tokenA[0]);}
			else{
				list->head = list->head->next;
				printf("%s deleted!\n\n", tokenA[0]);}
			}
			prev = node;
			node = node->next;

;
    }
	
	




}


void resetStock(List * list)
{	
    Node * node = list->head;
	while(node != NULL)
    {	
		node->data->onHand = DEFAULT_STOCK_LEVEL;
		node = node->next;
	}
	
}



void addItem(List * list){
	
	int cents, dollars, i = 1;
	struct stock tempStock;
	char user_inputA[6], *tokenA[6];
	char* idtoken[5];
    user_inputA[0] = 0;
	Node * node = list->head;
	int tempid;
   	 while(node != NULL)
    {

		node = node->next;
		i++;
    }
	char newId[4] = "I";
	int x = lenHelper(i);
	x = 4 - x;
	printf("%d\n", x);
	int j;
	for( j = 0; j <x; j++){
		strcat(newId, "0");
	}
	char snum[5];
	sprintf(snum, "%d", i);
	strcat(newId,snum);
	
	
	strcpy(tempStock.id, newId);
	printf("This new meal item will have the item id of %s\n",tempStock.id);
	printf("Enter the item name:\n");

	while (strlen(user_inputA) <= 1 || strlen(user_inputA) > 82) {
        fgets(user_inputA, sizeof(user_inputA), stdin); /* fgets statement to start the menu*/
        size_t len = strlen(user_inputA);
        if (len > 0 && user_inputA[len-1] == '\n') {
        user_inputA[--len] = '\0';} /* shaves off the /n at the ends of the stdin stream input*/
	}
	tokenA[0] = strtok(user_inputA, "\n");
	strcpy(tempStock.name, tokenA[0]);

	printf("Enter the item description:\n");
	
	char user_input[6], *token[6];
    user_input[0] = 0;
	while (strlen(user_input) <= 1 || strlen(user_input) > 82) {
        fgets(user_input, sizeof(user_input), stdin); /* fgets statement to start the menu*/
        size_t len = strlen(user_input);
        if (len > 0 && user_input[len-1] == '\n') {
        user_inputA[--len] = '\0';} /* shaves off the /n at the ends of the stdin stream input*/
	}
	token[0] = strtok(user_input, "\n");
	strcpy(tempStock.desc, token[0]);
	printf("Enter the price for this item (dollars.cents):\n");
	
	char user_inputq[30], *tokenq[30];
    user_inputq[0] = 0;
	while (strlen(user_inputq) <= 1 || strlen(user_inputq) > 82) {
        fgets(user_inputq, sizeof(user_inputq), stdin); /* fgets statement to start the menu*/
        size_t len = strlen(user_inputq);
        if (len > 0 && user_inputq[len-1] == '\n') {
        user_inputA[--len] = '\0';} /* shaves off the /n at the ends of the stdin stream input*/
	}

	i = 0;
	tokenq[0] = strtok(user_inputq, ".\n");
    while (tokenq[i] != NULL) {
        i++;
        tokenq[i] = strtok(NULL, ".");
    }
	
	dollars = atoi(tokenq[0]);
	cents = atoi(tokenq[1]);
	printf("%d . %d\n", dollars, cents);
	tempStock.price.dollars = dollars, tempStock.price.cents = cents;

	printf("This item - \"%s\" has now been added to the menu\n",tempStock.desc);
	
	addToList(list, &tempStock);

}


int saveAndClose(List * list, FILE *fp){
	    
	Node * node = list->head;
	while(node != NULL)
    {	
		fprintf(fp,"%s|%s|%s|%i.%i|%i\n",node->data->id, node->data->name, node->data->desc, node->data->price.dollars, node->data->price.cents, node->data->onHand);
		node = node->next;
		
	}
	freeList(list);
	fclose(fp);
	return 0;

}
