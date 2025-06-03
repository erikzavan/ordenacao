EXEC = programa
SRCS = codigo/main.c \
       codigo/ordenacao.c \
       codigo/busca.c \
       codigo/gerador_dados.c \
       codigo/app_utils.c
CC = gcc
CFLAGS = -Wall -O2

all: $(EXEC)
$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRCS)

clean:
	rm -f $(EXEC) tempos.csv desempenho.csv *.o