// H3P2

#include <stdio.h>
#include <stdlib.h>

// Returns the length of the string
int length(const char *str) {
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

// Check which string is greater (Absolute Value)
// Returns 1 if the first string is greater (in magnitude)
// Returns 2 if the second string is greater (in magnitude)
// Returns 0 if the strings are equal (in magnitude)
int greater(const char *str1, const char *str2, int l1, int l2) {

    if(str1[0] == '-')
        return greater(str1+1, str2, l1-1, l2);

    if(str2[0] == '-')
        return greater(str1, str2+1, l1, l2-1);

    if (l1 > l2)
        return 1;  // Means length of str1 is greater and hence str1 is greater

    if (l2 > l1)
        return 2;  // Means length of str2 is greater and hence str2 is greater


    // Only runs when the length of both strings is equal
    for (int i = 0; str1[i] != '\0'; i++) {
        // Don't worry about them being characters since the ASCII values behave similarly anyway
        if (str1[i] > str2[i])
            return 1;
        if (str2[i] > str1[i])
            return 2;
    }
    return 0;
}

// The sum of 2 numbers
// The sum of str1 and str2 will be stored inside ans
void calcSum(const char *str1, const char *str2, char *ans, int l1, int l2, int l3) {
    int i = l1-1;
    int j = l2-1;
    int k = l3-1;

    int tempSum;
    int carry = 0;  // Carry is 0 initially

    while (i >= 0) {
        if (j >= 0)
            tempSum = (str1[i--] - '0') + (str2[j--] - '0') + carry;
        else  // No elements of j are left to add
            tempSum = (str1[i--] - '0') + carry;
        ans[k--] = tempSum % 10 + '0';
        carry = tempSum / 10;
    }
    if (carry > 0)
        ans[k] = carry + '0';
}

// The difference
// str1 - str2 will be stored inside ans
// str1 >= str2 is assumed due to the implementation in the other function
void calcDiff(const char *str1, const char *str2, char *ans, int l1, int l2, int l3) {
    int i = l1-1;
    int j = l2-1;
    int k = l3-1;

    int carry = 0; // Carry = 1 if the carry has taken place

    int upper, lower;

    while (i >= 0) {
        if (carry)
            upper = (str1[i--] - '0') - 1;  // Previous number has taken a carry from this number
        else
            upper = str1[i--] - '0';  // No carry

        if (j >= 0)
            lower = str2[j--] - '0';
        else
            lower = 0;  // The lower number has been completely subtracted

        if (upper - lower >= 0)
            carry = 0;  // We do not need a carry
        else {
            carry = 1;  // The carry is 1
            upper += 10;  // Add 10 to the upper number after taking a carry
        }

        ans[k--] = (upper - lower) + '0';
    }
}

// Clean the zeroes in the beginning of the answer string
void clean(char *ans, int l) {
    int i = 0;
    while (ans[i] == '0' && i < l)
        i++;
    if (i == l) {
        // Case when the number is 0
        ans[0] = '0';
        ans[1] = '\0';
        return;
    }

    for (int j = 0; j+i < l; j++)
        ans[j] = ans[i+j];
    ans[l-i] = '\0';
}

// The function that directs to the other helper functions
void solve(char *str1, char *str2, int l1, int l2) {
    // We can safely assume Magnitude(str1) > Magnitude(str2)

    int neg = 0;  // Means that the final answer is positive
    int l3 = (l1 > l2 ? l1 : l2) + 1;  // Length of the final answer

    char *ans = (char *)calloc(l3+1, sizeof(char));
    for (int i=0; i < l3; i++)
        ans[i] = '0';
    ans[l3] = '\0';

    // Both are +
    if (str1[0] != '-' && str2[0] != '-') {
        calcSum(str1, str2, ans, l1, l2, l3);
    }

    // Both are -
    else if (str1[0] == '-' && str2[0] == '-') {
        neg = 1;  // Indicating the final answer is negative
        // Ignoring the first character in both
        calcSum(str1 + 1, str2 + 1, ans, l1 - 1, l2 - 1, l3);
    }

    // Greater one is - but lesser one is +
    else if (str1[0] == '-') {
        neg = 1;  // Indicating the final answer is negative
        // Ignoring the first character in first
        calcDiff(str1 + 1, str2, ans, l1 - 1, l2, l3);
    }

    // Final case when the greater one is + and the lesser one is -
    else {
        // The final answer will be positive
        // Ignoring the first character in second
        calcDiff(str1, str2 + 1, ans, l1, l2 - 1, l3);
    }

    if (neg)
        ans[0] = '-';

    // Clean the zeroes
    // If the number is negative, neg = 1 and the first character is ignored
    clean (ans + neg, l3 - neg);  

    // Cleaning -0 case
    if (ans[0] == '-' && ans[1] == '0') {
        ans[0] = '0';
        ans[1] = '\0';
    }

    printf("%s\n",ans);
    free(ans);  // Freeing the variable
}

int main() {
    int n = 100;
    char *a, *b;

    a = (char *) malloc(sizeof(char) * n);
    b = (char *) malloc(sizeof(char) * n);

    while(scanf("%s %s",a,b) != -1) {
        int l1 = length(a);
        int l2 = length(b);

        // Manipulating such that Magnitude(str1) > Magnitude(str2)
        if (greater(a, b, l1, l2) == 2)
            solve(b, a, l2, l1);  
        else
            solve(a, b, l1, l2);
    }

    free(a);
    free(b);
    return 0;
}
