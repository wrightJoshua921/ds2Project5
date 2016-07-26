/* 
 * File: stack.h
 * Author: Joshua Wright
 * Assignment Number: 5
 * Created on November 18, 2015, 9:45 AM
 */

#ifndef STACK_H
#define	STACK_H
#include <stdio.h>
#include <stdlib.h>
#include "matrixDetail.h"

typedef struct stack
{
    detailT *head;
}stackT;

stackT *init(void);

void push(stackT *stack, detailT *detail);

detailT *pop(stackT *stack);

void deleteStack(stackT *stack);

#endif	/* STACK_H */

