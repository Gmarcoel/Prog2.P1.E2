all: p1_e1

p1_e1: p1_e1.o node.o graph.o
	gcc p1_e1.o node.o graph.o -o p1_e1

node.o: node.c
	gcc -c node.c

p1_e1.o: p1_e1.c
	gcc -c p1_e1.c	

graph.o: graph.c
	gcc -c graph.c

clean:
	rm *.o p1_e1
