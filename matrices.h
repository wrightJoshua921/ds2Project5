/* 
 * File: matrices.h
 * Author: Joshua Wright
 * Assignment Number: 5
 * Created on November 18, 2015, 9:45 AM
 */

#ifndef MATRICES_H
#define	MATRICES_H
#define MAXTERMS 100
#define MAXLENGTH 100

typedef struct matrixInfo
{
    int length;
    int *dimensions;
    int **s;
    int **m;
    long long int **afterMath;
    long long int ***matrix;    
}MatrixInfoT;

void freeMemory(MatrixInfoT *p);
void printMatrix(long long int **matrix, int rows, int cols);
detailT *multiplyMatrix(detailT *matrixOne, detailT *matrixTwo);
void matrixMultiplication(MatrixInfoT *p, char *str);
void partThreeAndFour(MatrixInfoT *p, char *postfix);
void partTwo(MatrixInfoT *p, char *postfix, char placeHolder[][MAXLENGTH], int *numTerms);
void partOne(MatrixInfoT *p, char placeHolder[][MAXLENGTH], int *numTerms);
long long int **dupMatrix(long long int **matrix, int rows, int cols);
void readFile(MatrixInfoT *p);
void matrixChainOrder(MatrixInfoT *p);
void printOptimalParens(int **p, int i, int j);
void findHolders(int **s, int i, int j, char placeHolder[][MAXLENGTH], int *numTerms);
void postFix(char *dest, char placeHolder[][MAXLENGTH], int numHolder);

#endif	/* MATRICES_H */

