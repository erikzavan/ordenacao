#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "busca.h"
#include "ordenacao.h"
#include "gerador_dados.h"
#include "app_utils.h"

void copiar_vetor(int* destino, int* origem, int tamanho) {
    for (int i = 0; i < tamanho; i++)
        destino[i] = origem[i];
}

void salvar_csv(const char *algoritmo, const char* nome_arquivo, double tempo) {
    FILE *file = fopen("tempos.csv", "a");
    if (!file){
        exit(1);
    }

    fprintf(file, "%s,%s,%.4f\n", algoritmo, nome_arquivo, tempo);
    fclose(file);
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

    printf("→ Ordenando %s...\n", nome_entrada);

    processar_ordenacao("selection", selection_sort, original, tamanho, nome_entrada);
    processar_ordenacao("bubble", bubble_sort, original, tamanho, nome_entrada);
    processar_ordenacao("bubble_otimizado", bubble_sort_otimizado, original, tamanho, nome_entrada);
    processar_ordenacao("insertion", insertion_sort, original, tamanho, nome_entrada);
    processar_ordenacao("insertion_otimizado", insertion_sort_otimizado, original, tamanho, nome_entrada);

    free(original);
}

void gerador_arquivos(int pequeno, int medio, int grande) {
    char resposta;
    printf("quer gerar arquivos binarios? s/n\n> ");
    char linha[10];
    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, " %c", &resposta);

    if (resposta == 's' || resposta == 'S') {
        gerar_arquivo("dados/pequeno.bin", pequeno);
        gerar_arquivo("dados/medio.bin", medio);
        gerar_arquivo("dados/grande.bin", grande);
        printf("arquivos gerados!\n");
    }
}

void menu_busca() {
    while (1) {
        char tipo_busca[20];
        char tipo_ordenacao[30];
        char tamanho_arquivo[20];
        int valor;

        printf("\n=== BUSCA EM ARQUIVO ORDENADO ===\n");
        printf("digite 0 em qualquer entrada para sair\n");

        while (1) {
            printf("\ntipo de busca (sequencial / binaria): ");
            scanf("%s", tipo_busca);
            if (strcmp(tipo_busca, "0") == 0) return;
            if (strcmp(tipo_busca, "sequencial") == 0 || strcmp(tipo_busca, "binaria") == 0) break;
            printf("tipo invalido digite novamente\n");
        }

        while (1) {
            printf("\ntipo de ordenacao (selection / bubble / bubble_otimizado / insertion / insertion_otimizado): ");
            scanf("%s", tipo_ordenacao);
            if (strcmp(tipo_ordenacao, "0") == 0) return;
            if (
                strcmp(tipo_ordenacao, "selection") == 0 ||
                strcmp(tipo_ordenacao, "bubble") == 0 ||
                strcmp(tipo_ordenacao, "bubble_otimizado") == 0 ||
                strcmp(tipo_ordenacao, "insertion") == 0 ||
                strcmp(tipo_ordenacao, "insertion_otimizado") == 0
            ) break;
            printf("ordenacao invalida digite novamente\n");
        }

        while (1) {
            printf("\ntamanho do arquivo (pequeno / medio / grande): ");
            scanf("%s", tamanho_arquivo);
            if (strcmp(tamanho_arquivo, "0") == 0) return;
            if (
                strcmp(tamanho_arquivo, "pequeno") == 0 ||
                strcmp(tamanho_arquivo, "medio") == 0 ||
                strcmp(tamanho_arquivo, "grande") == 0
            ) break;
            printf("tamanho invalido digite novamente\n");
        }

        printf("\nvalor a ser buscado (ou 0 para sair): ");
        scanf("%d", &valor);
        if (valor == 0) return;

        char nome_arquivo[100];
        sprintf(nome_arquivo, "dados/ordenado_%s_%s.bin", tipo_ordenacao, tamanho_arquivo);

        int tam;
        int* vetor = carregar_dados(nome_arquivo, &tam);
        int pos = strcmp(tipo_busca, "sequencial") == 0
            ? busca_sequencial(vetor, tam, valor)
            : busca_binaria(vetor, tam, valor);

        if (pos != -1)
            printf("valor %d encontrado na posicao %d\n", valor, pos);
        else
            printf("valor %d nao encontrado\n", valor);

        free(vetor);
    }
}

void limpar_csv() {
    FILE *file = fopen("tempos.csv", "w");
    if (!file) {
        perror("Erro ao limpar tempos.csv");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Algoritmo,Tamanho,Tempo\n");
    fclose(file);
}
