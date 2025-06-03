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