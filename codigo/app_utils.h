#ifndef APP_UTILS_H
#define APP_UTILS_H

void copiar_vetor(int* destino, int* origem, int tamanho);
void salvar_csv(const char *algoritmo, const char* nome_arquivo, double tempo, long comparacoes, long trocas);
void limpar_csv();
void menu_busca();

#endif