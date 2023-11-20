#include "Headers.h"

int main()
{
	//Подключаем русский язык
	setlocale(LC_ALL, "ru");

	//Матрица смежности
	int matrix[size][size] =
	{
		{0,   7,  9, -1, -1, 14},
		{7,   0, 10, 15, -1, -1},
		{9,  10,  0, 11, -1,  2},
		{-1, 15, 11,  0,  6, -1},
		{-1, -1, -1,  6,  0,  9},
		{14, -1,  2, -1,  9,  0}
	};

	int result_array[size][size];
	//Массив минимальных расстояний до вершин
	int* min_weight = new int[size];
	//Массив пройденных вершин
	int* passed_peaks = new int[size];

	cout << "Матрица смежности графа:" << endl;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;

	dijkstra_algorithm(passed_peaks, min_weight, matrix, result_array);

	for (int i = 0; i < size; i++)
	{
		cout << "Кратчайшие расстояния от " << i + 1 << " вершины" << endl;
		for (int j = 0; j < size; j++)
		{
			cout << j + 1 << ':' << result_array[i][j] << endl;
		}
	}

	delete[] min_weight;
	delete[] passed_peaks;
}