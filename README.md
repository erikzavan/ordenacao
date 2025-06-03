# Projeto: Ordenação e Busca em C

Este projeto em linguagem C permite gerar arquivos binários com números aleatórios, ordená-los com diferentes algoritmos e realizar buscas sobre os vetores ordenados. O tempo de execução de cada algoritmo também é registrado em um arquivo `.csv`.

## Funcionalidades

- Geração de dados aleatórios em arquivos binários
- Ordenação com os algoritmos:
  - `selection_sort`
  - `bubble_sort`
  - `bubble_sort_otimizado`
  - `insertion_sort`
  - `insertion_sort_otimizado`
- Registro de tempo em `tempos.csv`
- Salvamento de vetores ordenados em arquivos
- Busca sequencial ou binária nos arquivos gerados

---

## Estrutura do Projeto

```
codigo/
├── main.c               → ponto de entrada do programa
├── ordenacao.c/.h       → funções de ordenação e medição de tempo
├── busca.c/.h           → buscas e leitura de arquivos binários
├── gerador_dados.c/.h   → geração dos dados
├── app_utils.c/.h       → funções auxiliares (menu, CSV, etc.)
├── Makefile             → automatiza a compilação
```

---

## Como Compilar

### Usando Makefile:

```bash
make
```

Gera o executável:

```
./programa (ou programa.exe no Windows)
```

### Manualmente:

```bash
gcc codigo/main.c codigo/ordenacao.c codigo/busca.c codigo/gerador_dados.c codigo/app_utils.c -o programa
```

---

## ▶Como Executar

```bash
./programa
```

No Windows:

```bash
programa.exe
```

---

## Como Usar

### 1. Geração dos Arquivos

Ao iniciar o programa:

```
quer gerar arquivos binarios? s/n
>
```

Digite `s` para gerar:

- `dados/pequeno.bin` (40.000 valores)
- `dados/medio.bin` (100.000 valores)
- `dados/grande.bin` (250.000 valores)

---

### 2. Ordenação

Cada arquivo é ordenado com os 5 algoritmos. Para cada um:

- Tempo registrado em `tempos.csv`
- Vetor ordenado salvo como:
  ```
  dados/ordenado_selection_pequeno.bin
  dados/ordenado_bubble_medio.bin
  ...
  ```

---

### 3. Menu de Busca

Você poderá escolher:

- Tipo de busca: `sequencial` ou `binaria`
- Algoritmo de ordenação: `selection`, `bubble`, etc.
- Tamanho do vetor: `pequeno`, `medio`, `grande`
- Valor a buscar (ex: 123)

A saída indica se o valor foi encontrado e em qual posição.

---

## Saída Gerada

- `tempos.csv` — tempos por algoritmo e tamanho
- `dados/*.bin` — arquivos binários com dados originais e ordenados

---