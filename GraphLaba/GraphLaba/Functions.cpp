#include "Headers.h"

void dijkstra_algorithm(int* passed_peaks, int* min_weight, int  matrix[][size], int result_array[][size])
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

void kruskal_algorithm(int matrix[][size])
{
	int* peaks = new int[size];
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			
		}
	}
}

