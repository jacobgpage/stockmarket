/*
 
	Name: linkedlist.h
	Author: Jacob P.
	Header file for linked list structure

*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

typedef struct {

	node_t* headPtr;
	node_t* tailPtr;

} linked_list_t;

void createList(linked_list_t* l); //Creates a new empty list
void printList(const linked_list_t* l); //Prints contents of a list
int countStocks(const linked_list_t* l); //Counts how many stocks are owned
double removeStocks (linked_list_t* l, int i, char fileName[10]); //Removes stocks from list
void deleteList(linked_list_t* l); //Frees the list

#endif
