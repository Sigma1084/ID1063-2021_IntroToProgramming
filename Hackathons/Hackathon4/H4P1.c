// H4P1

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int k = atoi(argv[1]);
    FILE *fp = fopen(argv[argc-1], "r");

    if (fp == NULL)
        exit(0);  // File Pointer is NULL

    char *line = (char *) malloc(sizeof(char) * 256);
    size_t lineLen;

    for (int i=0; i<k; i++) {
        if (getline(&line, &lineLen, fp) != -1)
            printf("%s", line);
        else
            exit(0);  // Exit since we encountered EOF
    }

    for (char c = getchar(); c != -1; c = getchar()) {
        if (c != '\n')
            continue;

        // We are now sure c is '\n'
        if (getline(&line, &lineLen, fp) != -1)
            printf("%s", line);
        else
            exit(0);  // Exit since we encountered EOF
    }
}
