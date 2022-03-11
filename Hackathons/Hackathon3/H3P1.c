// H3P1

#include <stdio.h>

/* The size of long unsigned is 4 bytes
 * The max value stored in long unsigned in around 10^9
 *     which is definitely not sufficient to store the very first test case
 *
 * Therefore, long long unsigned used which uses 8 bytes
 * The max value stored in long long unsigned is around 10^18
 *     which is sufficient for our purpose
 */


// Just defining long long unsigned as llu to make it easier to use
typedef long long unsigned llu;


/*
 * Suppose k = 13
 * k in Binary is 1101
 * Coming from the left, we need to multiply n, n^4, n^8 to produce n^11
 * Therefore, we calculate n, n^2 using n,n^4 using n^2 and so on
 * We multiply the required values to the answer to produce n^k
 */

llu power(llu n, llu k) {
    llu ans = 1;
    for (llu curr = n; k > 0; curr *= curr, k /= 2) {
        if (k % 2 == 1)
            ans *= curr;
    }
    return ans;
}

int main() {
    llu n, k;
    while(scanf("%llu %llu", &n, &k) != -1) {
        printf("%llu\n", power(n, k));
    }
}
