#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* define macro bool and compare function*/
#define TRUE 1
#define FALSE 0
#define MIN(a,b) (((a)>(b))?(b):(a))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX3(a,b,c) (MAX((MAX((a),(b))),(c)))

/* print given 2d array, assign 1-digit random integer if requested */
void arrayPrint(int** arr, int r, int c, int ra) {
    int i=0,j=0;
    for(i=0;i<r;i++) {
        for(j=0;j<c;j++) {
            if(ra) { arr[i][j] = rand() % 10; }
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }
}

/* dynamically allocate 2d array with given row, col input, default value 0 */
int** dynamic2dArray(int r, int c) {
    int i=0,j=0;
    int **arr = (int**)malloc(r*sizeof(int*));
    for(i=0;i<r;i++) {
        arr[i] = (int*)malloc(c*sizeof(int));
    }
    for(i=0;i<r;i++) {
        for(j=0;j<c;j++) {
            arr[i][j] = 0;
        }
    }
    return arr;
}

/* memory deallocation of given array */
void freeArray(int **arr, int r) {
    int i=0;
    for(i=0;i<r;i++) {
        free(arr[i]);
    }
    free(arr);
    return;
}

/* ordinary matrix multiplication function without recursion */
int** ordinaryMultiplication(int** A, int** B, int x, int y, int z) {
    int i=0,j=0,k=0;
    int** C;
    C = dynamic2dArray(x, z);
    for(i=0;i<x;i++) {
        for(j=0;j<z;j++) {
            C[i][j]=0;
            for(k=0;k<y;k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

/* matrix addition function for strassen */
int** matadd(int **A, int**B, int n) {
    int **C = dynamic2dArray(n, n);
    int i, j;
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

 /* matrix subtraction function for strassen */
int** matsub(int **A, int**B, int n) {
    int **C = dynamic2dArray(n, n);
    int i, j;
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

/* matrix multiplication function using strassen's algorithm */
int** strassen(int** A, int** B, int x, int y, int z) {
    int max=0, n=x, m=n/2;
    int i=0,j=0;
    int** C;
    /* if given matrix size unmatch, calculate smallest 2^n */
    if(x!=y||y!=z||z!=x) {
        max = MAX3(x,y,z);
        for(n=2;n<max;n*=2);
        m=n/2;
    }
    C = dynamic2dArray(n, n);

    /* if given matrices are 2*2, calculate by strassen's algorithm */
    if(n==2) {
        int a=A[0][0], b=A[0][1], c=A[1][0], d=A[1][1];
        int e=B[0][0], f=B[0][1], g=B[1][0], h=B[1][1];
        int P1 = a * (f - h);
        int P2 = (a + b) * h;
        int P3 = (c + d) * e;
        int P4 = d * (g - e);
        int P5 = (a + d) * (e + h);
        int P6 = (b - d) * (g + h);
        int P7 = (a - c) * (e + f);
        int r = P5 + P4 - P2 + P6;
        int s = P1 + P2;
        int t = P3 + P4;
        int u = P5 + P1 - P3 - P7;
        C[0][0]=r; C[0][1]=s; C[1][0]=t; C[1][1]=u;
        return C;
    } 

    /* if given matrices are not 2*2, recursively call strassen function*/
    else {
        /* memory allocation for submatrices of given matrices */
        int **a, **b, **c, **d, **e, **f, **g, **h;
        a = dynamic2dArray(m, m);
        b = dynamic2dArray(m, m);
        c = dynamic2dArray(m, m);
        d = dynamic2dArray(m, m);
        e = dynamic2dArray(m, m);
        f = dynamic2dArray(m, m);
        g = dynamic2dArray(m, m);
        h = dynamic2dArray(m, m);
        /* fill submatrices */
        for(i=0;i<MIN(x,m);i++) {
            for(j=0;j<MIN(y,m);j++) { a[i][j]=A[i][j]; }
            for(j=m;j<MIN(y,n);j++) { b[i][j-m]=A[i][j]; }
        }
        for(i=m;i<MIN(x,n);i++) {
            for(j=0;j<MIN(y,m);j++) { c[i-m][j]=A[i][j]; }
            for(j=m;j<MIN(y,n);j++) { d[i-m][j-m]=A[i][j]; }
        }
        for(i=0;i<MIN(y,m);i++) {
            for(j=0;j<MIN(z,m);j++) { e[i][j]=B[i][j]; }
            for(j=m;j<MIN(z,n);j++) { f[i][j-m]=B[i][j]; }
        }
        for(i=m;i<MIN(y,n);i++) {
            for(j=0;j<MIN(z,m);j++) { g[i-m][j]=B[i][j]; }
            for(j=m;j<MIN(z,n);j++) { h[i-m][j-m]=B[i][j]; }
        }
        
        /* memory allocation for strassen's algorithm */
        int **P1, **P2, **P3, **P4, **P5, **P6, **P7;
        P1 = dynamic2dArray(m, m);
        P2 = dynamic2dArray(m, m);
        P3 = dynamic2dArray(m, m);
        P4 = dynamic2dArray(m, m);
        P5 = dynamic2dArray(m, m);
        P6 = dynamic2dArray(m, m);
        P7 = dynamic2dArray(m, m);
        /* recursively calculate */
        int **fmh = dynamic2dArray(m, m);
        fmh = matsub(f, h, m);
        P1 = strassen(a, fmh, m, m, m); // P1=a*(f-h)
        freeArray(fmh, m);
        int **apb = dynamic2dArray(m, m);
        apb = matadd(a, b, m);
        P2 = strassen(apb, h, m, m, m); // P2=(a+b)*h
        freeArray(apb, m);
        int **cpd = dynamic2dArray(m, m);
        cpd = matadd(c, d, m);
        P3 = strassen(cpd, e, m, m, m); // P3=(c+d)*e
        freeArray(cpd, m);
        int **gme = dynamic2dArray(m, m);
        gme = matsub(g, e, m);
        P4 = strassen(d, gme, m, m, m); // P4=d*(g-e)
        freeArray(gme, m);
        int **apd = dynamic2dArray(m, m);
        apd = matadd(a, d, m);
        int **eph = dynamic2dArray(m, m);
        eph = matadd(e, h, m);
        P5 = strassen(apd, eph, m, m, m); // P5=(a+d)*(e+h)
        freeArray(apd, m);
        freeArray(eph, m);
        int **bmd = dynamic2dArray(m, m);
        bmd = matsub(b, d, m);
        int **gph = dynamic2dArray(m, m);
        gph = matadd(g, h, m);
        P6 = strassen(bmd, gph, m, m, m); // P6=(b-d)*(g+h)
        freeArray(bmd, m);
        freeArray(gph, m);

        int **amc = dynamic2dArray(m, m);
        amc = matsub(a, c, m);
        int **epf = dynamic2dArray(m, m);
        epf = matadd(e, f, m);
        P7 = strassen(amc, epf, m, m, m); //P7=(a-c)*(e+f)
        freeArray(amc, m);
        freeArray(epf, m);
        
        /* memory allocation for result submatrices */
        int **r, **s, **t, **u;
        r = dynamic2dArray(m, m);
        s = dynamic2dArray(m, m);
        t = dynamic2dArray(m, m);
        u = dynamic2dArray(m, m);
        /* calculate result submatrices */
        int** P54 = dynamic2dArray(m, m);
        P54 = matadd(P5, P4, m);
        int** P542 = dynamic2dArray(m, m);
        P542 = matsub(P54, P2, m);
        r = matadd(P542, P6, m); // r=P5+P4-P2
        freeArray(P54, m);
        freeArray(P542, m);
        s = matadd(P1, P2, m); // s=P1+P2
        t = matadd(P3, P4, m); // t=P3+P4
        int** P51 = dynamic2dArray(m, m);
        P51 = matadd(P5, P1, m);
        int** P513 = dynamic2dArray(m, m);
        P513 = matsub(P51, P3, m);
        u = matsub(P513, P7, m); // u=P5+P1-P3
        freeArray(P51, m);
        freeArray(P513, m);

        /* fill result matrix with calculated submatrices */
        for(i=0;i<m;i++) {
            for(j=0;j<m;j++) {
                C[i][j] = r[i][j];
                C[i][j+m] = s[i][j];
                C[i+m][j] = t[i][j];
                C[i+m][j+m] = u[i][j];
            }
        }

        freeArray(r, m);
        freeArray(s, m);
        freeArray(t, m);
        freeArray(u, m);

        /* if sizes of given matrices unmatch, resize and return */
        if(x!=y||y!=z||z!=x) {
            int **Strassen = dynamic2dArray(x, z);
            for(i=0;i<x;i++) {
                for(j=0;j<z;j++) {
                    Strassen[i][j] = C[i][j];
                }
            }
            freeArray(C, n);
            return Strassen;
        }
        return C;
    }
}

int main() {
    struct timeval  tv;
	double begin, end;
    /* assign A and B */
    int **A, **B;
    A = dynamic2dArray(30, 10);
    printf("A: \n");
    arrayPrint(A, 30, 10, TRUE);
    B = dynamic2dArray(10, 50);
    printf("B: \n");
    arrayPrint(B, 10, 50, TRUE);
    
    /* execute ordinary multiplication */
    printf("Ordinary multiplication\n");
    int **Ordinary = dynamic2dArray(30, 50);
    time_t ordinaryBegin = clock();
    Ordinary = ordinaryMultiplication(A, B, 30, 10, 50);
    time_t ordinaryEnd = clock();
    double ordinaryTime = (double)(ordinaryEnd - ordinaryBegin) / CLOCKS_PER_SEC;
    arrayPrint(Ordinary, 30, 50, FALSE);
    printf("Ordinary multiplication execution time: %lfs\n", ordinaryTime);

    /* execute strassen's multiplication */
    printf("Strassen multiplication\n");
    int **Strassen = dynamic2dArray(30, 50);
    time_t strassenBegin = clock();
    Strassen = strassen(A, B, 30, 10, 50);
    time_t strassenEnd = clock();
    double strassenTime = (double)(strassenEnd - strassenBegin) / CLOCKS_PER_SEC;
    arrayPrint(Strassen, 30, 50, FALSE);
    printf("Strassen multiplication execution time: %lfs\n", strassenTime);

    return 0;
}