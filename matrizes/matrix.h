#ifndef MATRIX_H
#define MATRIX_H

typedef struct Node {
    int column;
    int value;
    struct Node* next;
    struct Node* previous;
} Node;

typedef struct {
    Node* head;
} MatrixRow;

typedef struct {
    int rows;
    int columns;
    MatrixRow* matrixRows;
} Matrix;

Matrix createMatrix(int rows, int columns);
void insertElement(Matrix* A, int row, int column, int value);
void printMatrix(Matrix A);
Matrix readMatrix();
Matrix addMatrices(Matrix A, Matrix B);
Matrix multiplyMatrices(Matrix A, Matrix B);
void freeMatrix(Matrix* A);

#endif

