#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

// Structure for stack elements (char and pointer to next element)
typedef struct _stack_element {
    char data;
    struct _stack_element* next;
} StackElement;

// Stack (top points to the top element)
StackElement* stack = NULL;

// Function prototypes
int is_delimiter(char c);
int is_operator(char c);
int get_precedence(char c);
void push(char c);
char pop();
char* get_expression(const char* input);
double evaluate(const char* expression);

int main() {
    char input[MAX_SIZE];
    double result;

    // Set decimal separator for output (optional)
    setlocale(LC_NUMERIC, "");

    printf("Enter an expression in RPN: ");
    fgets(input, sizeof(input), stdin);

    // Remove trailing newline character (if present)
    input[strcspn(input, "\n")] = '\0';

    char* output = get_expression(input);
    if (output == NULL) {
        printf("Invalid expression.\n");
        return 1; // Return error code
    }

    printf("RPN expression: %s\n", output);

    result = evaluate(output);
    printf("Result: %.2lf\n", result);

    // Free memory allocated for the output string
    free(output);

    return 0;
}

// Check if a character is a delimiter (space or equals)
int is_delimiter(char c) {
    return (c == ' ' || c == '=');
}

// Check if a character is an operator
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '√');
}

// Get operator precedence (higher value for higher precedence)
int get_precedence(char c) {
    switch (c) {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;
    case '^': return 4;
    case '√': return 5;
    default: return -1; // Error handling for invalid operators
    }
}

// Push an element onto the stack
void push(char c) {
    StackElement* new_element = malloc(sizeof(StackElement));
    new_element->data = c;
    new_element->next = stack;
    stack = new_element;
}

// Pop an element from the stack
char pop() {
    if (stack == NULL) {
        return '\0'; // Error handling for empty stack
    }

    char top_element = stack->data;
    StackElement* temp = stack;
    stack = stack->next;
    free(temp);
    return top_element;
}

// Convert infix expression (with spaces) to RPN expression
char* get_expression(const char* input) {
    char* output = malloc(MAX_SIZE * sizeof(char));
    if (output == NULL) {
        return NULL; // Memory allocation failed
    }

    int output_index = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        if (is_delimiter(c)) {
            continue;
        }

        if (isdigit(c)) {
            // Append digits until encountering a delimiter or operator
            while (isdigit(input[i]) || input[i] == '.') {
                output[output_index++] = input[i++];
            }
            output[output_index++] = ' '; // Add space between operands
            i--; // Decrement i to process the operator after the operand
        }
        else if (is_operator(c)) {
            while (stack != NULL && get_precedence(stack->data) >= get_precedence(c)) {
                output[output_index++] = pop();
                output[output_index++] = ' ';
            }
            push(c);
        }
        else {
            // Error handling for invalid characters
            printf("Invalid character: %c\n", c);
            free(output); // Free memory before returning
            return NULL; // Indicate error
        }
    }

    // Pop remaining operators from the stack
    while (stack != NULL) {
        output[output_index++] = pop();
        output[output_index++] = ' ';
    }

    output[output_index] = '\0'; // Null-terminate the string
    return output;
}