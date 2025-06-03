#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerar_arquivo(const char* nome, int quantidade) {
	FILE *file = fopen(nome, "wb");
		if (!file) {
    		perror("Erro ao abrir arquivo");
    		exit(1);
	}

	srand(time(NULL));
	for (int i = 0; i < quantidade; i++) {
    		int numero = rand() % 10000;  // números entre 0 e 9999
    		fwrite(&numero, sizeof(int), 1, file);
	}

	fclose(file);
}

void gerador_arquivos(int pequeno, int medio, int grande) {
    char resposta;
    printf("quer gerar arquivos binarios? s/n\n> ");
    char linha[10];
    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, " %c", &resposta);

    if (resposta == 's' || resposta == 'S') {
        gerar_arquivo("dados/pequeno.bin", pequeno);
        gerar_arquivo("dados/medio.bin", medio);
        gerar_arquivo("dados/grande.bin", grande);
        printf("arquivos gerados!\n");
    }
}