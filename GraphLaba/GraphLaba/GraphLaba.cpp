#include <iostream>
#include "GraphLaba.h"
#define size 6

using namespace std;

void DijkstraAlgorithm(int* passed_peaks, int* min_weight, int  matrix[][size], int result_array[][size]);

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

	DijkstraAlgorithm(passed_peaks, min_weight, matrix, result_array);

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

void DijkstraAlgorithm(int* passed_peaks, int* min_weight, int  matrix[][size], int result_array[][size])
{
	int min_index, min;
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			*(min_weight + i) = INT_MAX;
			*(passed_peaks + i) = 1;
		}
		*(min_weight + j) = 0;

		do
		{
			min_index = INT_MAX;
			min = INT_MAX;//минимальный вес не пройденной вершины
			for (int i = 0; i < size; i++)
			{ // Если вершину ещё не обошли и вес меньше min
				if ((passed_peaks[i] == 1) && (min_weight[i] < min))
				{
					min = min_weight[i];
					min_index = i;
				}
			}

			// Добавляем найденный минимальный вес
			// к текущему весу вершины
			// и сравниваем с текущим минимальным весом вершины
			if (min_index != INT_MAX)
			{
				for (int i = 0; i < size; i++)
				{
					if (matrix[min_index][i] > 0)
					{
						int temp = min + matrix[min_index][i];
						if (temp < min_weight[i])
						{
							min_weight[i] = temp;
						}
					}
				}
				passed_peaks[min_index] = 0;
			}
		} while (min_index < INT_MAX);

		for (int i = 0; i < size; i++)
			result_array[j][i] = min_weight[i];
	}
}
