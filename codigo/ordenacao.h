#ifndef ORDENACAO_H
#define ORDENACAO_H

void selection_sort(int v[], int n, const char* nome, unsigned long long* comp, unsigned long long* troc);
void bubble_sort(int v[], int n, const char* nome, unsigned long long* comp, unsigned long long* troc);
void bubble_sort_otimizado(int v[], int n, const char* nome, unsigned long long* comp, unsigned long long* troc);
void insertion_sort(int v[], int n, const char* nome, unsigned long long* comp, unsigned long long* troc);
void insertion_sort_otimizado(int v[], int n, const char* nome, unsigned long long* comp, unsigned long long* troc);

double medir_tempo(void (*func)(int*, int, const char*, unsigned long long*, unsigned long long*),
                   int* v, int n, const char* nome,
                   unsigned long long* comp, unsigned long long* troc);

void processar_ordenacao(const char* nome_algoritmo,
                         void (*alg)(int*, int, const char*, unsigned long long*, unsigned long long*),
                         int* original, int tamanho,
                         const char* nome_entrada);

void ordenar_todos(const char* arquivo, const char* nome_entrada);

#endif
