/*

	Name: linkedlist.c
	Author: Jacob P.
	C File for all linked list related functions

*/

#include "linkedlist.h"
#include <stdlib.h>

/*

	Name: createList
	Parameters: List pointer
	Creates a list and set head and tail pointers to NULL

*/

void createList (linked_list_t* list) {

	if (list != NULL) {

		list->headPtr = NULL;
		list->tailPtr = NULL;	

	}

	return;

}

/*

	Name: printList
	Parameters: constant linked list
	Prints out the data formatted in the list

*/

void printList (const linked_list_t* list) {
	
	node_t* curPtr = list->tailPtr;
	
	printf("Ticker  Purchase Date Shares Price Per Share\n");
	printf("--------------------------------------------\n\n");
	
	while (curPtr != NULL) {
		
		printf("%-6s", curPtr->stock.ticker);
		printf(" ");
		printf("%2d", curPtr->stock.date.month);
		printf("/");
		printf("%2d", curPtr->stock.date.day);
		printf("/");
		printf("%4d", curPtr->stock.date.year);
		printf("    ");
		printf("%3d", curPtr->stock.numShares);
		printf("     ");
		printf("$");
		printf("%9.2lf", curPtr->stock.pricePerShare);
		printf("\n");
		
		curPtr = curPtr->prevPtr;
		
	}
	
	printf("\n\n");
	
}

/*

	Name: countStocks
	Parameters: constant linked list
	Counts the total number of shares one stock has

*/

int countStocks (const linked_list_t* l) {
	
	int totalStocks = 0;
	node_t* curPtr = l->tailPtr;
	
	while (curPtr != NULL) {
		
		totalStocks = totalStocks + curPtr->stock.numShares;
		
		curPtr = curPtr->prevPtr;
		
	}
	
	return (totalStocks);

}
 
double removeStocks (linked_list_t* l, int stocksBefore, char fileName[10]) {
	
	node_t* curPtr = l->tailPtr;
	double dollarValue = 0;
	
	while (stocksBefore != 0) {
		
		if (curPtr->stock.numShares > 0) {
			
			dollarValue = dollarValue + curPtr->stock.pricePerShare;
				
		} else {
			
			curPtr = curPtr->prevPtr;
			l->tailPtr = l->tailPtr->prevPtr;
			
			dollarValue = dollarValue + curPtr->stock.pricePerShare;
			
		}
		
		curPtr->stock.numShares = curPtr->stock.numShares - 1;
		stocksBefore--;
		
	}
	
	FILE* out;
	out = fopen(fileName, "wb");
	
	curPtr = l->tailPtr;
	
	while (curPtr != NULL) {
		
		fwrite(&curPtr->stock, sizeof(stock_t), 1, out);
		curPtr = curPtr->prevPtr;
		
	}
	
	fclose(out);
	
	return (dollarValue);
	
}

void deleteList(linked_list_t* l) {

	node_t* curPtr = l->tailPtr;
	
	while (curPtr != NULL) {
		
		node_t* tempPtr;
		
		tempPtr = curPtr;
		curPtr = curPtr->prevPtr;
		
		free (tempPtr);
		
	}
	
}
