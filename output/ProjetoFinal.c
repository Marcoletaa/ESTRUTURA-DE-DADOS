 #include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX_EXP 100

typedef struct Node {
    double data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

void initialize(Stack *stack);
void push(Stack *stack, double value);
double pop(Stack *stack);
double calculateLog(double value);
double calculateSin(double value);
double calculateCos(double value);
double calculateTan(double value);
double calculatePower(double base, double exponent);
double calculateRoot(double value);
double evaluatePostfixExpression(const char *expression);

double convertToDouble(const char *expression, int *position);

int main() {
    const char *expressions[] = {
        "3 4 + 5 *",
        "7 2 * 4 +",
        "8 5 2 4 + * +",
        "6 2 / 3 + 4 *",
        "9 5 2 8 * 4 + * +",
        "2 3 + l 5 /",
        "10 l 3 ^ 2 + ",
        "45 60 + 30 c *",
        "0.5 45 s 2 ^ + ",
        "3 4 + 5 t *"
    };

    for (int i = 0; i < sizeof(expressions) / sizeof(expressions[0]); ++i) {
        double result = evaluatePostfixExpression(expressions[i]);
        printf("Test %d: Result: %f\n", i + 1, result);
    }

    return 0;
}

void initialize(Stack *stack) {
    stack->top = NULL;
}

void push(Stack *stack, double value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

double pop(Stack *stack) {
    if (stack->top != NULL) {
        Node *temp = stack->top;
        double value = temp->data;
        stack->top = temp->next;
        free(temp);
        return value;
    } else {
        fprintf(stderr, "Error: Empty stack\n");
        exit(EXIT_FAILURE);
    }
}

double calculateLog(double value) {
    return log10(value);
}

double calculateSin(double value) {
    return sin(value);
}

double calculateCos(double value) {
    return cos(value);
}

double calculateTan(double value) {
    return tan(value);
}

double calculatePower(double base, double exponent) {
    return pow(base, exponent);
}

double calculateRoot(double value) {
    return sqrt(value);
}

double convertToDouble(const char *expression, int *position) {
    double result = 0.0;
    int decimalFound = 0;
    int decimalPlaces = 0;

    while (isdigit(expression[*position]) || expression[*position] == '.') {
        if (expression[*position] == '.') {
            decimalFound = 1;
        } else {
            result = result * 10 + (expression[*position] - '0');
            if (decimalFound) {
                decimalPlaces++;
            }
        }
        (*position)++;
    }

    while (decimalPlaces > 0) {
        result /= 10.0;
        decimalPlaces--;
    }

    return result;
}

double evaluatePostfixExpression(const char *expression) {
    Stack stack;
    initialize(&stack);

    for (int i = 0; expression[i] != '\0'; ++i) {
        if (isdigit(expression[i]) || (expression[i] == '-' && isdigit(expression[i + 1]))) {
            int position = i;
            double value = convertToDouble(expression, &position);
            push(&stack, value);
            i = position - 1;
        } else if (expression[i] == ' ' || expression[i] == '\t') {
            continue;
        } else {
            double operand2, operand1;

            switch (expression[i]) {
                case '+':
                    operand2 = pop(&stack);
                    operand1 = pop(&stack);
                    push(&stack, operand1 + operand2);
                    break;
                case '-':
                    operand2 = pop(&stack);
                    operand1 = pop(&stack);
                    push(&stack, operand1 - operand2);
                    break;
                case '*':
                    operand2 = pop(&stack);
                    operand1 = pop(&stack);
                    push(&stack, operand1 * operand2);
                    break;
                case '/':
                    operand2 = pop(&stack);
                    operand1 = pop(&stack);
                    if (operand2 != 0.0) {
                        push(&stack, operand1 / operand2);
                    } else {
                        fprintf(stderr, "Error: Division by zero\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                case 'l':
                    push(&stack, calculateLog(pop(&stack)));
                    break;
                case 's':
                    push(&stack, calculateSin(pop(&stack)));
                    break;
                case 'c':
                    push(&stack, calculateCos(pop(&stack)));
                    break;
                case 't':
                    push(&stack, calculateTan(pop(&stack)));
                    break;
                case '^':
                    operand2 = pop(&stack);
                    operand1 = pop(&stack);
                    push(&stack, calculatePower(operand1, operand2));
                    break;
                case 'r':
                    push(&stack, calculateRoot(pop(&stack)));
                    break;
                default:
                    fprintf(stderr, "Error: Invalid operator\n");
                    exit(EXIT_FAILURE);
            }
        }
    }

    return pop(&stack);
}
