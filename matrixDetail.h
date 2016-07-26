/* 
 * File:   matrixDetail.h
 * Author: Joshua Wright
 * Assignment Number: 5
 * Created on November 18, 2015, 9:45 AM
 */

#ifndef MATRIXDETAIL_H
#define	MATRIXDETAIL_H

typedef struct detail
{
    long long **matrix;
    int rows;
    int cols;
    struct detail *next;
}detailT;

detailT *create(long long **matrix, int rows, int cols);

void deleteDetail(detailT *detail);

#endif	/* MATRIXDETAIL_H */

