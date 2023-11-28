#include "Headers.h"

int main()
{
	//Подключаем русский язык
	setlocale(LC_ALL, "ru");

	//массив с кратчайшими расстояниями
	int* shortest = new int[SIZE];
	//массив с предыдущими вершинами
	int* previous = new int[SIZE];
	//массивы для алгоритма флойда-уоршелла
	int shortest_floyd_warshall[SIZE][SIZE];
	int previous_floyd_warshall[SIZE][SIZE];
	//вершина
	int peak;
	//тип матрицы 
	int matrix_number;

	////Ориентированный граф без отрицательных весов
	//matrix_number = 1;
	//int adjacency_matrix[SIZE][SIZE] =
	//{
	//	{NO_WAY, 10,     NO_WAY, NO_WAY, 8,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, 3,      7,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, 3,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, 3     },
	//	{NO_WAY, NO_WAY, 6,      NO_WAY, NO_WAY, NO_WAY, 20,     5,      NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, 9,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, 18,     NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, 14,     NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, 16,     NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//};

	////Ориентированный граф отрицательными весами без цикла
	//matrix_number = 2;
	//int adjacency_matrix[SIZE][SIZE] =
	//{
	//	{NO_WAY, 10,     NO_WAY, NO_WAY, 8,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, 3,      7,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, 3,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, 3     },
	//	{NO_WAY, NO_WAY, 6,      NO_WAY, NO_WAY, NO_WAY, 20,     5,      NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, 9,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, -18,     NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, 14,     NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, 16,     NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//};

	////Ориентированный граф с отрицательными весами с циклом
	//matrix_number = 3;
	//int adjacency_matrix[SIZE][SIZE] =
	//{
	//	{NO_WAY, 10,     NO_WAY, NO_WAY, 8,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, 3,      7,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, 3,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, -3     },
	//	{NO_WAY, NO_WAY, 6,      NO_WAY, NO_WAY, NO_WAY, 20,     5,      NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, 9,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, 18,     NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, 14,     NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, -16,    NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//};

	//Неориентированный граф без отрицательных весов
	matrix_number = 4;
	int adjacency_matrix[SIZE][SIZE] =
	{
		{NO_WAY, 10,     NO_WAY, NO_WAY, 8,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
		{10,     NO_WAY, 3,      7,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
		{NO_WAY, 3,      NO_WAY, 3,      6,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
		{NO_WAY, 7,      3,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, 3     },
		{8,      NO_WAY, 6,      NO_WAY, NO_WAY, 9,      20,     5,      NO_WAY, NO_WAY},
		{NO_WAY, NO_WAY, NO_WAY, NO_WAY, 9,      NO_WAY, 18,     NO_WAY, NO_WAY, 16    },
		{NO_WAY, NO_WAY, NO_WAY, NO_WAY, 20,     18,     NO_WAY, NO_WAY, NO_WAY, NO_WAY},
		{NO_WAY, NO_WAY, NO_WAY, NO_WAY, 5,      NO_WAY, NO_WAY, NO_WAY, 14,     NO_WAY},
		{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, 14,     NO_WAY, NO_WAY},
		{NO_WAY, NO_WAY, NO_WAY, 3,      NO_WAY, 16,     NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	};

	////Неориентированный граф с отрицательными весами
	//matrix_number = 5;
	//int adjacency_matrix[SIZE][SIZE] =
	//{
	//	{NO_WAY, -10,     NO_WAY, NO_WAY, 8,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{10,     NO_WAY, 3,      7,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, 3,      NO_WAY, 3,      6,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, 7,      3,      NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, 3     },
	//	{8,      NO_WAY, 6,      NO_WAY, NO_WAY, 9,      20,     5,      NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, 9,      NO_WAY, 18,     NO_WAY, NO_WAY, 16    },
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, 20,     18,     NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, 5,      NO_WAY, NO_WAY, NO_WAY, 14,     NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, NO_WAY, 14,     NO_WAY, NO_WAY},
	//	{NO_WAY, NO_WAY, NO_WAY, 3,      NO_WAY, -16,     NO_WAY, NO_WAY, NO_WAY, NO_WAY},
	//};

	int result_array[SIZE][SIZE];
	//Массив минимальных расстояний до вершин
	int* min_weight = new int[SIZE];
	int numb;

	cout << "Матрица смежности графа " << matrix_number << ": " << endl;

	print_matrix(adjacency_matrix);

	while (1)
	{
		cout << "\nВведите номер алгоритма:";
		cout << "\n1. Дейкстра\n2. Беллман-Форда\n3. Флойд-Уоршелл\n4. Прим\n5. Краскалл\n0. Выход" << endl;
		cin >> numb;

		//Анализ полученного ответа
		switch (numb)
		{
		case 1: //алгоритм Дейсктры
			if (matrix_number != 1 && matrix_number != 4)
			{
				cout << "Выбрана некорректная матрица смежности - граф должен быть ориентированным, " <<
					"взвешенным и не содержать рёбра с отрицательным весом" << endl;
				break;
			}
			cout << "\nДейкстра: \n";
			cout << "Введите вершину (от 1 до " << SIZE << "): ";
			cin >> peak;
			peak--;
			if (peak < 0 || peak > SIZE - 1)
			{
				cout << "\nВведена несуществующая вершина\n";
				break;
			}
			dijkstra_algorithm(adjacency_matrix, shortest, previous, peak);
			cout << "Окончательный результат: " << endl;
			print_shortest(peak, shortest, previous);
			break;
		case 2: //алгоритм Белмана-Форда
			/*if (matrix_number != 2 && matrix_number != 1 && matrix_number != 3)
			{
				cout << "Некорректная матрица смежности - граф должен быть ориентированным и взвешенным" << endl;
				break;
			}*/
			cout << "\nБелман-Форд: \n";
			cout << "Введите вершину (от 1 до " << SIZE << "): ";
			cin >> peak;
			peak--;
			if (peak < 0 || peak > SIZE - 1)
			{
				cout << "\nВведена несуществующая вершина\n";
				break;
			}
			bellman_ford_algorithm(adjacency_matrix, shortest, previous, peak);
			cout << "Окончательный результат:" << endl;
			print_shortest(peak, shortest, previous);
			break;
		case 3: //алгоритм Флойда-Уоршелла
			if (false)
			{
				cout << "Неправильная матрица смежности." << endl;
				break;
			}
			cout << "\nФлойд-Уоршелл: \n";
			floyd_warshall_algorithm(adjacency_matrix, shortest_floyd_warshall, previous_floyd_warshall);
			cout << "Окончательный результат:" << endl;
			print_matrix(shortest_floyd_warshall);
			print_matrix(previous_floyd_warshall);
			break;
		case 4: //алгоритм Прима
			if (!(matrix_number == 4 || matrix_number == 5))
			{
				cout << "Неправильная матрица смежности." << endl;
				break;
			}
			cout << "Прим: " << endl;
			prim_algorithm(adjacency_matrix);
			break;
		case 5: //алгоритм Краскалла
			if (!(matrix_number == 4 || matrix_number == 5))
			{
				cout << "Неправильная матрица смежности." << endl;
				break;
			}
			cout << "\nКраскалл: \n";
			kruskal_algorithm(adjacency_matrix);
			break;
		case 0: //конец программы
			break;
		default: cout << "\nНеизвестная команда\n" << endl;
		}//switch
	}

	delete[] shortest;
	delete[] previous;

	system("pause");
	return 0;
}
