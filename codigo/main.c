#include <stdio.h>
#include <stdlib.h>

int* carregar_dados(const char *nome_arquivo, int *tamanho);
int busca_sequencial(int *v, int tamanho, int alvo);
int busca_binaria(int *v, int tamanho, int alvo);

int main() {
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
