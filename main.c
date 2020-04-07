/*

	Author: Jacob P.
	Name: Stock Market
	A simple stock market application that allows the user to report, buy, and sell stock

*/

#include <stdio.h>
#include <string.h>

int main() {
	
	int userContinue = -1;
	
	while (userContinue < 0 || userContinue > 4) { //Gets user input and loops till the input is either 0, 1, 2, or 3
	
		printf("Reporting, buying or selling? \n 0=quit, 1=report, 2=buy, 3=sell: ");
		scanf("%d",&userContinue);
		printf("\n");
		
		if (userContinue < 0 || userContinue > 4) {
			
			printf("Please input a valid number! \n\n");
			
		}
		
	}
	
	while (userContinue != 0) { //Loops until user wants to quit the program
		
		if (userContinue == 1) { //User wants a stock report!
			
			readStock();
			
		} else if (userContinue == 2) { //User wants to buy stock!
			
			buyStock();
			
		} else { //User wants to sell stock!
			
			sellStock();
			
		}
		
		userContinue = -1;
		
		while (userContinue < 0 || userContinue > 4) { //Gets user input and loops till the input is either 0, 1, 2, or 3
		
		printf("Reporting, buying or selling? \n 0=quit, 1=report, 2=buy, 3=sell: ");
		scanf("%d",&userContinue);
		printf("\n");
		
		if (userContinue < 0 || userContinue > 4) {
			
			printf("Please input a valid number! \n\n");
			
		}
		
	}
		
	}
	
	printf("\n\nThank you for using YouTrade.com!\n\n");
	
	return (0);
	
}
