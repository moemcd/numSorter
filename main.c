//
//  main.c
//  hw07
//
//  Created by Morgan  McDowell on 4/11/17.
//  Copyright © 2017 Morgan  McDowell. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAXSIZE 35

int getArray(int []);
int checkPrime(int);
int seperate(int [], int [], int [], int);
void bubbleSort(int [], int);
void convertPrime(int [], int , int []);
void mergeArraysSorted(int, int, int [], int [], int []);
void mergeArrays();
int determineSort(int [], int);
int determineDuplicate(int [], int);
void print(int [], int, int [], int, int [], int);

int main()
{
    int input[MAXSIZE];
    int inputSize;
    int prime[(MAXSIZE / 2) + 1];
    int primeSize;
    int notPrime[(MAXSIZE / 2) + 1];
    int notPrimeSize;
    int newPrime[(MAXSIZE / 2) + 1];
    int allPrime[MAXSIZE];
    
    inputSize = getArray(input);
    primeSize = seperate(input, prime, notPrime, inputSize);
    notPrimeSize = inputSize - primeSize;
    bubbleSort(prime, primeSize);
    bubbleSort(notPrime, notPrimeSize);
    convertPrime(notPrime, notPrimeSize, newPrime);
    
    if ((primeSize <= 1) || (notPrimeSize <= 1))
        mergeArraysSorted(primeSize, notPrimeSize, prime, newPrime, allPrime);
    else
        mergeArrays();
    
    print(prime, primeSize, notPrime, notPrimeSize, allPrime, inputSize);
    return 0;
}

int getArray(int input[])
{
    int i = 0;
    int size = 0;
    
    printf("Enter up to 35 integers or -1 to exit: ");
    while (i < MAXSIZE && input[i] > 0)
    {
        scanf("%d", &input[i]);
        size ++;
        i ++;
    }
    return size;
}

int checkPrime(int num)
{
    int i;
    
    for (i = 2; i < num; i++)
    {
        if (num % i == 0 && i != num)
            return 0;
    }
    return 1;
}

int seperate(int input[], int prime[], int notPrime[], int size)
{
    int i;
    int j;
    int primeSize = 0;
    
    for (i = 0; i < size; i++)
        if (checkPrime(input[i]) == 1)
        {
            prime[i] = input[i];
            primeSize ++;
        }
    for (j = 0; j < size; j++)
        if (checkPrime(input[j] == 0))
            notPrime[j] = input[j];
    return primeSize;
}

void bubbleSort(int array[], int size)
{
    int i;
    int j;
    int swap;
    
    for (i = 0; i < size; i++)
    {
        for (j = size - 1; j > i; j--)
        {
            if (array[j] < array[j-1])
            {
                swap = array[j];
                array[j] = array[j+1];
                array[j+1] = swap;
            }
        }
    }
}

void convertPrime(int notPrime[], int size, int newPrime[])
{
    int i;
    int num;
    
    for (i = 0; i < size; i++)
    {
        num = 2 * notPrime[i];
        
        while (checkPrime(num) == 0)
        {
            checkPrime(num);
            num++;
        }
        
        newPrime[i] = num;
    }
}


void mergeArraysSorted(int size1, int size2, int prime[], int newPrime[], int allPrime[])
{
    int i = 0;
    int j = 0;
    int k = 0;
    
    while (i < size1 && j < size2)
    {
        if (prime[i] <= newPrime[j])
        {
            allPrime[k] = prime[i];
            i++;
            k++;
        }
        else
        {
            allPrime[k] = newPrime[j];
            k++;
            j++;
        }
    }
    
    while (i < size1)
    {
        allPrime[k] = prime[i];
        i++;
        k++;
    }
    
    while (j < size2)
    {
        allPrime[k] = newPrime[j];
        k++;
        j++;
    }
}

void mergeArrays()
{
    
}

int determineSort(int allPrime[], int size)
{
    int i;
    int sort = 0;
    
    for (i = 0; i < (size - 1); i++)
    {
        if (allPrime[i] <= allPrime[i - 1])
            sort = 1;
        else
            sort = 0;
    }
    return sort;
}

int determineDuplicate(int allPrime[], int size)
{
    int i;
    int j;
    int dupli = 0;
    
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (allPrime[i] == allPrime[j])
                dupli = 1;
            else
                dupli = 0;
        }
    }
    return dupli;
}

void print(int prime[], int primeSize, int notPrime[], int notPrimeSize, int allPrime[], int allPrimeSize)
{
    int i;
    int j;
    int k;
    
    printf("Sorted prime data: ");
    for (i = 0; i < primeSize; i++)
    {
        printf("%d ", prime[i]);
    }
    
    printf("\nSorted non-prime data: ");
    for (j = 0; j < notPrimeSize; j++)
    {
        printf("%d ", notPrime[j]);
    }
    
    if (determineSort(allPrime, allPrimeSize) == 0)
        printf("\n\nAll-prime array is no longer sorted.");
    else if ((determineSort(allPrime, allPrimeSize) == 1) && (determineDuplicate(allPrime, allPrimeSize) == 0))
        printf("\n\nAll-prime array remains sorted [no duplicates].");
    else
        printf("\n\nAll-prime array remains sorted [with duplicates].");
    
    printf("\nContents of all-prime array: ");
    for (k = 0; k < allPrimeSize; k++)
    {
        printf("%d ", allPrime[k]);
    }
}






