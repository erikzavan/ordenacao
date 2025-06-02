#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// SelectionSort

// BubbleSort (padrao) 
void bubble_sort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                trocar(&v[j], &v[j + 1]);
            }
        }
    }
}

// BubbleSort (otimizado)
void bubble_sort_otimizado(int v[], int n) {
    int trocou;
    for (int i = 0; i < n - 1; i++) {
        trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                trocar(&v[j], &v[j + 1]);
                trocou = 1;
            }
        }
        if (trocou == 0)
            break;
    }
}

// InsertionSort (padrao)
// InsertionSort (otimizado)




// para medir o tempo

clock_t inicio = clock();
// chama a funcao de ordenacao
clock_t fim = clock();

double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("Tempo de execução: %.2f segundos\n", tempo);