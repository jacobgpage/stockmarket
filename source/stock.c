/*

	Author: Jacob P.
	Name: stock.c
	Main manager for all things stocks!

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>

#include "stock.h"
#include "linkedlist.h"

/*

	Name: initStock
	Parameters: A stock_t stock
	Creates a stock by inserting values and setting next and prev pointers to NULL

*/

node_t* initNode (stock_t s) {

	node_t* nodePtr = malloc(sizeof(node_t));
	
	nodePtr->stock = s;
	
	nodePtr->nextPtr = NULL;
	nodePtr->prevPtr = NULL;
	
	return(nodePtr);
	
}
/*

	Name: insertStock
	Parameters: Pointer to linked list
	Inserts a node stock_t into a linked list!
	

*/

void insertStock (linked_list_t* i, node_t* n) {

	if (i != NULL) {

		if (i->headPtr == NULL) {

			i->headPtr = n;
			i->tailPtr = n;

		} else {

			n->nextPtr = i->headPtr;
			i->headPtr->prevPtr = n;
			i->headPtr = n;

		}

	}

}

/*

	Name: buyStock
	Parameters: n/a
	Gets input from user and stores it in a structure. Then the structure is written to a file!

*/

void buyStock () {
	
	char tickerSymbol[MAX_TICKER_LENGTH];
	char fileName[10];

	int numShares;
	int nameLen;
	int i = 0;
	
	time_t t;
	stock_t stock;
	
	printf("Input the stock's ticker symbol: ");
	scanf("%s", &tickerSymbol);
	printf("\n");
	
	while (tickerSymbol[i]) {
		
		tickerSymbol[i] = toupper(tickerSymbol[i]);
		i++;
		
	}
	
	strcpy(stock.ticker, tickerSymbol);
	
	strcat(fileName, tickerSymbol);
	strcat(fileName, ".bin");
	
	stock.numShares = 0;
	
	while (!(stock.numShares > 0)) {
		
		printf("Hows many shares will you be buying? "); //Gets num of shares from user
		scanf("%d", &stock.numShares);
		printf("\n");
		
		if (stock.numShares < 1) {
			
			printf ("Please input a number greater than 0!\n\n");
			
		} 		
		
	}
	
	printf("What is the price per share? "); //Gets price per share from user
	scanf("%lf", &stock.pricePerShare);
	printf("\n");
			
	struct tm* tPtr;        //Gets time and date
	t = time(NULL);
	tPtr = localtime( &t );
	stock.date.month = tPtr->tm_mon + 1;
	stock.date.day = tPtr->tm_mday;
	stock.date.year = tPtr->tm_year + 1900;
	
	FILE* out;
	out = fopen(fileName, "a");
	
	fwrite(&stock, sizeof(stock_t), 1, out);
			
	fclose(out);
	
	return;
	
}


/*

	Name: readStock
	Parameters: n/a
	List all stocks purchased and reads a chosen stocks data into a list. Then it prints out the list!

*/

void readStock () {
	
	char tickerSymbol[MAX_TICKER_LENGTH];
	char fileName[10];

	int i = 0;
	
	linked_list_t list;
	node_t* nodePtr;
	node_t node;
	stock_t stock;
	
	
	DIR* dirPtr;
	struct dirent* dirEntry;
	dirPtr = opendir(".");
	
	fileName[0] = '\0';
	
	printf("Stocks Owned\n");
	printf("------------\n\n");
	
	while((dirEntry = readdir(dirPtr)) != NULL) { //Finds all Binary files in directory and list then without hte ".bin"
		
		size_t lenstr = strlen(dirEntry->d_name);
		size_t lensuffix = 4;
		
		if (strncmp(dirEntry->d_name + lenstr - lensuffix, ".bin", lensuffix) == 0) {
			
			for (i = 0; i < MAX_TICKER_LENGTH; i++) {
				
				tickerSymbol[i] = 0;
				
			}
			
			strncpy(tickerSymbol, dirEntry->d_name, lenstr - 4);
			printf(tickerSymbol);
			printf("\n");
			
		}
		
	}
	
	i = 0;
	
	printf("\n");
	printf("Input the stock's ticker symbol: ");
	scanf("%s", &tickerSymbol);
	printf("\n");
	
	while (tickerSymbol[i]) {  //Puts ticker symbol to all uppercase
		
		tickerSymbol[i] = toupper(tickerSymbol[i]);
		i++;
		
	}
			
	strcat(fileName, tickerSymbol);
	strcat(fileName, ".bin");
	
	FILE* in;
	
	if (in = fopen(fileName, "rb")) {
		
		createList (&list); //Creates list
		
		while (fread((char*)(&stock), 1, sizeof(stock_t), in)) {
			
			nodePtr = initNode(stock);	
			insertStock(&list, nodePtr);
			
		}
		
		
		fclose(in);	
		printList(&list);
		deleteList(&list);
		
	} else {
		
		printf("You don't own any stocks with that ticker symbol!");
		printf("\n\n");
		
	}
	
	return;
	
}

/*

	Name: sellStock
	Parameters: n/a
	Sells stock

*/

void sellStock () {
	
	char tickerSymbol[MAX_TICKER_LENGTH];
	char fileName[10];
	
	int stocksBefore = 0;
	int totalStocks;
	int i = 0;

	double dollarValue, valueAfter, priceSold = 0;
	
	stock_t stock;
	node_t* nodePtr;
	linked_list_t list;
	
	fileName[0] = '\0';
	
	printf("Input the stock's ticker symbol: ");
	scanf("%s", &tickerSymbol);
	printf("\n");
	
	while (tickerSymbol[i]) {
		
		tickerSymbol[i] = toupper(tickerSymbol[i]);
		i++;
		
	}
			
	strcat(fileName, tickerSymbol);
	strcat(fileName, ".bin");
	
	FILE* in;
	in = fopen(fileName, "rb");
	
	if (in = fopen(fileName, "rb")) { //Checks if user owns the inputed stock
	
		createList (&list); //Creates list
		
		while (fread(&stock, 1, sizeof(stock_t), in)) {

			nodePtr = initNode(stock);
			insertStock(&list, nodePtr);
		
		}
		
		fclose(in);
		
		totalStocks = countStocks(&list);
		
		while (!(stocksBefore > 0)) {
			
			printf("How many stocks would you like to sell: ");
			scanf("%d", &stocksBefore);
			printf("\n");
			
			if (stocksBefore < 1) {
				
				printf ("Please input a number greater than 0!\n\n");
				
			}
		
		}
		
		if (stocksBefore > totalStocks) { //If the user tries to sell more stocks than owned!

			printf("You don't have that many stocks to sell!");
			printf("\n\n");
			
		} else {
			
			dollarValue = removeStocks(&list, stocksBefore, fileName);
			
			if (totalStocks == stocksBefore) {
				
				remove (fileName);
				
			}
			
			printf("What price are you selling the stocks for: ");
			scanf("%lf", &priceSold);
			printf("\n\n");
			
			valueAfter = (priceSold * stocksBefore) - dollarValue;
			
			printf("Total selling price: "); //Prints out earnings report
			printf("%5.2lf", (priceSold * stocksBefore));
			printf("\nBuying price: ");
			printf("%5.2lf", dollarValue);
			printf("\nProfit: ");
			printf("%5.2lf", valueAfter);
			printf("\n\n");
			
			deleteList(&list);
			
		}
		
	} else {
		
		printf("You don't own any stocks with ticker symbol: ");
		printf("%s", tickerSymbol);
		printf("\n\n");
	
	 }
	
	return;
	
}
