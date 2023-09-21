#include <stdio.h>
#include <string.h>
void swap(char *arr[], int i, int j) {
    char *temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
int partition(char *arr[], int low, int high) {
    char *pivot = arr[high];
    int i = (low - 1);
    int j = low;

    for (j ; j <= high - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, high); 
    return (i + 1);
}

void quicksort(char *arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}

int main() {
    char *arr[20] = {
        "maca", "banana", "pera", "uva", "laranja", "abacaxi", "limao", "manga", "abacate", "kiwi",
        "cereja", "morango", "pessego", "goiaba", "melancia", "framboesa", "amora", "caqui", "figo", "papaya"
    };

    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 0;

    quicksort(arr, 0, n - 1);

    FILE *arquivo = fopen("saida.txt", "w");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fprintf(arquivo, "Vetor ordenado:\n");
    for (i ; i < n; i++) {
        fprintf(arquivo, "%s\n", arr[i]);
    }

    fclose(arquivo);

    printf("Arquivo 'saida.txt' gerado com sucesso.\n");

    return 0;
}

