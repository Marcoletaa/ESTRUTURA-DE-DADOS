#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float X;
    float Y;
} Ponto;

float calcArea(Ponto* vertices, int nVert) {
    if (nVert < 3) {
        return 0.0;
    }

    float area = 0.0;
    int i = 0;
    int j = nVert - 1;

    for (i; i < nVert; i++) {
        area += (vertices[j].X + vertices[i].X) * (vertices[j].Y - vertices[i].Y);
        j = i;
    }

    return fabsf(area) / 2.0;
}

int main() {
    FILE* arquivo;
    int nVert;
    int i =0;

    arquivo = fopen("vertices.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fscanf(arquivo, "%d", &nVert);

    Ponto* vertices = (Ponto*)malloc(nVert * sizeof(Ponto));

    if (vertices == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        return 1;
    }

    for (i; i < nVert; i++) {
        fscanf(arquivo, "%f %f", &vertices[i].X, &vertices[i].Y);
    }

    fclose(arquivo);

    float area = calcArea(vertices, nVert);

    printf("A area do poligono e %.2f\n", area);

    free(vertices);

    return 0;
}

