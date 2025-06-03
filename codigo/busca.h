#ifndef BUSCA_H
#define BUSCA_H

int* carregar_dados(const char *nome_arquivo, int *tamanho);
int busca_sequencial(int *v, int tamanho, int alvo, long* comp);
int busca_binaria(int *v, int tamanho, int alvo, long* comp);
void salvar_vetor(const char* nome_arquivo, int* v, int tamanho);

#endif