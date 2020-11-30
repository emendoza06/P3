all: statSem 

statSem: 
	gcc -Wall tree.c node.c token.c main.c parser.c scanner.c testtree.c staticsemantics.c -o statSem

clean:
	rm statSem
