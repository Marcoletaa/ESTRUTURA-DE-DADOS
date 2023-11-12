#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void printSeparator() {
    printf("------------------------------------------------------\n");
}

void printMatrixInfo(const char* matrixName) {
    printf("\n%s:\n", matrixName);
}

int main() {
    printf("1 - Criacao de Matriz\n");
    Matrix A = createMatrix(3, 3);
    printMatrixInfo("Matriz A criada");
    printMatrix(A);
    printSeparator();

    printf("\n2 - Insercao de Elementos\n");
    insertElement(&A, 0, 1, 10);
    insertElement(&A, 1, 2, 20);
    insertElement(&A, 2, 0, 30);
    printMatrixInfo("Matriz A apos a insercao de elementos");
    printMatrix(A);
    printSeparator();

    printf("\n3 - Leitura de Matriz\n");
    Matrix B = readMatrix();
    printMatrixInfo("Matriz B lida do arquivo");
    printMatrix(B);
    printSeparator();

    printf("\n4 - Soma de Matrizes\n");
    Matrix C = addMatrices(A, B);
    printMatrixInfo("Matriz C (soma de A e B)");
    printMatrix(C);
    printSeparator();

    printf("\n5 - Multiplicacao de Matrizes\n");
    Matrix D = multiplyMatrices(A, B);
    printMatrixInfo("Matriz D (produto de A e B)");
    printMatrix(D);
    printSeparator();

    printf("\n6 - Liberacao de Memoria\n");
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    printf("Memoria liberada com sucesso.\n");

    return 0;
}

