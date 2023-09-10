#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_BUFFER 200

typedef struct {
    char nome[MAX_NOME];
    char telefone[MAX_NOME];
    char curso[MAX_NOME];
    float nota1;
    float nota2;
    float media;
    char situacao[20];
} Aluno;

int main() {
    FILE *entrada, *saida;
    char linha[MAX_BUFFER];
    char *token;
    Aluno aluno;

    // Abre o arquivo de entrada (leitura)
    entrada = fopen("DadosEntrada.csv", "r");
    if (entrada == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    // Abre o arquivo de sa�da (escrita)
    saida = fopen("SituacaoFinal.csv", "w");
    if (saida == NULL) {
        perror("Erro ao abrir o arquivo de sa�da");
        fclose(entrada);
        return 1;
    }

    // Escreve o cabe�alho no arquivo de sa�da
    fprintf(saida, "Nome,Media,Situacao\n");

    // L� e processa os dados do arquivo de entrada
    while (fgets(linha, MAX_BUFFER, entrada) != NULL) {
        // Divide a linha em tokens usando v�rgula como delimitador
        token = strtok(linha, ",");
        strncpy(aluno.nome, token, MAX_NOME);

        token = strtok(NULL, ",");
        strncpy(aluno.telefone, token, MAX_NOME);

        token = strtok(NULL, ",");
        strncpy(aluno.curso, token, MAX_NOME);

        token = strtok(NULL, ",");
        aluno.nota1 = atof(token);

        token = strtok(NULL, ",");
        aluno.nota2 = atof(token);

        // Calcula a m�dia
        aluno.media = (aluno.nota1 + aluno.nota2) / 2.0;

        // Determina a situa��o (aprovado ou reprovado)
        if (aluno.media > 7.0) {
            strcpy(aluno.situacao, "APROVADO");
        } else {
            strcpy(aluno.situacao, "REPROVADO");
        }

        // Escreve os dados do aluno no arquivo de sa�da
        fprintf(saida, "%s,%.2f,%s\n", aluno.nome, aluno.media, aluno.situacao);
    }

    // Fecha os arquivos
    fclose(entrada);
    fclose(saida);

    printf("Processamento concluido. Os resultados foram salvos em SituacaoFinal.csv.\n");

    return 0;
}

