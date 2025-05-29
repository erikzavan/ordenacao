#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pequeno = 10000; // 1 segundo
int medio = 500000; // 30 segundos
int grande = 4000000; // 3 minutos (testar tempo de tds)

void gerar_arquivo(const char* nome, int quantidade) {
	FILE *arquivo = fopen(nome, "wb");
	if (!arquivo) {
    	perror("Erro ao abrir arquivo");
    	exit(1);
	}

	srand(time(NULL));
	for (int i = 0; i < quantidade; i++) {
    	int numero = rand() % 100000;  // números entre 0 e 99999
    	fwrite(&numero, sizeof(int), 1, arquivo);
	}

	fclose(arquivo);
}

int main() {
	gerar_arquivo("dados/pequeno.bin", pequeno);
	gerar_arquivo("dados/medio.bin", medio);
	gerar_arquivo("dados/grande.bin", grande);
	return 0;
}

