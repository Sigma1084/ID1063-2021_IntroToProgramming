// H4P1

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int k = atoi(argv[1]);
    FILE *fp = fopen(argv[argc-1], "r");

    if (fp == NULL)
        exit(0);  // File Pointer is NULL

    char *line = NULL;
    size_t lineLen;

    for (int i=0; i<k; i++) {
        if (getline(&line, &lineLen, fp) != -1)
            printf("%s", line);
        else {
            // Exit since we encountered EOF
            free(line);
            fclose(fp);
            exit(0);
        }
    }

    char c;
    while ((c = getchar()) != -1) {
        if (c != '\n')
            continue;

        // We are now sure c is '\n'
        if (getline(&line, &lineLen, fp) != -1)
            printf("%s", line);
        else {
            // Exit since we encountered EOF
            free(line);
            fclose(fp);
            exit(0);
        }
    }

    free(line);
    fclose(fp);
    return 0;
}
