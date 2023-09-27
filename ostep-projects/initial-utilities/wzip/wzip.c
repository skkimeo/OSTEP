#include <stdio.h>
#include <stdlib.h>

#define READ "r"

void printErrorAndExit(char *msg) {
    fprintf(stdout, "wzip: %s\n", msg);
    exit(1);
}

void writeToFile(int cnt, int chr, FILE *file) {
    fwrite(&cnt, sizeof(cnt), 1, file);
    fputc(chr, file);
}

void rle(FILE *file, int *prev, int *cnt) {
    int cur = 0;

    while ((cur = fgetc(file)) != EOF) {
        if (*prev == cur) {
            (*cnt)++;
        } else {
            if (*prev != EOF) {
                writeToFile(*cnt, *prev, stdout);
            }
            *prev = cur;
            *cnt = 1;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printErrorAndExit("file1 [file2 ...]");
    }

    FILE *file = NULL;
    int prev = EOF, cnt = 0;
    
    for(int i = 1; i < argc; i++) {
        file = fopen(argv[i], READ);
        
        if (file == NULL) {
            printErrorAndExit("cannot open file");
        }

        rle(file, &prev, &cnt);

        if (fclose(file) != 0) {
            printErrorAndExit("cannot close file");
        }
    }

    if (prev != EOF) {
        writeToFile(cnt, prev, stdout);
    }

    exit(0);
}

