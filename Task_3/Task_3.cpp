#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

typedef struct _stack_element {
    char data;
    struct _stack_element* next;
} StackElement;

StackElement* stack = NULL;

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

    setlocale(LC_NUMERIC, "");

    printf("Enter an expression in RPN: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    char* output = get_expression(input);
    if (output == NULL) {
        printf("Invalid expression.\n");
        return 1;
    }

    printf("RPN expression: %s\n", output);

    result = evaluate(output);
    printf("Result: %.2lf\n", result);

    free(output);
    return 0;
}

int is_delimiter(char c) {
    return (c == ' ' || c == '=');
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '√');
}

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
    default: return -1;
    }
}

void push(char c) {
    StackElement* new_element = malloc(sizeof(StackElement));
    new_element->data = c;
    new_element->next = stack;
    stack = new_element;
}

char pop() {
    if (stack == NULL) {
        return '\0';
    }

    char top_element = stack->data;
    StackElement* temp = stack;
    stack = stack->next;
    free(temp);
    return top_element;
}

char* get_expression(const char* input) {
    char* output = malloc(MAX_SIZE * sizeof(char));
    if (output == NULL) {
        return NULL;
    }

    int output_index = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        if (is_delimiter(c)) {
            continue;
        }

        if (isdigit(c)) {
            while (isdigit(input[i]) || input[i] == '.') {
                output[output_index++] = input[i++];
            }
            output[output_index++] = ' ';
            i--;
        }
        else if (is_operator(c)) {
            while (stack != NULL && get_precedence(stack->data) >= get_precedence(c)) {
                output[output_index++] = pop();
                output[output_index++] = ' ';
            }
            push(c);
        }
        else {
            printf("Invalid character: %c\n", c);
            free(output);
            return NULL;
        }
    }

    while (stack != NULL) {
        output[output_index++] = pop();
        output[output_index++] = ' ';
    }

    output[output_index] = '\0';
    return output;
}
