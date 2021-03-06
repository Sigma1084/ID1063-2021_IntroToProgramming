// H4P3

#include <stdio.h>
#include <stdlib.h>

/*
 * (Idea of a circular Queue)
 * The Structure Queue contains the following
 *     maxSize: (int) The maximum size of the array
 *     size: (int) The number of elements in the array
 *     start: (int) The starting index
 *     arr: (int *) The array in which the elements are stored in
 *
 * Accessing Elements
 *     Element to be removed: arr[start]
 *     i-th element to be removed: arr[(start+i) % maxSize]
 *
 * Adding an Element
 *     We basically place the element at the end of the array in the cyclic order
 *     If the array is full, we make a new Queue with double the size
 *         and move all the elements into the new array
 *
 * Removing an Element
 *     arr[start] is removed and start is incremented
 *     Prints empty if the array is empty
 *
 */


// Arbitrarily define the initial size of the queue
// We keep doubling the size of the queue as and when required
#define INITIAL_SIZE 10

// Struct Definition
struct Queue {
    int maxSize;
    int start;
    int size;
    int *arr;
};
typedef struct Queue Queue;


// Just a function to print the details of the queue convenient for debugging
void printQueue(Queue q) {
    printf("Start: %d, Size: %d\n", q.start, q.size);
    if (q.size == 0)
        printf("<Empty Array>");
    for (int i = q.start; i < q.start + q.size; i++) 
        printf("%d ", q.arr[i % q.maxSize]);
    printf("\n");
}

// Returns an empty fresh queue to work with
Queue createQueue(int size) {
    Queue q;
    q.maxSize = size;
    int *a = (int *)malloc(sizeof(int) * q.maxSize);
    q.arr = a;
    q.size = 0;
    q.start = 0;
    return q;
}

// Resizes the existing queue to double the size
Queue resized(Queue q) {
    // Doubling the total size of the array using realloc
    q.arr = (int *) realloc(q.arr, sizeof(int) * 2 * q.maxSize);

    // All the elements before the starting element are sent to the next half of the original array
    for (int i = 0; i < q.start; i++)
        q.arr[q.maxSize + i] = q.arr[i];

    q.maxSize *= 2;  // The max size of the new array is double
    // Size remains constant

    return q;
}

// Adds an element to the queue and returns the new queue
Queue addElement(Queue q, int ele) {
    // printf("\nEntering addElement: \n");
    // printQueue(q);
    // printf("Element: %d\n", ele);
    if (q.size >= q.maxSize) 
        q = resized(q);
    q.arr[(q.start + q.size) % q.maxSize] = ele;
    q.size++;
    return q;
}

// Removes an element and prints it or prints empty
Queue removeElement(Queue q) {
    // printf("\nEntering remElement: \n");
    // printQueue(q);
    if (q.size == 0) {
        printf("Empty\n");
        return q;
    }
    printf("%d\n", q.arr[q.start]);
    q.size--;
    q.start++;
    if (q.size == 0) 
        q.start = 0;
    return q;
}

// The main method
int main() {
    char c;
    Queue q = createQueue(INITIAL_SIZE);

    while (scanf("%c", &c) != -1) {
        if (c == 'D') 
            q = removeElement(q);
        else if (c == 'E') {
            int temp;
            scanf("%d", &temp);
            q = addElement(q, temp);
        }
    }

    free(q.arr);
    return 0;
}
