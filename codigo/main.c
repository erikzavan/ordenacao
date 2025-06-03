#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordenacao.h"

extern void gerar_arquivo(const char* nome, int quantidade);
int* carregar_dados(const char *nome_arquivo, int *tamanho);
int busca_sequencial(int *v, int tamanho, int alvo);
int busca_binaria(int *v, int tamanho, int alvo);
void salvar_vetor(const char* nome_arquivo, int* v, int tamanho);

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

int main() {

    int pequeno = 40000; // 1 segundo
    int medio = 100000; // 30 segundos
    int grande = 250000; // 3 minutos (testar tempo de tds)
    
    //limpar csv

    FILE *f = fopen("tempos.csv", "w");
    fprintf(f, "Algoritmo,Tamanho,Tempo\n");
    fclose(f);

    //gerador

    char resposta;

    printf("quer gerar arquvios bin? s/n\n>");
    char linha[10];
    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, " %c", &resposta);

    switch (resposta)
    {
    case 's':
    case 'S':

        printf("gerando arquivos. . .\n\n");

	gerar_arquivo("dados/pequeno.bin", pequeno);
        printf("pequeno gerado\n");

	gerar_arquivo("dados/medio.bin", medio);
        printf("medio gerado\n");

	gerar_arquivo("dados/grande.bin", grande);
        printf("grande gerado\n");

    printf("arquivos gerados!!!!!!!!\n\n");

        break;
    
    default:
        printf("arquivos nao gerados.\n\n");
        break;
    }

    const char* arquivos[] = {
        "dados/pequeno.bin",
        "dados/medio.bin",
        "dados/grande.bin"
    };

    const char* nomes[] = {
        "pequeno",
        "medio",
        "grande"
    };

    for (int a = 0; a < 3; a++) {
        int tamanho;
        int* original = carregar_dados(arquivos[a], &tamanho);
        int* temp = malloc(tamanho * sizeof(int));

        printf("processando selection %s\n", nomes[a]);
            copiar_vetor(temp, original, tamanho);
            salvar_csv("selection_sort", nomes[a], medir_tempo(selection_sort, temp, tamanho, "selection_sort"));
            char nome_sel[100];
            sprintf(nome_sel, "dados/ordenado_selection_%s.bin", nomes[a]);
            salvar_vetor(nome_sel, temp, tamanho);

        printf("processando bubble %s\n", nomes[a]);
            copiar_vetor(temp, original, tamanho);
            salvar_csv("bubble_sort", nomes[a], medir_tempo(bubble_sort, temp, tamanho, "bubble_sort"));
            char nome_bub[100];
            sprintf(nome_bub, "dados/ordenado_bubble_%s.bin", nomes[a]);
            salvar_vetor(nome_bub, temp, tamanho);
        
            copiar_vetor(temp, original, tamanho);
            salvar_csv("bubble_sort_otimizado", nomes[a], medir_tempo(bubble_sort_otimizado, temp, tamanho, "bubble_sort_otimizado"));
            char nome_bubo[100];
            sprintf(nome_bubo, "dados/ordenado_bubble_otimizado_%s.bin", nomes[a]);
            salvar_vetor(nome_bubo, temp, tamanho);

        printf("processando insertion %s\n", nomes[a]);
            copiar_vetor(temp, original, tamanho);
            salvar_csv("insertion_sort", nomes[a], medir_tempo(insertion_sort, temp, tamanho, "insertion_sort"));
            char nome_ins[100];
            sprintf(nome_ins, "dados/ordenado_insertion_%s.bin", nomes[a]);
            salvar_vetor(nome_ins, temp, tamanho);

            copiar_vetor(temp, original, tamanho);
            salvar_csv("insertion_sort_otimizado", nomes[a], medir_tempo(insertion_sort_otimizado, temp, tamanho, "insertion_sort_otimizado"));
            char nome_inso[100];
            sprintf(nome_inso, "dados/ordenado_insertion_otimizado_%s.bin", nomes[a]);
            salvar_vetor(nome_inso, temp, tamanho);

        printf("%s pronto!\n\n", nomes[a]);

        free(temp);
        free(original);
    }

    //buscas

    while(1){
        char tipo_busca[20];
        char tipo_ordenacao[30];
        char tamanho_arquivo[20];
        int valor;

        printf("\n=== BUSCA EM ARQUIVO ORDENADO ===\n");
        printf("digite 0 em qualquer entrada para sair\n");

        //tipo de busca
        while (1) {
            printf("\ntipo de busca (sequencial / binaria): ");
            scanf("%s", tipo_busca);
            if (strcmp(tipo_busca, "0") == 0) return 0;
            if (strcmp(tipo_busca, "sequencial") == 0 || strcmp(tipo_busca, "binaria") == 0) break;
            printf("tipo invalido digite novamente\n");
        }

        //tipo de ordenacao
        while (1) {
            printf("\ntipo de ordenacao (selection / bubble / bubble_otimizado / insertion / insertion_otimizado): ");
            scanf("%s", tipo_ordenacao);
            if (strcmp(tipo_ordenacao, "0") == 0) return 0;
            if (
                strcmp(tipo_ordenacao, "selection") == 0 ||
                strcmp(tipo_ordenacao, "bubble") == 0 ||
                strcmp(tipo_ordenacao, "bubble_otimizado") == 0 ||
                strcmp(tipo_ordenacao, "insertion") == 0 ||
                strcmp(tipo_ordenacao, "insertion_otimizado") == 0
        ) break;
            printf("ordenacao invalida digite novamente\n");
        }

        //tamanho arquivo
        while (1) {
            printf("\ntamanho do arquivo (pequeno / medio / grande): ");
            scanf("%s", tamanho_arquivo);
            if (strcmp(tamanho_arquivo, "0") == 0) return 0;
            if (
                strcmp(tamanho_arquivo, "pequeno") == 0 ||
                strcmp(tamanho_arquivo, "medio") == 0 ||
                strcmp(tamanho_arquivo, "grande") == 0
            ) break;
            printf("tamanho invalido digite novamente\n");
        }

        //valor pra buscar
        printf("\nvalor a ser buscado (ou 0 para sair): ");
        scanf("%d", &valor);
        if (valor == 0) return 0;

        // montar nome
        char nome_arquivo[100];
        sprintf(nome_arquivo, "dados/ordenado_%s_%s.bin", tipo_ordenacao, tamanho_arquivo);

        // carregar e buscar
        int tam;
        int* vetor = carregar_dados(nome_arquivo, &tam);

        int pos = -1;
        if (strcmp(tipo_busca, "sequencial") == 0) {
            pos = busca_sequencial(vetor, tam, valor);
        } else {
            pos = busca_binaria(vetor, tam, valor);
        }

        if (pos != -1)
            printf("valor %d encontrado na posicao %d\n", valor, pos);
        else
            printf("valor %d nao encontrado\n", valor);

        free(vetor);
        printf("\n");
    }
    return 0;
}





// gcc codigo/main.c codigo/ordenacao.c codigo/busca.c codigo/gerador_dados.c -o programa