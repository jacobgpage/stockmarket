/*

	File: stock.h
	Author: Jacob P.
	This is the header file for stock.c

*/

#ifndef STOCK_H
#define STOCK_H

#include <stdio.h>
#include "date.h"

#define MAX_TICKER_LENGTH 6

typedef struct stock_t {
	
	char ticker[MAX_TICKER_LENGTH];
	date_t date;
	int numShares;
	double pricePerShare;
	
} stock_t;

void buyStock (); //Creates or appends to file for specified stock
void sellStock (); //Sells stock from file and prints report
void readStock (); //Reports all stocks
void insertStock(); //Inserts a stock into a list

#endif
