#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFFER_SIZE 1024

typedef struct {
    char* buffer;
    size_t buffer_length;
    int input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = (char*)malloc(INITIAL_BUFFER_SIZE);
    input_buffer->buffer_length = INITIAL_BUFFER_SIZE;
    input_buffer->input_length = 0;

    return input_buffer;
}

void print_prompt() {
    printf("db > ");
}

void read_input(InputBuffer* input_buffer) {
    if (fgets(input_buffer->buffer, input_buffer->buffer_length, stdin) == NULL) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = strlen(input_buffer->buffer);

    if (input_buffer->input_length > 0 && input_buffer->buffer[input_buffer->input_length - 1] == '\n') {
        input_buffer->buffer[input_buffer->input_length - 1] = '\0';
        input_buffer->input_length--;
    }
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new_input_buffer();

    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit") == 0) {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        }
        else {
            printf("Unrecognised command '%s'.\n", input_buffer->buffer);
        }
    }
}