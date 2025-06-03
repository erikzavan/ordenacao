#ifndef APP_UTILS_H
#define APP_UTILS_H

void copiar_vetor(int* destino, int* origem, int tamanho);
void salvar_csv(const char *algoritmo, const char* nome_arquivo, double tempo);
void processar_ordenacao(const char* nome_algoritmo, void (*alg)(int*, int, const char*), int* original, int tamanho, const char* nome_entrada);
void ordenar_todos(const char* arquivo, const char* nome_entrada);
void gerador_arquivos(int pequeno, int medio, int grande);
void menu_busca();
void limpar_csv();

#endif
