#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define NUM_MAT 3

/* matrix memory allocation, assign random value */
int** allocMatrix(int row, int col) {
    int **matrix;
    int i, j;
    matrix = (int**)malloc(row*sizeof(int*));
    for(i=0;i<row;i++) {
        matrix[i] = (int*)malloc(col*sizeof(int));
        for(j=0;j<col;j++) {
            matrix[i][j] = rand()%10;
        }
    }
    return matrix;
}

/* print matrix */
void printMatrix(int **matrix, int row, int col) {
    int i, j;
    printf("%dx%d\n", row, col);
    for(i=0;i<row;i++) {
        for(j=0;j<col;j++) {
            printf("%5d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

/* multiply two matrices */
int** multiplyMatrix(int **A, int **B, int p, int q, int r) {
    int **matrix;
    int i, j, k;
    matrix = allocMatrix(p, r);
    for(i=0;i<p;i++) {
        for(j=0;j<r;j++) {
            matrix[i][j]=0;
            for(k=0;k<q;k++) {
                matrix[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return matrix;
}

/* print optimal chain order, multiply matrices with optimal order */
int** computeOrder(int **s, int i, int j, int *p, int ***matrices) {
	int **A, **B, **C;
	if(i==j) {
		printf("(%dx%d)", p[i-1], p[i]);
		return matrices[i-1];
	}
	else {
		printf("(");
		A = computeOrder(s, i, s[i][j], p, matrices);
		printf("*");
		B = computeOrder(s, s[i][j]+1, j, p, matrices);
		printf(")");
		C = multiplyMatrix(A, B, p[i-1], p[s[i][j]], p[j]);
		return C;
	}
}

/* multiply matrices with minimum computation cost */
int** matrixChainMultiply(int *p, int ***matrices, int n) {
    int **m, **s, **result;
    int i=0, j=0, k=0, l=0, q=0;
    m = allocMatrix(n+1, n+1);
    s = allocMatrix(n+1, n+1);
    /* calculate minimum computation cost bottom up */
    for(i=1;i<=n;i++) { m[i][i] = 0; }
    for(l=2;l<=n;l++) {
        for(i=1;i<=n-l+1;i++) {
            j = i + l - 1;
            m[i][j] = INT_MAX;
            for(k=i;k<=j-1;k++) {
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if(q<m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
	/* multiply matrices with calculated minimum cost */
	printf("Optimal Chain Order : ");
    result = computeOrder(s, 1, n, p, matrices);
    printf("\nMinimum Number of Computation : %d\n", m[1][NUM_MAT]);
	return result;
}

int main() {
    int matRowCol[NUM_MAT + 1];
    int **A, **B, **C, **result;
    int ***matrices;
	/* three matrices */
    A = allocMatrix(5, 3);
    B = allocMatrix(3, 7);
    C = allocMatrix(7, 10);
    printMatrix(A, 5, 3);
    printMatrix(B, 3, 7);
    printMatrix(C, 7, 10);
	/* array that stores row and column information of matrices */
    matRowCol[0] = 5;
    matRowCol[1] = 3;
    matRowCol[2] = 7;
    matRowCol[3] = 10;
	/* array that stores matrices */
	matrices = (int***)malloc(NUM_MAT*sizeof(int**));
    matrices[0] = A;
    matrices[1] = B;
    matrices[2] = C;
	/* multiply matrices */
    result = matrixChainMultiply(matRowCol, matrices, NUM_MAT);
    printf("Output Matrix : ");
    printMatrix(result, matRowCol[0], matRowCol[NUM_MAT]);
    return 0;
}
