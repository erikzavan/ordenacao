#include <time.h>


// para medir o tempo

clock_t inicio = clock();
// chama a função de ordenação
clock_t fim = clock();

double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("Tempo de execução: %.2f segundos\n", tempo);

// SelectionSort
// BubbleSort (padrão) 
// BubbleSort (otimizado)
// InsertionSort (padrão)
// InsertionSort (otimizado)

int main{
  return 0;
}
