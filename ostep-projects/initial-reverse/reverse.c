#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct Node {
    char *data;
    struct Node* next;
} Node;

Node* createNode(char *data) {
    Node* node = (struct Node*)malloc(sizeof(struct Node));

    if (!node) {
        fprintf(stderr, "reverse: malloc failed\n");
        exit(1);
    }

    node->data = strdup(data);
    node->next = NULL;

    return node;
}

void appendLeft(Node** head, char *data) {
    Node* newNode = createNode(data);

    newNode->next = *head;
    *head = newNode;
}

Node* readInReverse(FILE *input) {
    Node *head = NULL;
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, input) != -1) {
        appendLeft(&head, line);
    }

    return head;
}

void writeToOuput(FILE *output, Node *head) {
    Node *temp = NULL;

    while (head != NULL) {
        fprintf(output, "%s", head->data);
        temp = head;
        head = head->next;
        free(temp);
    }

    temp = NULL;
}

void reverse(FILE *input, FILE *output) {
    Node *head = readInReverse(input);
    writeToOuput(output, head);
}

int areSameFile(FILE* file1, FILE* file2) {
    int fd1 = fileno(file1);
    int fd2 = fileno(file2);

    struct stat stat1, stat2;

    if (fstat(fd1, &stat1) == -1 || fstat(fd2, &stat2) == -1) {
        fprintf(stderr, "reverse: failed to retrieve file stats\n");
        exit(1);
    }

    return stat1.st_ino == stat2.st_ino;
}

int main(int argc, char *argv[]) {
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    
    FILE *input = (argc == 1) ? stdin : fopen(argv[1], "r");
    FILE *output = (argc == 3) ? fopen(argv[2], "w") : stdout;

    if (input == NULL || output == NULL) {
        char *file = (input == NULL) ? argv[1] : argv[2];
        fprintf(stderr, "reverse: cannot open file '%s'\n", file);
        exit(1);
    }

    if (argc == 3 && areSameFile(input, output)) {
        fprintf(stderr, "reverse: input and output file must differ\n");
        exit(1);
    }

    reverse(input, output);
    
    if (input != stdin && fclose(input)) {
        fprintf(stderr, "reverse: cannot close file '%s'\n", argv[1]);
        exit(1);
    }
    
    if (output != stdout && fclose(output)) {
        fprintf(stderr, "reverse: cannot close file '%s'\n", argv[2]);
        exit(1);
    }

    return(0);
}
