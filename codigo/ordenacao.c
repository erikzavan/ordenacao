#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ordenacao.h"

void mostrar_progresso(int atual, int total, const char* nome) {
    double pct = (100.0 * atual) / total;
    int blocos = (int)(20.0 * atual / total);

    printf("\r%s [", nome);
    for (int i = 0; i < 20; i++) {
        if (i < blocos) printf("#");
        else printf("-");
    }
    printf("] %6.1f%%", pct);
    fflush(stdout);
}

double medir_tempo(void (*func)(int*, int, const char*), int* v, int n, const char* nome) {
    clock_t inicio = clock();
    func(v, n, nome);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo de execucao: %.2f segundos\n---\n", tempo);

    return tempo;
}

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// SelectionSort
void selection_sort(int v[], int n, const char* nome) {
    for (int i = 0; i < n; i++) {
        int menorIndice = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[menorIndice]) {
                menorIndice = j;
            }
        }
        trocar(&v[i], &v[menorIndice]);

        if (i % (n / 1000 + 1) == 0) {
            mostrar_progresso(i, n, nome);
        }
    }
    mostrar_progresso(n, n, nome);
    printf("\n");
}

// BubbleSort (padrao) 
void bubble_sort(int v[], int n, const char* nome) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                trocar(&v[j], &v[j + 1]);
            }
        }
        if (i % (n / 1000 + 1) == 0) {
            mostrar_progresso(i, n, nome);
        }
    }
    mostrar_progresso(n, n, nome);
    printf("\n");
}

// BubbleSort (otimizado)
void bubble_sort_otimizado(int v[], int n, const char* nome) {
    int trocou;
    for (int i = 0; i < n - 1; i++) {
        trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                trocar(&v[j], &v[j + 1]);
                trocou = 1;
            }
        }
        if (i % (n / 1000 + 1) == 0) {
            mostrar_progresso(i, n, nome);
        }
        if (trocou == 0) break;
    }
    mostrar_progresso(n, n, nome);
    printf("\n");
}

// InsertionSort (padrao)
void insertion_sort(int v[], int n, const char* nome) {
    for (int i = 1; i < n; i++) {
        int atual = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > atual) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = atual;

        if (i % (n / 1000 + 1) == 0) {
            mostrar_progresso(i, n, nome);
        }
    }
    mostrar_progresso(n, n, nome);
    printf("\n");
}

// InsertionSort (otimizado)
void insertion_sort_otimizado(int v[], int n, const char* nome)
{
    for (int i = 1; i < n; i++) {
        int atual = v[i];
        int j = i - 1;
        
        while (j >= 0 && v[j] > atual) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = atual;

        if (i % (n / 1000 + 1) == 0) {
            mostrar_progresso(i, n, nome);
        }
    }

    mostrar_progresso(n, n, nome);
    printf("\n");
}
