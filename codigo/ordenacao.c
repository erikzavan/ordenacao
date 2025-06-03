
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ordenacao.h"
#include "busca.h"
#include "app_utils.h"
#define ESCALA 10000L

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

double medir_tempo(void (*func)(int*, int, const char*, unsigned long long*, unsigned long long*), int* v, int n, const char* nome, unsigned long long* comp, unsigned long long* troc) {
    clock_t inicio = clock();
    func(v, n, nome, comp, troc);
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

void selection_sort(int v[], int n, const char* nome, unsigned long long* comp, unsigned long long* troc) {
    unsigned long long comps_real = 0, trocs_real = 0;
    for (int i = 0; i < n; i++) {
        int menorIndice = i;
        for (int j = i + 1; j < n; j++) {
            comps_real++;
            if (v[j] < v[menorIndice]) {
                menorIndice = j;
            }
        }
        trocar(&v[i], &v[menorIndice]);
        trocs_real++;
        if (i % (n / 1000 + 1) == 0) {
            mostrar_progresso(i, n, nome);
        }
    }
    mostrar_progresso(n, n, nome);
    printf("\n");
    *comp = comps_real / ESCALA;
    *troc = trocs_real / ESCALA;
}

void bubble_sort(int v[], int n, const char* nome, unsigned long long* comp, unsigned long long* troc) {
    unsigned long long comps_real = 0, trocs_real = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comps_real++;
            if (v[j] > v[j + 1]) {
                trocar(&v[j], &v[j + 1]);
                trocs_real++;
            }
        }
        if (i % (n / 1000 + 1) == 0) {
            mostrar_progresso(i, n, nome);
        }
    }
    mostrar_progresso(n, n, nome);
    printf("\n");
    *comp = comps_real / ESCALA;
    *troc = trocs_real / ESCALA;
}

void bubble_sort_otimizado(int v[], int n, const char* nome, unsigned long long* comp, unsigned long long* troc) {
    unsigned long long comps_real = 0, trocs_real = 0;
    int trocou;
    for (int i = 0; i < n - 1; i++) {
        trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            comps_real++;
            if (v[j] > v[j + 1]) {
                trocar(&v[j], &v[j + 1]);
                trocs_real++;
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
    *comp = comps_real / ESCALA;
    *troc = trocs_real / ESCALA;
}

void insertion_sort(int v[], int n, const char* nome, unsigned long long* comp, unsigned long long* troc) {
    unsigned long long comps_real = 0, trocs_real = 0;
    for (int i = 1; i < n; i++) {
        int atual = v[i];
        int j = i - 1;
        comps_real++;
        while (j >= 0 && v[j] > atual) {
            v[j + 1] = v[j];
            j--;
            comps_real++;
            trocs_real++;
        }
        v[j + 1] = atual;

        if (i % (n / 1000 + 1) == 0) {
            mostrar_progresso(i, n, nome);
        }
    }
    mostrar_progresso(n, n, nome);
    printf("\n");
    *comp = comps_real / ESCALA;
    *troc = trocs_real / ESCALA;
}

void insertion_sort_otimizado(int v[], int n, const char* nome, unsigned long long* comp, unsigned long long* troc) {
    unsigned long long comps_real = 0, trocs_real = 0;
    for (int i = 1; i < n; i++) {
        int atual = v[i];
        int j = i - 1;
        comps_real++;
        while (j >= 0 && v[j] > atual) {
            v[j + 1] = v[j];
            j--;
            comps_real++;
            trocs_real++;
        }
        v[j + 1] = atual;

        if (i % (n / 1000 + 1) == 0) {
            mostrar_progresso(i, n, nome);
        }
    }
    mostrar_progresso(n, n, nome);
    printf("\n");
    *comp = comps_real / ESCALA;
    *troc = trocs_real / ESCALA;
}

void processar_ordenacao(const char* nome_algoritmo,
                         void (*alg)(int*, int, const char*, unsigned long long*, unsigned long long*),
                         int* original, int tamanho,
                         const char* nome_entrada) {
    int* temp = malloc(tamanho * sizeof(int));
    if (!temp) {
        perror("erro ao alocar vetor temp\n");
        exit(1);
    }

    unsigned long long comparacoes = 0, trocas = 0;
    copiar_vetor(temp, original, tamanho);

    double tempo = medir_tempo(alg, temp, tamanho, nome_algoritmo, &comparacoes, &trocas);
    salvar_csv(nome_algoritmo, nome_entrada, tempo, comparacoes, trocas);

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