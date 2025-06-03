#include <stdio.h>
#include "app_utils.h"

int main() {
    int pequeno = 40000, medio = 100000, grande = 250000;

    limpar_csv();
    gerador_arquivos(pequeno, medio, grande);

    ordenar_todos("dados/pequeno.bin", "pequeno");
    ordenar_todos("dados/medio.bin", "medio");
    ordenar_todos("dados/grande.bin", "grande");

    menu_busca();
    return 0;
}

// gcc codigo/main.c codigo/ordenacao.c codigo/busca.c codigo/gerador_dados.c codigo/app_utils.c -o programa
