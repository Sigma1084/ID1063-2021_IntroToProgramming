// H3P3

#include <stdio.h>
#include <stdlib.h>

// Just prints the array in the required format
void printArr(int *arr, int k) {
    printf("%d", arr[0]);
    for (int i=1; i<k; i++)
        printf("+%d", arr[i]);
    printf("\n");
}

// The recursive function to print all the combinations
// It prints the array only in it's exit condition
// Every iteration, the value of k is increased by 1 
//     (One extra value to keep track of)
// It prints when the only element that can be printed is the remaining number
// prev is an array that contains all the numbers till then (k of them)
void repeat(int *prev, int k, int rem) {
    int i;
    if (k==0)
        i = 1;  // The initial Case
    else
        i = prev[k-1];

    for (; i <= rem-i; i++) {
        prev[k] = i;
        repeat(prev, k+1, rem-i);
    }

    // Here, is the terminal case
    prev[k] = rem;
    printArr(prev, k+1);
}

// The function that directs to the required function
void solve (int n) {
    // Using an array to store all the numbers... The max will be n
    int *prev = (int *) malloc(sizeof (int) * n);
    int k = 0;
    repeat(prev, k, n);
    free(prev);
}

// The main method
int main() {
    int n = 100;

    while(scanf("%d", &n) != -1)
        solve(n);

    return 0;
}
