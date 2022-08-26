#include <stdio.h>

/* define maximum number of input number */
#define MAX_FIB 46

/* define global array for memoization */
int fib_mem[MAX_FIB+1] = {0, };

int fib(int n) {
    if(fib_mem[n]==0) {
        /* if no data in memoization array, recursively calculate */
        fib_mem[n] = fib(n-1) + fib(n-2);
    }
    return fib_mem[n];
}

int main() {
    int n;
    /* initialize memoization array */
    fib_mem[1] = 1;
    fib_mem[2] = 1;
    /* input loop */
    while(1) {
        printf("n = ");
        scanf("%d", &n);
        if(n<=0) { 
            /* terminate */
            break;
        }
        else if(n>MAX_FIB) { 
            /* larger than max input */
            printf("out of range\n");
        }
        else { 
            /* print fibonacci number */
            printf("fib(%d) = %d\n", n, fib(n));
        }
    }
    return 0;
}
