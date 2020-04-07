/*

	Name: node.h
	Author: Jacob P.
	Header file for node sturcture

*/

#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include "stock.h"

typedef struct node_t {
	
	stock_t stock;
	
	struct node_t* nextPtr;
	struct node_t* prevPtr;
	
} node_t;

node_t* initNode();

#endif
