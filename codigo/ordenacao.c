#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// SelectionSort
void SelectionSort(int v[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int menorIndice = i;
        for(int indiceSeguinte = i+1; indiceSeguinte < n; indiceSeguinte++)
        {
            if (v[indiceSeguinte] > v[menorIndice]) continue;
            menorIndice = indiceSeguinte;
        }

        int aux = v[i];
        v[i] = v[menorIndice];
        v[menorIndice] = aux;
    }
}

// BubbleSort (padrao) 
void bubble_sort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                trocar(&v[j], &v[j + 1]);
            }
        }
    }
}

// BubbleSort (otimizado)
void bubble_sort_otimizado(int v[], int n) {
    int trocou;
    for (int i = 0; i < n - 1; i++) {
        trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                trocar(&v[j], &v[j + 1]);
                trocou = 1;
            }
        }
        if (trocou == 0)
            break;
    }
}

// InsertionSort (padrao)
void insertion_sort(int v[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int atual = v[i];
        int anterior = i - 1;
        
        while ((anterior >= 0) && (v[anterior] > atual))
        {
            int proximo = anterior + 1;
            v[proximo] = v[anterior];
            anterior--;
        }

        v[anterior + 1] = atual;
    }
}

// InsertionSort (otimizado)
void insertion_sort_otimizado(int v[], int n)
{
    for (int i = 1; i < n; i++) {
        int atual = v[i];
        int j = i - 1;
        
        // Move os elementos maiores que 'atual' uma posição à frente
        while (j >= 0 && v[j] > atual) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = atual;
    }
}

// para medir o tempo

clock_t inicio = clock();
// chama a funcao de ordenacao
clock_t fim = clock();

double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("Tempo de execução: %.2f segundos\n", tempo);
