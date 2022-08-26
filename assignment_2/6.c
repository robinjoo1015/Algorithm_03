#include <stdio.h>
#include <stdlib.h>
/* global variable for array size */
int arrayLength = 0;

/* function that returns all pairs of integer whose sum is given number */
int** pairSum(int *array, int num) {
    int i=0,j=0;
    int idx=0;
    /* memory allocation for result array */
    int **result = (int**)malloc((arrayLength*arrayLength/2)*sizeof(int*));
    /* look every element in array twice in order */
    for(i=0;i<arrayLength-1;i++) {
        for(j=i+1;j<arrayLength;j++) {
            if(array[i]+array[j]==num) {
                /* if sum of a pair equals to given number assign at result */
                result[idx]=(int*)malloc(2*sizeof(int));
                result[idx][0]=array[i];
                result[idx][1]=array[j];
                idx++;
            }
        }
    }
    /* if loop is done assign given number twice as a pair for end signal */
    result[idx]=(int*)malloc(2*sizeof(int));
    result[idx][0]=result[idx][1]=num;
    return result;
}

int main() {
    int array[] = {2, 4, 3, 5, 6, -2, 4, 7, 8, 9};
    int sum = 7;
    int i = 0, j = 0;
    arrayLength = sizeof(array)/sizeof(int);
    int **result = pairSum(array, sum);
    /* print result array */
    printf("[");
    for(i=0; i<arrayLength*arrayLength/2; i++) {
        if(result[i][0]==sum && result[i][1]==sum) {
            free(result[i]);
            break;
        } else {
            if(i!=0) {
                printf(", ");
            }
            printf("'%d", result[i][0]);
            if(result[i][1]<0) {
                printf("%d'", result[i][1]);
            } else {
                printf("+%d'", result[i][1]);
            }
            free(result[i]);
        }
    }
    free(result);
    printf("]");
    return 0;
}