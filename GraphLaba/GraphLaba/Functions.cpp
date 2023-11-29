#include "Headers.h"


void print_matrix(int matrix[][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (matrix[i][j] == NO_WAY)
			{
				cout << "-" << '\t';
				continue;
			}
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
}

void print_sequestion(int* sequestion, int size)
{
	for (int i = 0; i < size; i++)
		cout << *(sequestion + i) << ' ';
	cout << endl;
}

void dijkstra_algorithm(int matrix[][SIZE], int* shortest, int* previous, int peak)
{
	//Инициализация переменных
	int* passed_peaks = new int[SIZE]; //мн-во с пройденными вершинами
	int min;

	//заполняем passed_peaks нулями
	for (int i = 0; i < SIZE; i++)
		*(passed_peaks + i) = 0;

	//заполняем shortest и previous
	for (int i = 0; i < SIZE; i++)
	{
		*(shortest + i) = NO_WAY;
		*(previous + i) = -1;
	}
	*(shortest) = 0;
	*(previous) = -1;

	cout << "Промежуточные результаты: " << endl;
	for (int i = 0; i < SIZE; i++) {
		min = -1;
		for (int j = 0; j < SIZE; j++)
			if (*(passed_peaks + j) == 0 && ((min == -1) || (*(shortest + j) < *(shortest + min))))
				min = j;
		*(passed_peaks + min) = 1;

		for (int j = 0; j < SIZE; j++)
			relax(matrix, shortest, previous, min, j);

		print_shortest(peak, shortest, previous);
	}

	for (int i = 0; i < SIZE; i++)
	{
		int x = i;

		while (x != -1)
		{
			cout << x + 1 << " <= ";
			x = *(previous + x);
		}

		cout << endl;
	}

	delete[] passed_peaks;//очищение выделенной памяти
}

void print_shortest(int peak, int* shortest, int* previous)
{
	for (int j = 0; j < SIZE; j++)
	{
		if (j == peak)
			continue;
		if (*(shortest + j) == NO_WAY)
		{
			cout << "Нет пути в вершину " << j + 1 << endl;
		}
		else
		{
			cout << "Кратчайшее расстояние в вершину " << j + 1 << " - " << *(shortest + j) << endl;
			cout << "Предыдущая вершина " << *(previous + j) + 1 << endl;
		}
	}
	cout << endl;
}

void relax(int matrix[][SIZE], int* shortest, int* previous, int a, int b)
{
	if (*(*(matrix + a) + b) != NO_WAY && *(shortest + a) != NO_WAY)
	{
		if (*(shortest + a) + *(*(matrix + a) + b) < *(shortest + b)) //выбираем минимальный путь
		{
			*(shortest + b) = *(shortest + a) + *(*(matrix + a) + b);
			*(previous + b) = a;
		}
	}
}

void bellman_ford_algorithm(int matrix[][SIZE], int* shortest, int* previous, int peak)
{
	//заполняем shortest и pred
	for (int i = 0; i < SIZE; i++)
	{
		*(shortest + i) = NO_WAY;
		*(previous + i) = -1;
	}
	*(shortest) = 0;
	*(previous) = -1;

	cout << "Промежуточные результаты:" << endl;
	for (int i = 0; i < SIZE - 1; i++)
	{
		//вызываем релакс для каждого ребра size-1 раз
		for (int j = 0; j < SIZE; j++)
			for (int k = 0; k < SIZE; k++)
				if (*(*(matrix + j) + k) != NO_WAY)
					relax(matrix, shortest, previous, j, k);
		//печать shortest и pred
		print_shortest(peak, shortest, previous);
	}

	//Процедура поиска отрицательного цикла
	bool isCycle = negative_cycle(matrix, shortest, previous);

	if (isCycle)
		return;

	for (int i = 0; i < SIZE; i++)
	{
		int x = i;

		while (x != -1)
		{
			cout << x + 1 << " <= ";
			x = *(previous + x);
		}

		cout << endl;
	}
}

void floyd_warshall_algorithm(int matrix[][SIZE], int shortest_floyd_warshall[][SIZE], int previous_floyd_warshall[][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			//копируем матрицу смежности в shortest floyd warshall
			shortest_floyd_warshall[i][j] = matrix[i][j];
			//заполняем матрицу previous floyd warshall
			if (matrix[i][j] != NO_WAY && i != j)
				previous_floyd_warshall[i][j] = i;
			else
				previous_floyd_warshall[i][j] = -1;
		}
	}

	//bool isCycle;
	cout << "Промежуточные результаты:" << endl;

	//поиск кратчайшего пути из i в j через k
	for (int k = 0; k < SIZE; k++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (shortest_floyd_warshall[i][k] != NO_WAY && shortest_floyd_warshall[k][j] != NO_WAY && i != j)
				{
					if (shortest_floyd_warshall[i][k] + shortest_floyd_warshall[k][j] < shortest_floyd_warshall[i][j])
					{
						shortest_floyd_warshall[i][j] = shortest_floyd_warshall[i][k] + shortest_floyd_warshall[k][j];
						previous_floyd_warshall[i][j] = previous_floyd_warshall[k][j];
					}
				}
			}
		}

		cout << "\nk = " << k << endl;
		cout << "Кратчайшее расстояние в вершину: " << endl;
		print_matrix(shortest_floyd_warshall);
		cout << endl;
		cout << "Предыдущие вершины: " << endl;
		print_matrix(previous_floyd_warshall);
		cout << endl;
	}

	/*isCycle = negative_cycle(matrix, shortest_floyd_warshall[k], previous_floyd_warshall[k]);

	if (isCycle)
		return;*/

	//Печать путей до вершин для каждой начальной вершины
	for (int j = 0; j < SIZE; j++)
	{
		cout << "Вершина: " << j << endl;
		for (int i = 0; i < SIZE; i++)
		{
			int x = i;

			while (x != -1)
			{
				cout << x + 1 << " <= "; 
				x = previous_floyd_warshall[j][x];
			}

			cout << endl;
		}
		cout << endl;
	}
}

//Функция поиска отрицательного цикла
bool negative_cycle(int matrix[][SIZE], int* shortest, int* previous)
{
	//Инициализация переменных
	int cycle_start = -1;//Флаг нахождения отрицательного цикла и индекс его начала

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			//Если суммарный путь < 0
			if (matrix[i][j] != NO_WAY && (matrix[i][j] + shortest[i] < shortest[j]) && shortest[j] != NO_WAY && shortest[i] != NO_WAY)
			{
				cycle_start = i; //запоминаем начало отрицательного цикла
				break;
			}
		}

		if (cycle_start != -1)
			break; //если нашли отрицательный цикл
	}

	//Не нашли отрицательный цикл
	if (cycle_start == -1)
	{
		cout << "\nОтрицательного цикла нет" << endl;
	}
	else//Иначе выводим вершины самого сильного отрицательного цикла
	{
		cout << "\nНайден отрицательный цикл: " << endl << "<= ";
		int x = cycle_start;
		do
		{
			cout << x + 1 << " <= "; //вывод вершин цикла
			x = *(previous + x);
		} while (x != cycle_start); //пока не вернулись в вершину начала цикла
		cout << endl;

		return true;
	}
	cout << endl << endl;

	return false;
}

void prim_algorithm(int matrix[][SIZE])
{
	//Инициализация переменных
	bool* passed_peaks = new bool[SIZE]; //вершины, содержащиеся в осточного дереве
	for (int i = 0; i < SIZE; i++)
		passed_peaks[i] = false;
	int min; //минимум
	int from, to; //начальная вершина, конечная вершина
	passed_peaks[0] = true; //разрешаем просмотр рёбер первой вершины
	int weight = 0; //минимальный вес остовного дерева

	for (int i = 0; i < SIZE - 1; i++)
	{
		min = NO_WAY;
		from = 0;
		to = 0;

		for (int j = 0; j < SIZE; j++)
		{
			if (passed_peaks[j])//если разрешён просмотр рёбер вершины
			{
				for (int k = 0; k < SIZE; k++)
				{
					if (!passed_peaks[k] && matrix[j][k] != NO_WAY) //если вершина не содержится в остовном дереве и в нее есть путь
					{
						if (min > matrix[j][k])
						{
							min = matrix[j][k];
							from = j;
							to = k;
						}
					}
				}
			}
		}

		cout << from + 1 << " - " << to + 1 << " : " << matrix[from][to] << endl;
		passed_peaks[to] = true;
		weight += matrix[from][to]; //увеличиваем вес остовного дерева
	}

	cout << "Минимальный вес дерева: " << weight << endl;
	delete[] passed_peaks;//очищение выделенной памяти
}

void kruskal_algorithm(int matrix[][SIZE])
{
	//Инициализация переменных
	//выделение памяти под Массив рёбер графа размера size^2
	Edge* edges = new Edge[SIZE * SIZE]{ NULL };
	int k = 0;//количество ребер
	int* flags = new int[SIZE]; //выделение памяти под Массив множеств

	//Заполняем массив рёбрами из матрицы смежности
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (matrix[i][j] != NO_WAY)
			{
				edges[k].weight = matrix[i][j];
				edges[k].from = i;
				edges[k].to = j;
				k++;
			}
		}
	}

	//Сортируем массив рёбер по возрастанию
	sort(edges, 0, k);

	int weight = 0; //вес минимального остовного дерева

	//Каждая вершина изначально принадлежит своему множеству
	for (int i = 0; i < SIZE; i++)
		*(flags + i) = i;

	//цикл по всем рёбрам
	for (int i = 0; i < k; i++)
	{
		if (flags[edges[i].from] != flags[edges[i].to])
		{   // Проверка принадлежности вершин разным множествам
			int oldflag = flags[edges[i].to];

			for (int j = 0; j < SIZE; j++)
				if (flags[j] == oldflag)
					flags[j] = flags[edges[i].from];

			weight += edges[i].weight; //увеличиваем вес остовного дерева
			cout << edges[i].from + 1 << " - " << edges[i].to + 1 << " : " << edges[i].weight << endl;
		}
	}

	cout << "Минимальный вес связующего дерева:";
	cout << weight << endl;

	//Очищение выделенной памяти
	delete[] flags;
	delete[] edges;
}

void sort(Edge* sequestion, int start, int end)
{
	if (start >= end)
		return;

	int i = start;//начало массива
	int j = end;//конец массива
	int pivot = sequestion[(start + end) / 2].weight;//средний элемент массива

	while (i <= j)
	{
		while (sequestion[i].weight < pivot)
			i++;
		while (sequestion[j].weight > pivot)
			j--;
		if (i <= j)
		{
			swap(*(sequestion + i), *(sequestion + j));
			i++;
			j--;
		}
	}

	sort(sequestion, start, j);
	sort(sequestion, i, end);
}


