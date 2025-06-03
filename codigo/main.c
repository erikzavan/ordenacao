#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordenacao.h"

extern void gerar_arquivo(const char* nome, int quantidade);
int* carregar_dados(const char *nome_arquivo, int *tamanho);
int busca_sequencial(int *v, int tamanho, int alvo);
int busca_binaria(int *v, int tamanho, int alvo);

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

        printf("processando bubble %s\n", nomes[a]);
            copiar_vetor(temp, original, tamanho);
            salvar_csv("bubble_sort", nomes[a], medir_tempo(bubble_sort, temp, tamanho, "bubble_sort"));
        
            copiar_vetor(temp, original, tamanho);
            salvar_csv("bubble_sort_otimizado", nomes[a], medir_tempo(bubble_sort_otimizado, temp, tamanho, "bubble_sort_otimizado"));

        printf("processando insertion %s\n", nomes[a]);
            copiar_vetor(temp, original, tamanho);
            salvar_csv("insertion_sort", nomes[a], medir_tempo(insertion_sort, temp, tamanho, "insertion_sort"));

            copiar_vetor(temp, original, tamanho);
            salvar_csv("insertion_sort_otimizado", nomes[a], medir_tempo(insertion_sort_otimizado, temp, tamanho, "insertion_sort_otimizado"));

        printf("%s pronto!\n\n", nomes[a]);

        free(temp);
        free(original);
    }

    int tamanho;
    int *v = carregar_dados("dados/ordenado_bubble.bin", &tamanho);
    int alvo = 123;

    int pos = busca_binaria(v, tamanho, alvo);
    if (pos != -1)
        printf("Encontrado na posicao %d\n", pos);
    else
        printf("Nao encontrado\n");

    free(v);

    return 0;
}





// gcc codigo/main.c codigo/ordenacao.c codigo/busca.c codigo/gerador_dados.c -o programa