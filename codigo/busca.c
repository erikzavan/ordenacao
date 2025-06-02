
#include <stdio.h>
#include <stdlib.h>

int* carregar_dados(const char *nome_arquivo, int *tamanho) {
    //open
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) {
        exit(EXIT_FAILURE);
    }

    //size
    fseek(arquivo, 0, SEEK_END);
    long tamanho_bytes = ftell(arquivo);
    rewind(arquivo);

    //alloc
    *tamanho = tamanho_bytes / sizeof(int);
    int *dados = (int *)malloc(tamanho_bytes);
    if (!dados) {
        exit(EXIT_FAILURE);
    }

    //read
    fread(dados, sizeof(int), *tamanho, arquivo);
    fclose(arquivo);

    return dados;
}

int busca_sequencial(int *v, int tamanho, int alvo) {
    for (int i = 0; i < tamanho; i++) {
        if (v[i] == alvo)
            return i;
    }
    return -1;
}

int busca_binaria(int *v, int tamanho, int alvo) {
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (v[meio] == alvo)
            return meio;
        else if (v[meio] < alvo)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}
