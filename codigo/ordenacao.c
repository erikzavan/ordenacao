#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ordenacao.h"
#include "busca.h"
#include "app_utils.h"

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
void selection_sort(int v[], int n, const char* nome, long* comp, long* troc) {
    for (int i = 0; i < n; i++) {
        int menorIndice = i;
        for (int j = i + 1; j < n; j++) {
            (*comp)++;
            if (v[j] < v[menorIndice]) {
                menorIndice = j;
            }
        }
        trocar(&v[i], &v[menorIndice]);
        (*troc)++;

        if (i % (n / 1000 + 1) == 0) {
            mostrar_progresso(i, n, nome);
        }
    }
    mostrar_progresso(n, n, nome);
    printf("\n");
}

// BubbleSort (padrao) 
void bubble_sort(int v[], int n, const char* nome, long* comp, long* troc) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*comp)++;
            if (v[j] > v[j + 1]) {
                trocar(&v[j], &v[j + 1]);
                (*troc)++;
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
void bubble_sort_otimizado(int v[], int n, const char* nome, long* comp, long* troc) {
    int trocou;
    for (int i = 0; i < n - 1; i++) {
        trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            (*comp)++;
            if (v[j] > v[j + 1]) {
                trocar(&v[j], &v[j + 1]);
                (*troc)++;
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
void insertion_sort(int v[], int n, const char* nome, long* comp, long* troc) {
    for (int i = 1; i < n; i++) {
        int atual = v[i];
        int j = i - 1;
        (*comp)++;
        while (j >= 0 && v[j] > atual) {
            v[j + 1] = v[j];
            j--;
            (*comp)++;
            (*troc)++;
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
void insertion_sort_otimizado(int v[], int n, const char* nome, long* comp, long* troc)
{
    for (int i = 1; i < n; i++) {
        int atual = v[i];
        int j = i - 1;
        (*comp)++;
        while (j >= 0 && v[j] > atual) {
            v[j + 1] = v[j];
            j--;
            (*comp)++;
            (*troc)++;
        }
        v[j + 1] = atual;

        if (i % (n / 1000 + 1) == 0) {
            mostrar_progresso(i, n, nome);
        }
    }

    mostrar_progresso(n, n, nome);
    printf("\n");
}

void processar_ordenacao(const char* nome_algoritmo,
                         void (*alg)(int*, int, const char*),
                         int* original, int tamanho,
                         const char* nome_entrada) {
    int* temp = malloc(tamanho * sizeof(int));
    if (!temp) {
        perror("erro ao alocar vetor temp\n");
        exit(1);
    }

    copiar_vetor(temp, original, tamanho);
    double tempo = medir_tempo(alg, temp, tamanho, nome_algoritmo);
    salvar_csv(nome_algoritmo, nome_entrada, tempo);

    char nome_bin[100];
    sprintf(nome_bin, "dados/ordenado_%s_%s.bin", nome_algoritmo, nome_entrada);
    salvar_vetor(nome_bin, temp, tamanho);

    free(temp);
}

void ordenar_todos(const char* arquivo, const char* nome_entrada) {
    int tamanho;
    int* original = carregar_dados(arquivo, &tamanho);

    printf("\nordenando %s...\n", nome_entrada);

    processar_ordenacao("selection", selection_sort, original, tamanho, nome_entrada);
    processar_ordenacao("bubble", bubble_sort, original, tamanho, nome_entrada);
    processar_ordenacao("bubble_otimizado", bubble_sort_otimizado, original, tamanho, nome_entrada);
    processar_ordenacao("insertion", insertion_sort, original, tamanho, nome_entrada);
    processar_ordenacao("insertion_otimizado", insertion_sort_otimizado, original, tamanho, nome_entrada);

    free(original);
}