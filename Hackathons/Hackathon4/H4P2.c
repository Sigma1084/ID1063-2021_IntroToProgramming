// H4P2

#include <stdio.h>
#include <stdlib.h>

// Returns the length of the string
int length(const char *str) {
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

// Copies a given string
char* copyStr(char *str) {
    int l = length(str);
    char *newStr = (char *)malloc(sizeof (char) * (l+1));
    for (int i=0; i<l; i++)
        newStr[i] = str[i];
    newStr[l] = '\0';
    return newStr;
}

// Converts the given string into lower case
void toLower(char *str) {
    for (int i=0; str[i]!='\0' && str[i]!='\n'; i++) {
        if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + ('a' - 'A');
    }
}

// The check function checks if the given pattern is present in the line
int check(const char *pattern, const char *line, int lP, int lL) {
    lL = length(line);
    
    for (int i=0; i + lP < lL; i++) {
        if (line[i] == pattern[0] || pattern[0] == '.') {
            int present = 1;
            for (int j=1; j < lP; j++) {
                if (pattern[j] == '.' || pattern[j] == line[i+j])
                    continue;

                // Here, the pattern does not start at line[i]
                present = 0;
                break;
            }
            if (present)
                return 1;
        }
    }

    // Went through the entire line and did not find the pattern
    return 0;
}


// Argc: Number of Command Line Arguments (First one is the name of the executable)
// The last arg is the file name and the one before that is the pattern
// -v is Invert Output
// -i is Ignore Case

int main(int argc, char *argv[]) {
    char *pattern = argv[argc-2];
    FILE *fp = fopen(argv[argc-1], "r");

    int isI = 0;
    int isV = 0;

    for (int i=1; i+2 < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'v': isV = 1; break;
                case 'i': isI = 1; break;
            }
        }
    }

    if (isI)
        toLower(pattern);

    // Assuming the line length is less than 256
    char *line = (char *) malloc(sizeof (char) * 256);

    int lNo = 1;
    size_t lenLine;
    int lenPat = length(pattern);
    
    while(getline(&line, &lenLine, fp) != -1) {

        char *lineCpy = line;
        if (isI) {
            lineCpy = copyStr(line);
            // The original line is present in line
            // lineCpy is the copy of the original line
            toLower(lineCpy);
        }

        if (check(pattern, lineCpy, lenPat, (int)lenLine)) {
            if (!isV)
                printf ("%d: %s", lNo, line);  // The Line already has a '\n' in the end
        }
        else {
            if (isV)
                printf ("%d: %s", lNo, line);  // The Line already has a '\n' in the end
        }
        
        lNo++;
    }

    free(line);
    fclose(fp);
}
