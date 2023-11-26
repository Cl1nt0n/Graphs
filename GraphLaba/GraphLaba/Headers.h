#include <iostream>
#include <list>

#define SIZE 10
#define NO_WAY INT_MAX

//ребро
struct Edge
{
	int weight; //вес ребра
	int	from; //откуда
	int to; //куда
};

using namespace std;

//алгоритм Дейкстры
void dijkstra_algorithm(int matrix[][SIZE], //матрица смежности
	int* shortest, //массив с кратчайшими расстояниями
	int* previous, //массив с предыдущими вершинами
	int peak //вершина
);

//алгоритм Беллмана-Форда
void bellman_ford_algorithm(int matrix[][SIZE], //матрица смежности
	int* shortest, //массив с кратчайшими расстояниями
	int* previous, //массив с предыдущими вершинами
	int peak //вершина
);

//алгоритм Флойда-Уоршелла
void floyd_warshall_algorithm(int matrix[][SIZE], //матрица смежности
	int shortest_floyd_warshall[][SIZE], //матрица с кратчайшими расстояниями
	int previous_floyd_warshall[][SIZE] //матрица с предыдущими вершинами
);

//алгоритм Прима
void prim_algorithm(int matrix[][SIZE] //матрица смежности
);

//алгоритм Краскала
void kruskal_algorithm(int matrix[][SIZE] //матрица смежности
);

//печать матрицы
void print_matrix(int matrix[][SIZE] //матрица смежности
);

//печать 
void print_shortest(int peak, //вершина
	int* shortest, //массив с кратчайшими расстояниями
	int* previous  //массив с предыдущими вершинами
);

//функция relax
void relax(int matrix[][SIZE], //матрица смежности
	int* shortest, //массив с кратчайшими расстояниями
	int* previous, //массив с предыдущими вершинами
	int a, //индекс первой вершины
	int b //индекс второй вершины
);

//функция посика отрицательного цикла
bool negative_cycle(int matrix[][SIZE], //матрица смежности
	int* shortest, //массив с кратчайшими расстояниями
	int* previous  //массив с предыдущими вершинами
);

//сортировка
void sort(Edge* array, //массив ребер
	int size 
);


