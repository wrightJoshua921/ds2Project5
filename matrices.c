/* 
 * File:   matrices.c
 * Author: Joshua Wright
 * Assignment Number: 5
 * Created on November 18, 2015, 9:45 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "stack.h"
#include "matrixDetail.h"
#include "matrices.h"

/* In This Program, There are 4 parts to it. I named the commanding functions to those 4 parts
 * partOne, partTwo, and partThreeAndFour. In part 1, I implement a dynamic programming
 * solution to compute the optimal parenthesization of a series of matrices.
 * on part 2. I build an infix to postfix conversion program that takes the parenthesized
 * expression from part 1 and converts it to postFix. In part 3 and 4, I implement 
 * a routine to do matrix multiplication on rectangular matrices, and then using the
 * postfix expression to do the multiplications.
 */

int main(int argc, char** argv)
{
    int i, numHolder = 0;
    MatrixInfoT p;
    char postFix[1024] = {'\0'};
    char placeHolder[MAXTERMS][MAXLENGTH];
    for(i = 0; i < MAXTERMS; i++)
        placeHolder[i][0] = '\0';
    
    
    readFile(&p);
    
    partOne(&p, placeHolder, &numHolder);
    partTwo(&p, postFix, placeHolder, &numHolder);
    partThreeAndFour(&p, postFix);
    
    freeMemory(&p);
   
    return (EXIT_SUCCESS);
}

//**reads in the text files matrixData and matrixDimensions and dynamically 
//**allocates memory for the arrays
void readFile(MatrixInfoT *p)
{
    int i, j, k;
    FILE *fp;
    
    fp = fopen("MatrixDimensions.txt", "r");
    if(fp == NULL)
    {
        fprintf(stderr, "Could not open FILE");
        exit(1);
    }
    
    //getting the number of matrices
    fscanf(fp, "%d", &p->length);
    
    p->dimensions = (int *) malloc((p->length + 1) * sizeof(int));
    p->m = (int **) malloc(p->length * sizeof(int *));
    p->s = (int **) malloc(p->length * sizeof(int *));
    for(i = 0; i < p->length; i++)
    {
        p->m[i] = (int *) malloc(p->length * sizeof(int));
        p->s[i] = (int *) malloc(p->length * sizeof(int));
    }
    
    for(i = 0; i <= p->length; i++)
    {
        fscanf(fp, "%d", &p->dimensions[i]);
    }
    fclose(fp);
    
    fp = fopen("matrixData.txt", "r");
    if(fp == NULL)
    {
        fprintf(stderr, "could not open file\n");
        exit(1);
    }
    
    p->matrix = (long long int ***)malloc(p->length *sizeof(long long int ***));
    for(i = 0; i < p->length; i++)
    {
        p->matrix[i] = (long long int **)malloc(p->dimensions[i] * sizeof(long long int *));
        for(j = 0; j < p->dimensions[i]; j++)
        {
            p->matrix[i][j] = (long long int *)malloc(p->dimensions[i+1] * sizeof(long long int));
        }
    }
    for(i = 0; i < p->length; i++)
    {
        for(j = 0; j < p->dimensions[i]; j++)
        {
            for(k = 0; k < p->dimensions[i+1]; k++)
            {
                fscanf(fp, "%lld", &p->matrix[i][j][k]);
            }
        }
    }
    fclose(fp);
}

//completes the matrix chain order algorithm
void matrixChainOrder(MatrixInfoT *p)
{
    int i, j, k, Q, L;
    for(i = 0; i < p->length; i++)
    {
        p->m[i][i] = 0;
    }
    for(L = 2; L <= p->length; L++)
    {
        for(i = 0; i < p->length - L + 1; i++)
        {
            j = i + L - 1;
            p->m[i][j] = INT_MAX;
            for(k = i; k < j; k++)
            {
                Q = p->m[i][k] + p->m[k+1][j] + p->dimensions[i] * p->dimensions[k+1] * p->dimensions[j+1];
                if(Q < p->m[i][j])
                {
                    p->m[i][j] = Q;
                    p->s[i][j] = k+1;
                }
            }
        }
    }
}

//prints out the optimal parens
void printOptimalParens(int **p, int i, int j)
{
    if(i == j)
    {
        printf("A%d", i);
    }
    else
    {
        printf("(");
        printOptimalParens(p, i, p[i][j]-1);
        printf("*");
        printOptimalParens(p, p[i][j], j);
        printf(")");
    }
}

//find the symbols and puts them in the postfix array
void findHolders(int **s, int i, int j, char placeHolder[][MAXLENGTH], int *numTerms)
{
    char temp[20] = {'\0'};
    
    if (i == j)
    {
        sprintf(temp, "A%d", i);
        strcpy(placeHolder[*numTerms], temp);
        (*numTerms)++;
    }
    else
    {
        strcpy(placeHolder[*numTerms], "(");
        (*numTerms)++;
        findHolders(s, i, s[i][j] - 1, placeHolder, numTerms);
        strcpy(placeHolder[*numTerms], "*");
        (*numTerms)++;
        findHolders(s, s[i][j], j, placeHolder, numTerms);
        strcpy(placeHolder[*numTerms], ")");
        (*numTerms)++;
    }
}

//duplicates the matrix
long long int **dupMatrix(long long int **matrix, int rows, int cols)
{
    int i, j;
    long long int **Matrix;
    
    Matrix = (long long int **)malloc(rows * sizeof(long long int *));
    for(i = 0; i < rows; i++)
    {
        Matrix[i] = (long long int *)malloc(cols * sizeof(long long int));
        for(j = 0; j < cols; j++)
        {
            Matrix[i][j] = matrix[i][j];
        }
    }
    
    return Matrix;
}
//function to start and call the functions needed for part 1 of the project
void partOne(MatrixInfoT *p, char placeHolder[][MAXLENGTH], int *numTerms)
{
    int i, j;
    
    printf("Matrix Dimensions: ");
    
    for(i = 0; i < p->length + 1; i++)
    {
        printf(" [%d] ",p->dimensions[i]);
    }
    printf("\n");
    matrixChainOrder(p);
    printf("\n");
    printf("M Matrix:\n");
    for(i = 0; i < p->length; i++)
    {
        for(j = 0; j < p->length; j++)
        {
            printf("%7d ", p->m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("S Matrix:\n");
    for(i = 0; i < p->length; i++)
    {
        for(j = 0; j < p->length; j++)
        {
            printf("%7d ", p->s[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Optimal - Parens:  ");
    printOptimalParens(p->s, 0, p->length - 1);
    printf("\n");
}

//function to start and call the functions needed for part 2 of the project
void partTwo(MatrixInfoT *p, char *postfix, char placeHolder[][MAXLENGTH], int *numTerms)
{
    findHolders(p->s, 0, p->length - 1, placeHolder, numTerms);
    postFix(postfix, placeHolder, *numTerms);
    printf("\nPostfix: %s\n\n", postfix);
}

//find the postFix solution of the problem
void postFix(char *dest, char placeHolder[][MAXLENGTH], int numHolder)
{
    int i, temp = 0;
    char stack[MAXTERMS];
    
    if(numHolder > MAXTERMS)
    {
        fprintf(stderr, "Too many terms\n");
        exit(1);
    }
    for(i = 0; i < MAXTERMS; i++)
    {
        stack[i] = '\0';
    }
    
    for(i = 0; i < numHolder; i++)
    {
        if(strstr(placeHolder[i], "("))
        {
            continue;
        }
        else if(strstr(placeHolder[i], "*"))
        {
            strcat(stack, "*");
        }
        else if(strstr(placeHolder[i], ")"))
        {
            char op[2] = {stack[temp], '\0'};
            strcat(dest, op);
            temp++;
        }
        else
        {
            strcat(dest, placeHolder[i]);
        }
        
    }
}

//function to call the functions to start part 3 and 4 of the project
void partThreeAndFour(MatrixInfoT *p, char *postfix)
{
    matrixMultiplication(p, postfix);
    printf("Final Matrix: \n");
    printMatrix(p->afterMath, p->dimensions[0], p->dimensions[p->length]);
}

//function to multiply 2 matrices
detailT *multiplyMatrix(detailT *matrixA, detailT *matrixB)
{
    int i, j, k;
    long long int answer;
    long long int **product;
    detailT *productDetail;
    
    product = (long long int **) malloc(matrixA->rows * sizeof(long long int *));
    for(i = 0; i < matrixA->rows; i++)
    {
        product[i] = (long long int *) malloc(matrixB->cols * sizeof(long long int));
    }
    
    if(matrixA->cols != matrixB->rows)
    {
        fprintf(stderr, "dimensions do not fit\n");
        exit(1);
    }
    
    for(i = 0; i < matrixA->rows; i++)
    {
        for(j = 0; j < matrixB->cols; j++)
        {
            answer = 0;
            for(k = 0; k < matrixA->cols; k++)
            {
                answer += matrixA->matrix[i][k] * matrixB->matrix[k][j];
            }
            product[i][j] = answer;
        }
    }
    
    productDetail = create(product, matrixA->rows, matrixB->cols);
    
    for(i = 0; i < matrixA->rows; i++)
    {
        free(product[i]);
    }
    free(product);
    
    return productDetail;
}

//function to decide when to multiply 2 matrices
void matrixMultiplication(MatrixInfoT *p, char *str)
{
   stackT *stack = init();
   char *current, tempString[2];
   int index;
   detailT *temp, *matrixA, *matrixB;
   
   current = str;
   while(*current != '\0')
   {
       if(*current == 'A')
       {
           current++;
           tempString[0] = *current; 
           tempString[1] = '\0';
           index = atoi(tempString);
           temp = create(p->matrix[index], p->dimensions[index], p->dimensions[index+1]);
           push(stack, temp);
       }
       else if(*current == '*')
       {
           matrixA = pop(stack);
           matrixB = pop(stack);
           
           temp = multiplyMatrix(matrixB, matrixA);
           push(stack, temp);
           
           deleteDetail(matrixA);
           deleteDetail(matrixB);
       }
       current++;
   }
   p->afterMath = dupMatrix(temp->matrix, temp->rows, temp->cols);
   deleteStack(stack);
}

//function to print final matrix
void printMatrix(long long int **matrix, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%-15lld ", (long long int) matrix[i][j]);
        }
        printf("\n");
    }
}

//free the memory for all the dynamically allocated memory
void freeMemory(MatrixInfoT *p)
{
    int i, j;
    for(i = 0; i < p->length; i++)
    {
        free(p->m[i]);
        free(p->s[i]);
        for(j = 0; j < p->dimensions[i]; j++)
        {
            free(p->matrix[i][j]);
        }
        free(p->matrix[i]);
    }
    free(p->m);
    free(p->s);
    free(p->matrix);
}
