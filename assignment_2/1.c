#include <stdio.h>

int main() {
    int n=0, k=0, pow2k=1;
    printf("n = ");
    scanf("%d", &n);
    /* iterate while pow2k is larger than n, while incrementing k */
    for(k = 0; pow2k <= n; k++) {
        pow2k = pow2k << 1;
    }
    printf("k = %d", k-1);
    return 0;
}
