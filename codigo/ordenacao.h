
#ifndef ORDENACAO_H
#define ORDENACAO_H

void selection_sort(int v[], int n, const char* nome);
void bubble_sort(int v[], int n, const char* nome);
void bubble_sort_otimizado(int v[], int n, const char* nome);
void insertion_sort(int v[], int n, const char* nome);
void insertion_sort_otimizado(int v[], int n, const char* nome);
double medir_tempo(void (*func)(int*, int, const char*), int* v, int n, const char* nome);
void processar_ordenacao(const char* nome_algoritmo, void (*alg)(int*, int, const char*), int* original, int tamanho, const char* nome_entrada);
void ordenar_todos(const char* arquivo, const char* nome_entrada);

#endif