#include <stdio.h>
#include <stdlib.h>

#define READ "r"

void printErrorAndExit(char *msg) {
    fprintf(stdout, "wunzip: %s\n", msg);
    exit(1);
}

void unzip(FILE *file) {
    int num = 0;
    char chr = 0;

    while (fread(&num, sizeof(int), 1, file) && fread(&chr, sizeof(char), 1, file)) {
        for(; num > 0; num--) {
            printf("%c", chr);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printErrorAndExit("file1 [file2 ...]");
    }

    FILE *file = NULL;
    
    for(int i = 1; i < argc; i++) {
        file = fopen(argv[i], READ);
        
        if (file == NULL) {
            printErrorAndExit("cannot open file");
        }

        unzip(file);

        if (fclose(file) != 0) {
            printErrorAndExit("cannot close file");
        }
    }

    exit(0);
}

