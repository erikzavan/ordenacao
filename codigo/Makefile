EXEC = programa
SRCS = codigo/main.c codigo/ordenacao.c codigo/busca.c codigo/gerador_dados.c
CFLAGS = -Wall - O2
CC = gcc

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRCS)

clean:
	rm -f $(EXEC) tempos.csv *.o