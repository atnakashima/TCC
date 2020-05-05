CC     = gcc
CFLAGS = -g -Wall -ansi -pedantic -Wno-unused-result
OBJS   = main.o digraph.o bellman.o dijkstra.o prim.o kruskal.o \
	 union.o queue.o util.o inputlib.o io.o validacao.o \
	 goemans-williamson.o 
RM     = rm
#------------------------------------------------

# chama o linker
oticomb:  $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o oticomb
       
main.o: main.c digraph.h bellman.h dijkstra.h util.h
	$(CC) $(CFLAGS) -c main.c 

digraph.o: digraph.c digraph.h item.h
	$(CC) $(CFLAGS) -c digraph.c 

# Algoritmos 

bellman.o: bellman.c bellman.h digraph.h
	$(CC) $(CFLAGS) -c bellman.c 

dijkstra.o: dijkstra.c dijkstra.h queue.h 
	$(CC) $(CFLAGS) -c dijkstra.c 

prim.o: prim.c prim.h
	$(CC) $(CFLAGS) -c prim.c 

kruskal.o: kruskal.c kruskal.h
	$(CC) $(CFLAGS) -c kruskal.c 

goemans-williamson.o: goemans-williamson.c goemans-williamson.h
	$(CC) $(CFLAGS) -c goemans-williamson.c
  
# Estruturas de Dados 

union.o: union.c union.h
	$(CC) $(CFLAGS) -c union.c

queue.o: queue.c queue.h item.h
	$(CC) $(CFLAGS) -c queue.c 

# Geral
util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c 

# I/O
inputlib.o: inputlib.c inputlib.h
	$(CC) $(CFLAGS) -c inputlib.c 

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c 

# I/O
validacao.o: validacao.c validacao.h
	$(CC) $(CFLAGS) -c validacao.c 

# Limpa
clean: 
	rm -f *.o *~
