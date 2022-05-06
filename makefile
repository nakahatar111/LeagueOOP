all: graph

graph: graph.o hash.o Node.o
	g++ graph.o hash.o Node.o -o graph

hash.o: hash.cpp hash.h Node.h Info.h
	g++ -c hash.cpp

graph.o: graph.cpp Info.h Node.h hash.h
	g++ -c graph.cpp

Node.o: Node.cpp Node.h hash.h Info.h
	g++ -c Node.cpp