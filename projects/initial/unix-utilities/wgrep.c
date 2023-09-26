#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define READ "r"

void printErrorAndExit(char *msg) {
    printf("wgrep: %s\n", msg);
    exit(1);
}

void grep(FILE *file, const char *term) { 
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        if (strstr(line, term) != NULL) {
            printf("%s", line);
        }
    }

    free(line);
    line = NULL;
}

int main(int argc, char *argv[]) {

    if (argc <= 1) {
        printErrorAndExit("searchterm [file ...]");
    }

    const char *term = argv[1];

    if (argc == 2) {
        grep(stdin, term);
        exit(0);
    }

    FILE *file = NULL;
    
    for(int i = 2; i < argc; i++) {
        file = fopen(argv[i], READ);
        
        if (file == NULL) {
            printErrorAndExit("cannot open file");
        }

        grep(file, term);

        if (fclose(file) != 0) {
            printErrorAndExit("cannot close file");
        }
    }

    exit(0);
}
