/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018


******************************************************************************/

#include "vm.h"
#include "vm_system.h"
#include <stdbool.h>

int main(int argc, char ** argv)
{
	
	List * linkedList;
    linkedList = initialiselist();
	

	char const* const fileName = argv[1]; 
    FILE* file = fopen(fileName, "r"); 
    char line[2048];
	char *token[80];
	char *tempID, *tempName, *tempDesc, *ptr, *temp;
	Price tempPrice;
	unsigned tempOnHand;
	struct stock tempStock;



	


    while (fgets(line, sizeof(line), file)) {
		int i = 0;
		token[0] = strtok(line, "|");
		while (token[i] != NULL) {
			i++;
			token[i] = strtok(NULL, "|");

		}
		tempID = token[0];	
		tempDesc = token[2];
		tempName = token[1];
		tempOnHand = strtoul(token[4], &ptr, 10);

		
 
		/*go through and make a stock object with each token, then add to list*/
		
		strcpy(tempStock.id, tempID);
		strcpy(tempStock.name, tempName);
		strcpy(tempStock.desc, tempDesc);
		
		temp = strtok(token[3], ".");
		tempPrice.dollars = strtoul(temp, &ptr, 10);
		temp = strtok(NULL, ".");
		tempPrice.cents = strtoul(temp, &ptr, 10);
		tempStock.price = tempPrice;
		tempStock.onHand = tempOnHand;
		


		
		addToList(linkedList, &tempStock);
	}

    fclose(file);
	
	int loopnumber = 1;
	while(loopnumber == 1){
		printf("Main Menu:\n");
		printf("1. Display Items\n");
		printf("2. Purchase Items\n");
		printf("3. Save and Exit\n");	
		printf("Adiministrator-Only Menu:\n");
		printf("4. Add Item\n");		
		printf("5. Remove Item\n");	
		printf("6. Display Coins\n");	
		printf("7. Reset Stock\n");	
		printf("8. Reset Coins\n");	
		printf("9. Abort Program\n");
		printf("Select your Option (1-9) :\n");
		int number = 0;	
		scanf("%d", &number);
		if(number == 1){
		printList(linkedList);}
		else if(number == 2){
		purchaseItem(linkedList);}
		else if(number == 3){

		FILE* file1 = fopen(fileName, "w");
		loopnumber = saveAndClose(linkedList, file1);
		}
		else if(number == 4){
		addItem(linkedList);}
		else if(number == 5){
		removeItem(linkedList);}
		else if(number == 7){
		resetStock(linkedList);}
		else if(number == 8){
		printf("coins not implemented\n");}
		else if(number == 9){
		loopnumber = 0;}
		else{
		printf("Try again\n");}
		readRestOfLine();
	}

    printf("Goodbye. \n\n");
    return EXIT_SUCCESS;

}


