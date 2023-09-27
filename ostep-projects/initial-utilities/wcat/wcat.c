#include <stdio.h>
#include <stdlib.h>

void wcat(char *name) {
    FILE *file = fopen(name, "r");

    if (file == NULL) {
        printf("wcat: cannot open file\n");
        exit(1);
    }

    char line[2] = "";

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }


    if (fclose(file) != 0) {
        printf("wcat: cannot close file\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(0);
    }

    for(int i = 1; i < argc; i++) {
        wcat(argv[i]);
    }

    exit(0);
}
