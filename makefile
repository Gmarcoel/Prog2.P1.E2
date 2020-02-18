(CFLAGS) = "-Wall -ansi -pedantic"
all: p1_e2

p1_e2: p1_e2.o node.o graph.o
	gcc p1_e2.o node.o graph.o -o p1_e2

node.o: node.c
	gcc $(CFLAGS) -c node.c

p1_e1.o: p1_e1.c
	gcc $(CFLAGS) -c p1_e1.c	

graph.o: graph.c
	gcc $(CFLAGS) -c graph.c

clean:
	rm *.o p1_e2
