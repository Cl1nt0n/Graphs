#include <iostream>
#include <list>

#define SIZE 6
#define NO_WAY INT_MAX

struct Edge
{
	int weight, from, to; //вес ребра и его вершины
};

using namespace std;

void dijkstra_algorithm(int matrix[][SIZE], 
	int* shortest, 
	int* previous, 
	int peak
);

void bellman_ford_algorithm(int matrix[][SIZE],
	int* shortest,
	int* previous,
	int peak
);

void floyd_warshall_algorithm(int matrix[][SIZE],
	int shortest_floyd_warshall[][SIZE],
	int previous_floyd_warshall[][SIZE]
);

void prim_algorithm(int matrix[][SIZE]
);

void kruskal_algorithm(int matrix[][SIZE]);

void print_matrix(int matrix[][SIZE]);

void print_shortest(int peak, int* shortest, int* previous);

void relax(int matrix[][SIZE], int* shortest, int* previous, int a, int b);

void NegativeCycle(int matrix[][SIZE], int* shortest, int* previous);

void sort(Edge* array, int size);


