/* 
 * File: stack.c
 * Author: Joshua Wright
 * Assignment Number: 5
 * Created on November 18, 2015, 9:45 AM
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

//initialize the stack
stackT *init(void)
{
    stackT *stack = (stackT *)malloc(sizeof(stackT));
    stack->head = NULL;
    
    return stack;
}

//push data onto the stack
void push(stackT *stack, detailT *detail)
{
    if(stack == NULL)
    {
        fprintf(stderr, "Stack is NULL\n");
        exit(1);
    }
    if(stack->head == NULL)
    {
        stack->head = detail;
    }
    else
    {
        detail->next = stack->head;
        stack->head = detail;
    }
}

//pop data onto the stack
detailT *pop(stackT *stack)
{
    detailT *detail;
    
    if(stack == NULL)
    {
        fprintf(stderr, "stack is null\n");
        exit(1);
    }
    
    if(stack->head == NULL)
    {
        fprintf(stderr, "stack is empty\n");
        exit(1);
    }
    
    detail = stack->head;
    stack->head = stack->head->next;
    return detail;
}

//delete the stack!
void deleteStack(stackT *stack)
{
    if(stack == NULL)
    {
        fprintf(stderr, "stack is null\n");
        exit(1);
    }
    if(stack->head != NULL)
    {
        detailT *temp1 = stack->head;
        detailT *temp2 = stack->head->next;
        
        while(1)
        {
            deleteDetail(temp1);
            temp1 = temp2;
            if(temp2 == NULL)
            {
                break;
            }
            else
            {
                temp2 = temp2->next;
            }
        }
                
    }
    free(stack);
}
