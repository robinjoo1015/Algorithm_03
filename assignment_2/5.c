#include <stdio.h>
#include <stdlib.h>

/* dynamic memory allocation of 5*5 array */
int** dynamic55Array() {
    int i=0;
    int **arr = (int**)malloc(5*sizeof(int*));
    for(i=0;i<5;i++) {
        arr[i] = (int*)malloc(5*sizeof(int));
    }
    return arr;
}

/* memory deallocation of given 5*5 array */
void free55Array(int **arr) {
    int i=0;
    for(i=0;i<5;i++) {
        free(arr[i]);
    }
    free(arr);
    return;
}

/* rotate given 5*5 array */
int** rotate55Matrix(int **matrix) {
    int i=0,j=0;
    int **rotatedMatrix = dynamic55Array();
    for(i=0;i<5;i++) {
        for(j=0;j<5;j++) {
            rotatedMatrix[i][j]=matrix[4-j][i];
        }
    }
    return rotatedMatrix;
}

int main() {
    int i=0, j=0;
    int **matrix = dynamic55Array();
    int **rotatedMatrix;
    printf("Original Matrix :\n");
    for(i=0;i<5;i++) {
        for(j=0;j<5;j++) {
            matrix[i][j]=rand()%1000;
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    rotatedMatrix = rotate55Matrix(matrix);
    printf("\nRotated Matrix :\n");
    for(i=0;i<5;i++) {
        for(j=0;j<5;j++) {
            printf("%3d ", rotatedMatrix[i][j]);
        }
        printf("\n");
    }
    free55Array(matrix);
    free55Array(rotatedMatrix);
    return 0;
}
