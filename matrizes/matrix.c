#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix createMatrix(int rows, int columns) {
    Matrix newMatrix;
    newMatrix.rows = rows;
    newMatrix.columns = columns;

    newMatrix.matrixRows = (MatrixRow*)malloc(rows * sizeof(MatrixRow));

    int i;
    for (i = 0; i < rows; i++) {
        newMatrix.matrixRows[i].head = NULL;
    }

    return newMatrix;
}

void insertElement(Matrix* A, int row, int column, int value) {
    if (row < 0 || row >= A->rows || column < 0 || column >= A->columns) {
        printf("Erro: Indices fora dos limites.\n");
        return;
    }

    Node* newElement = (Node*)malloc(sizeof(Node));
    newElement->column = column;
    newElement->value = value;
    newElement->next = NULL;

    if (A->matrixRows[row].head == NULL) {
        A->matrixRows[row].head = newElement;
        newElement->previous = NULL;
    } else {
        Node* current = A->matrixRows[row].head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newElement;
        newElement->previous = current;
    }
}

void printMatrix(Matrix A) {
    int i;
    for (i = 0; i < A.rows; i++) {
        printf("Linha %d: ", i);

        Node* current = A.matrixRows[i].head;
        while (current != NULL) {
            printf("(%d, %d)=%.2f ", i, current->column, (float)current->value);
            current = current->next;
        }

        printf("\n");
    }
}

Matrix readMatrix() {
    int rows, columns;
    printf("Informe o numero de linhas e colunas da matriz: ");
    scanf("%d %d", &rows, &columns);

    Matrix newMatrix = createMatrix(rows, columns);

    int i, j;
    float value;
    printf("Informe os elementos diferentes de zero da matriz (i, j, valor):\n");
    while (scanf("%d %d %f", &i, &j, &value) == 3) {
        insertElement(&newMatrix, i, j, value);
    }

    return newMatrix;
}

Matrix addMatrices(Matrix A, Matrix B) {
    if (A.rows != B.rows || A.columns != B.columns) {
        printf("Erro: As matrizes nao tem o mesmo tamanho.\n");
        exit(1);
    }

    Matrix result = createMatrix(A.rows, A.columns);

    int i;
    for (i = 0; i < A.rows; i++) {
        Node* currentA = A.matrixRows[i].head;
        Node* currentB = B.matrixRows[i].head;

        while (currentA != NULL || currentB != NULL) {
            if (currentA == NULL) {
                insertElement(&result, i, currentB->column, currentB->value);
                currentB = currentB->next;
            } else if (currentB == NULL) {
                insertElement(&result, i, currentA->column, currentA->value);
                currentA = currentA->next;
            } else {
                if (currentA->column == currentB->column) {
                    insertElement(&result, i, currentA->column, currentA->value + currentB->value);
                    currentA = currentA->next;
                    currentB = currentB->next;
                } else if (currentA->column < currentB->column) {
                    insertElement(&result, i, currentA->column, currentA->value);
                    currentA = currentA->next;
                } else {
                    insertElement(&result, i, currentB->column, currentB->value);
                    currentB = currentB->next;
                }
            }
        }
    }

    return result;
}

Matrix multiplyMatrices(Matrix A, Matrix B) {
    if (A.columns != B.rows) {
        printf("Erro: Numero de colunas de A nao e igual ao numero de linhas de B.\n");
        exit(1);
    }

    Matrix result = createMatrix(A.rows, B.columns);

    int i, j, k;
    for (i = 0; i < A.rows; i++) {
        for (j = 0; j < B.columns; j++) {
            float value = 0.0;

            for (k = 0; k < A.columns; k++) {
                Node* currentA = A.matrixRows[i].head;
                Node* currentB = B.matrixRows[k].head;

                while (currentA != NULL && currentB != NULL) {
                    if (currentA->column == k && currentB->column == j) {
                        value += currentA->value * currentB->value;
                        currentA = currentA->next;
                        currentB = currentB->next;
                    } else if (currentA->column < k) {
                        currentA = currentA->next;
                    } else if (currentB->column < j) {
                        currentB = currentB->next;
                    } else {
                        currentA = currentA->next;
                        currentB = currentB->next;
                    }
                }
            }

            if (value != 0.0) {
                insertElement(&result, i, j, value);
            }
        }
    }

    return result;
}

void freeMatrix(Matrix* A) {
    int i;
    for (i = 0; i < A->rows; i++) {
        Node* current = A->matrixRows[i].head;
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(A->matrixRows);
    A->rows = 0;
    A->columns = 0;
}

