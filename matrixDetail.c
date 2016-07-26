/* 
 * File:   matrixDetail.c
 * Author: Joshua Wright
 * Assignment Number: 5
 * Created on November 18, 2015, 9:45 AM
 */
#include "matrixDetail.h"
#include <stdlib.h>
#include <stdio.h>

//function to create details for the matrix
detailT *create(long long **matrix, int rows, int cols)
{
    int i, j;
    
    detailT *detail;
    
    detail = (detailT *)malloc(sizeof(detailT));
    detail->rows = rows;
    detail->cols = cols;
    detail->matrix = (long long **)malloc(rows * sizeof(long long *));
    detail->next = NULL;
    
    for(i = 0; i < rows; i++)
    {
        detail->matrix[i] = (long long *) malloc(cols *sizeof(long long));
    }
    
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            detail->matrix[i][j] = matrix[i][j];
        }
    }
    
    return detail;
}

//delete the details
void deleteDetail(detailT *detail)
{
    int i;
    for(i = 0; i < detail->rows; i++)
    {
        free(detail->matrix[i]);
    }
    free(detail->matrix);
    free(detail);
}
