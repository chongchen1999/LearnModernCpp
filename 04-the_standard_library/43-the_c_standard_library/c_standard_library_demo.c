// c_standard_library_demo.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// C-Style String Demo
void demo_cstrings() {
    char str1[50] = "Hello";
    char str2[50] = ", World!";
    char str3[50];

    printf("Length of str1: %lu\n", strlen(str1));
    strcpy(str3, str1);
    printf("Copied string: %s\n", str3);
    strcat(str1, str2);
    printf("Concatenated string: %s\n", str1);
    int cmp_result = strcmp(str1, "Hello, World!");
    printf("Comparison result: %d\n", cmp_result);
}

// Memory Manipulation Demo
void demo_memory() {
    char *buffer = (char *)malloc(20);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        return;
    }
    memset(buffer, 'A', 19);
    buffer[19] = '\0';
    printf("Buffer after memset: %s\n", buffer);
    char source[] = "Hello";
    memcpy(buffer, source, strlen(source) + 1);
    printf("Buffer after memcpy: %s\n", buffer);
    free(buffer);
}

// Date and Time Demo
void demo_datetime() {
    time_t t = time(NULL);
    struct tm *local = localtime(&t);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);
    printf("Current date and time: %s\n", buffer);
}

// Miscellaneous Functions Demo
void demo_miscellaneous() {
    srand(time(NULL));
    printf("Random numbers: %d, %d, %d\n", rand(), rand(), rand());
}

int main() {
    printf("=== C-Style Strings ===\n");
    demo_cstrings();

    printf("\n=== Memory Manipulation ===\n");
    demo_memory();

    printf("\n=== Date and Time ===\n");
    demo_datetime();

    printf("\n=== Miscellaneous Functions ===\n");
    demo_miscellaneous();

    return 0;
}
