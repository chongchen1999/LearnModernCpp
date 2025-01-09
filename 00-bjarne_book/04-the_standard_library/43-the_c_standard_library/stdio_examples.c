// stdio_examples.c

#include <stdio.h>

int main() {
    // File handling example
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(file, "Writing to a file.\n");
    fclose(file);

    // Formatted output example
    int num = 42;
    const char *message = "Hello, World!";
    printf("Message: %s, Number: %d\n", message, num);

    // Character I/O example
    int ch;
    printf("Type something (Ctrl+D to stop):\n");
    while ((ch = getchar()) != EOF) {
        putchar(ch); // Echo input
    }

    // Safe input
    char buffer[100];
    printf("\nEnter a line of text: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        printf("You typed: %s", buffer);
    }

    return 0;
}
