#include <stdio.h>
#include <stdlib.h>

int* carregar_dados(const char *nome_arquivo, int *tamanho) {
    //open
    FILE *file = fopen(nome_arquivo, "rb");
    if (!file) {
        exit(EXIT_FAILURE);
    }

    //size
    fseek(file, 0, SEEK_END);
    long tamanho_bytes = ftell(file);
    rewind(file);

    //alloc
    *tamanho = tamanho_bytes / sizeof(int);
    int *dados = (int *)malloc(tamanho_bytes);
    if (!dados) {
        exit(EXIT_FAILURE);
    }

    //read
    fread(dados, sizeof(int), *tamanho, file);
    fclose(file);

    return dados;
}

int busca_sequencial(int *v, int tamanho, int alvo, long* comp) {
    for (int i = 0; i < tamanho; i++) {
        (*comp)++;
        if (v[i] == alvo)
            return i;
    }
    return -1;
}

int busca_binaria(int *v, int tamanho, int alvo, long* comp) {
    int ini = 0, fim = tamanho - 1;
    while (ini <= fim) {
        (*comp)++;
        int meio = (ini + fim) / 2;
        if (v[meio] == alvo)
            return meio;
        else if (alvo < v[meio])
            fim = meio - 1;
        else
            ini = meio + 1;
    }
    return -1;
}

void salvar_vetor(const char* nome_arquivo, int* v, int tamanho){
    FILE* file = fopen(nome_arquivo, "wb");
    if (!file) {
        perror("erro abrir arquivo salvar vetor");
        exit(EXIT_FAILURE);
    }

    fwrite(v, sizeof(int), tamanho, file);
    fclose(file);
}
