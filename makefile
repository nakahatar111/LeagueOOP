all: graph

graph: graph.o
	g++ graph.o -o graph

graph.o: graph.cpp Info.h Node.h
	g++ -c graph.cpp

