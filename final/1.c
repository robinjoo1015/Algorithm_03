#include <stdio.h>
#include <limits.h>
#define LENGTH 11
/* global array for memoization of price and cut length */
int price_mem[LENGTH];
int cut_mem[LENGTH];

/* initialize memoization array */
void init_mem() {
    int i;
    for(i=0;i<LENGTH;i++) {
        price_mem[i] = INT_MIN;
        cut_mem[i] = 0;
    }
}

/* top-down recursive function for rod cutting */
int cut_rod(int *p, int n) {
    int q, temp, i;
    if(n==0) {
        return 0;
    }
    if(price_mem[n]>0) {
        /* if already calculated and memorized */
        return price_mem[n];
    }
    q = INT_MIN;
    for(i=1;i<=n;i++) {
        temp = cut_rod(p, n-i);
        if(q <= p[i] + temp) {
            q = p[i] + temp;
            /* save cut info in memoization array */
            cut_mem[n] = i;
        }
    }
    /* save price info in memoization array */
    price_mem[n] = q;
    return q;
}

/* print optimal cut recursively using memoization array */
void print_mem(int n) {
    printf("%d", cut_mem[n]);
    if(cut_mem[n]==n) {
        return;
    }
    printf("/");
    print_mem(n-cut_mem[n]);
    return;
}

int main() {
    int i;
    /* price array */
    int p[LENGTH] = {0, 1, 4, 5, 7, 9, 11, 13, 13, 15, 16};
    /* initialize memoization array */
    init_mem();
    /* calculate price and cuts for rod of length 1 to 10 */
    for(i=1;i<=10;i++) {
        printf("Rod length %d: Maximum price = %d, ", i, cut_rod(p, i));
        printf("Optimal cut = ");
        print_mem(i);
        printf("\n");
    }
    return 0;
}