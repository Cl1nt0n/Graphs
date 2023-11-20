#include <iostream>
#include <list>
#define size 6

using namespace std;

void dijkstra_algorithm(int* passed_peaks, 
	int* min_weight, 
	int matrix[][size], 
	int result_array[][size]
);

void kruskal_algorithm(int matrix[][size]);
