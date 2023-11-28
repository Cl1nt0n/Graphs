/********************************************************************
*                КАФЕДРА № 304 2 КУРС                               *
*-------------------------------------------------------------------*
* Project Type  : Win64 Console Application                         *
* Project Name  : Laba 3 sem graph                                  *
* File Name     : Laba 3 sem graph.cpp                              *
* Language      : C/C++                                             *
* Programmer(s) : Цыбуля А. К.                                      *
*               : Панфилов М. М                                     *
* Modifyed By   :                                                   *
* Created       : 02/11/23                                          *
* Last Revision : 21/11/23                                          *
* Comment(s)    : Взвешенный ориентированный граф                   *
*                                                                   *
*********************************************************************/

//------ПОДКЛЮЧЕНИЕ БИБЛИОТЕК------//
#include <iostream> 
using namespace std;

//Структура Ребра графа
struct Edge
{
	int weight, from, to; //вес ребра и его вершины
};

//------ПРОТОТИПЫ ФУНКЦИЙ------//
//---Алгоритмы поиска кратчайшего пути---
//Дейкстра
void Dijkstra(int** Matr, int size, int shortest[], int pred[], int Vershina);
//Балмана-Форда
void bellman_ford_algorithm(int** Matr, int size, int shortest[], int pred[], int Vershina);
//Флойда-Уоршелла
void floyd_warshall_algorithm(int** Matr, int size, int** shortestFU, int** predFU);
//Функция поиска отрицательного цикла
void NegativeCycle(int** Matr, int size, int shortest[], int pred[]);

//---Алгоритмы составления остовного дерева---
//Прима
void prim_algorithm(int size, int** Matr);
//Крускалла
void kruskal_algorithm(int size, int** Matr);

//---Вспомогательные функции---
//Функция печати одномерного массива
void print(int shortest[], int pred[], int Vershina, int size);
//Функция печати матрицы
void printMatr(int size, int** matrix);
//Процедура Relax (рассчет shortest и pred)
void relax(int** Matr, int shortest[], int pred[], int u, int v);
//Процедура сортировки вставкой
void Insertion_sort(Edge* array, int size);

//------ГЛОБАЛЬНЫЕ КОНСТАНТЫ------//
const int NO_PATH = INT_MAX; //Такого ребра - нет

//------ОСНОВНАЯ ПРОГРАММА------//
int main()
{
	setlocale(LC_ALL, "ru");//русский язык

	//---Инициализация переменных---
	const int size = 10; //размер графа
	int shortest[size]; //одномерный массив кратчайщих путей до вершины
	int pred[size]; //массив предшествующих вершин в кратчайшем пути
	int Vershina; //номер вершины начала обхода
	int answer = 1; //Переменная для цикла ввода ответа
	int matrix_number = -1; //номер выбранной матрицы смежности

	//Выделяем память для матрицы shortestFU
	int** shortestFU = new int* [size]; //shortest для алгоритма Флойда-Уоршелла
	for (int i = 0; i < size; i++)
	{
		shortestFU[i] = new int[size];

	}

	//Выделяем память для матрицы predFU
	int** predFU = new int* [size]; //pred для алгоритма Флойда-Уоршелла
	for (int i = 0; i < size; i++)
	{
		predFU[i] = new int[size];

	}

	//------Наборы матриц смежности для тестов------//
//-----------------------------------------------

//Матрица Смежности для алгоритма Дейкстры (без отрицательных весов)
//-----------------------------------------------
	//Матрица Смежности для алгоритма Дейкстры (без отрицательных весов)
//-----------------------------------------------
	/*cout << "\n№1" << endl;
	matrix_number = 1;
	cout << "Матрица Смежности без отрицательных весов" << endl;
	int Matr_smezh[size][size] =
	{
		{NO_PATH, 4, NO_PATH, 8, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 14, NO_PATH},
								{NO_PATH, NO_PATH, 13, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 7, NO_PATH, NO_PATH},
								{NO_PATH, NO_PATH, NO_PATH, 24, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 6},
								{NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 18, NO_PATH, NO_PATH, NO_PATH, NO_PATH},
								{NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 20, NO_PATH},
								{NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 15, 5, NO_PATH, NO_PATH},
								{NO_PATH, NO_PATH, 21, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH},
								{NO_PATH, NO_PATH, NO_PATH, NO_PATH, 9, NO_PATH, NO_PATH, NO_PATH, 6, NO_PATH},
								{NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 10},
								{NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 18, NO_PATH, NO_PATH, NO_PATH}
	};*/


	//
	//-----------------------------------------------
	// 
	//Матрица Смежности с отрицательными весами рёбер без цикла
	//-----------------------------------------------
	//cout << "\n№2" << endl;
	//cout << "Матрица Смежности с отрицательными весами рёбер без цикла" << endl;
	//int Matr_smezh[size][size] =   {{NO_PATH, 4, NO_PATH, 8, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 14, NO_PATH},
	//                                {NO_PATH, NO_PATH, 13, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 7, NO_PATH, NO_PATH},
	//                                {NO_PATH, NO_PATH, NO_PATH, 24, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 6},
	//                                {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, -18, NO_PATH, NO_PATH, NO_PATH, NO_PATH},
	//                                {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 20, NO_PATH},
	//                                {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, -15, 5, NO_PATH, NO_PATH},
	//                                {NO_PATH, NO_PATH, 21, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH},
	//                                {NO_PATH, NO_PATH, NO_PATH, NO_PATH, 9, NO_PATH, NO_PATH, NO_PATH, 6, NO_PATH},
	//                                {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 10},
	//                                {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, -18, NO_PATH, NO_PATH, NO_PATH} };
	//-----------------------------------------------
	//
	////Матрица Смежности с отрицательными весами рёбер с циклом
	////-----------------------------------------------
	//cout << "\n№3" << endl;
	//cout << "Матрица Смежности с отрицательными весами рёбер с циклом" << endl;
	//int Matr_smezh[size][size] = { {NO_PATH, 4, NO_PATH, 8, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 14, NO_PATH},
	//                                {NO_PATH, NO_PATH, 13, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 7, NO_PATH, NO_PATH},
	//                                {NO_PATH, NO_PATH, NO_PATH, 24, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 6},
	//                                {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, -18, NO_PATH, NO_PATH, NO_PATH, NO_PATH},
	//                                {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 20, NO_PATH},
	//                                {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, -15, 5, NO_PATH, NO_PATH},
	//                                {NO_PATH, NO_PATH, -21, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH},
	//                                {NO_PATH, NO_PATH, NO_PATH, NO_PATH, 9, NO_PATH, NO_PATH, NO_PATH, 6, NO_PATH},
	//                                {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 10},
	//                                {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, -18, NO_PATH, NO_PATH, NO_PATH} 
	//};

	////-----------------------------------------------

	//Неориентированный граф с отрицательными ребрами
	//-----------------------------------------------
		/*cout << "\n№4" << endl;
		matrix_number = 4;
		cout << "Неориентированный граф с отрицательными ребрами" << endl;
		int Matr_smezh[size][size] = { {NO_PATH, 4, NO_PATH, 8, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 14, NO_PATH},
									   {4, NO_PATH, 13, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 7, NO_PATH, NO_PATH},
									   {NO_PATH, 13, NO_PATH, 24, NO_PATH, NO_PATH, 21, NO_PATH, NO_PATH, 6},
									   {8, NO_PATH, 24, NO_PATH, NO_PATH, -18, NO_PATH, NO_PATH, NO_PATH, NO_PATH},
									   {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 9, 20, NO_PATH},
									   {NO_PATH, NO_PATH, NO_PATH, -18, NO_PATH, NO_PATH, -15, 5, NO_PATH, NO_PATH},
									   {NO_PATH, NO_PATH, 21, NO_PATH, NO_PATH, -15, NO_PATH, NO_PATH, NO_PATH, -18},
									   {NO_PATH, 7, NO_PATH, NO_PATH, 9, 5, NO_PATH, NO_PATH, 6, NO_PATH},
									   {14, NO_PATH, NO_PATH, NO_PATH, 20, NO_PATH, NO_PATH, 6, NO_PATH, 10},
									   {NO_PATH, NO_PATH, 6, NO_PATH, NO_PATH, NO_PATH, -18, NO_PATH, 10, NO_PATH} };*/
									   //-----------------------------------------------
									   // 
									   // /Неориентированный граф без отрицательных ребрер
									   //-----------------------------------------------
	cout << "\n№5" << endl;
	matrix_number = 5;
	cout << "Неориентированный граф без отрицательных ребрер" << endl;
	int Matr_smezh[size][size] =
	{
	{NO_PATH, 10,     NO_PATH, NO_PATH, 8,      NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH},
	{10,     NO_PATH, 3,      7,      NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH},
	{NO_PATH, 3,      NO_PATH, 3,      6,      NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH},
	{NO_PATH, 7,      3,      NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 3     },
	{8,      NO_PATH, 6,      NO_PATH, NO_PATH, 9,      20,     5,      NO_PATH, NO_PATH},
	{NO_PATH, NO_PATH, NO_PATH, NO_PATH, 9,      NO_PATH, 18,     NO_PATH, NO_PATH, 16    },
	{NO_PATH, NO_PATH, NO_PATH, NO_PATH, 20,     18,     NO_PATH, NO_PATH, NO_PATH, NO_PATH},
	{NO_PATH, NO_PATH, NO_PATH, NO_PATH, 5,      NO_PATH, NO_PATH, NO_PATH, 14,     NO_PATH},
	{NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 14,     NO_PATH, NO_PATH},
	{NO_PATH, NO_PATH, NO_PATH, 3,      NO_PATH, 16,     NO_PATH, NO_PATH, NO_PATH, NO_PATH},
	};
	//-----------------------------------------------
					//-----------------------------------------------------//

		//Заносим матрицу смежности в динамическую память
	int** Matr_smezh_ptr = new int* [size];
	for (int i = 0; i < size; i++) //матрица смежности в динамической памяти
	{
		Matr_smezh_ptr[i] = Matr_smezh[i];

	}
	printMatr(size, Matr_smezh_ptr);

	//-----Открыть меню выбора опции-----
	while (true)
	{
		cout << "\n\tВведите номер алгоритма:";
		cout << "\n 1. Дейкстра\n 2. Белмана-Форда\n 3. Флойда-Уоршелла\n 4. Прима\n 5. Крускалла\n 0. Выход" << endl;
		cin >> answer;

		//Анализ полученного ответа
		switch (answer) {
		case 1: //алгоритм Дейсктры
			if (matrix_number == 1)
			{
				cout << "\nДейкстра: \n";
				cout << "Введите вершину (от 0 до 9): ";
				cin >> Vershina;
				if (Vershina < 0 or Vershina > 9)
				{
					cout << "\nВведена несуществующая вершина\n";
					break;
				}
				Dijkstra(Matr_smezh_ptr, size, shortest, pred, Vershina);
				cout << "Окончательный результат:" << endl;
				print(shortest, pred, Vershina, size);
				break;
			}
			else
			{
				cout << "Выбрана некорректная матрица смежности - граф должен быть ориентированным, взвешенным и не содержать рёбра с отрицательным весом" << endl;
				break;
			}

		case 2: //алгоритм Белмана-Форда
			if (matrix_number == 4 or matrix_number == 5)
			{
				cout << "Некорректная матрица смежности - граф должен быть ориентированным и взвешенным" << endl;
				break;
			}
			else
			{
				cout << "\nБелман-Форд: \n";
				cout << "Введите вершину (от 0 до 9): ";
				cin >> Vershina;
				if (Vershina < 0 or Vershina > 9)
				{
					cout << "\nВведена несуществующая вершина\n";
					break;
				}
				bellman_ford_algorithm(Matr_smezh_ptr, size, shortest, pred, Vershina);
				cout << "Окончательный результат:" << endl;
				print(shortest, pred, Vershina, size);
				break;
			}
		case 3: //алгоритм Флойда-Уоршелла
			if (matrix_number == 4 or matrix_number == 5)
			{
				cout << "Некорректная матрица смежности - граф должен быть ориентированным и взвешенным" << endl;
				break;
			}
			else
			{
				cout << "\nФлойд-Уоршелл: \n";
				floyd_warshall_algorithm(Matr_smezh_ptr, size, shortestFU, predFU);
				cout << "Окончательный результат:" << endl;
				printMatr(size, shortestFU);
				printMatr(size, predFU);
				break;

			}
		case 4: //алгоритм Прима
			if (matrix_number == 4 or matrix_number == 5)
			{
				cout << "\nПрим: \n";
				prim_algorithm(size, Matr_smezh_ptr);
				break;
			}
			else
			{
				cout << "Выбрана некорректная матрица смежности - граф должен быть неориентированным и взвешенным (а матрица - симетрична)." << endl;
				break;
			}

		case 5: //алгоритм Крускалла
			if (matrix_number == 4 or matrix_number == 5)
			{
				cout << "\nКрускалла: \n";
				kruskal_algorithm(size, Matr_smezh_ptr);
				break;
			}
			else
			{
				cout << "Выбрана некорректная матрица смежности - граф должен быть неориентированным и взвешенным (а матрица - симетрична)." << endl;
				break;
			}
		case 0: //конец программы
			cout << "\n\tСпасибо, что воспользовались нашей программой!" << endl;

			//---Очищение выделенной динамической памяти---
			for (int i = 0; i < size; i++)
			{
				delete[] shortestFU[i];
				delete[] predFU[i];
			};

			delete[] Matr_smezh_ptr;
			delete[] shortestFU;
			delete[] predFU;

			return 0;
		default: cout << "\nНеизвестная команда\n" << endl;
		}//switch
	}

	return 0;
}//end main

		//------РЕАЛИЗАЦИЯ ФУНКЦИЙ------//

//Печать вектора
void print(int shortest[], int pred[], int Vershina, int size)
{
	cout << "Vershina = " << Vershina << endl;
	for (int j = 0; j < size; j++)
	{
		if (j != Vershina)
		{
			if (shortest[j] == NO_PATH) //если пути в вершину нет
			{
				cout << "There is no way to the point " << j << endl;
			}//if 2
			else
			{
				cout << "shortest to " << j << "   " << shortest[j] << endl;
				cout << "pred to " << j << "  " << pred[j] << endl;
			}//else

		}//if1
	}//for j
	cout << '\n';
}//end print

//Дейкстра
void Dijkstra(int** Matr, int size, int shortest[], int pred[], int Vershina)
{
	//Инициализация переменных
	int* Q = new int[size];// мн-во с неисследованными вершинами
	int u = 0; //вершина относительно которой смотрим пути
	int i; //переменная цикла
	int min;
	//заполняем Q вершинами
	for (int i = 0; i < size; i++)
	{
		Q[i] = 0;
	}//for i

	//заполняем shortest и pred
	for (int v = 0; v < size; v++)
	{
		//отделить ноль от остальных вершин
		if (v != Vershina)
		{
			shortest[v] = NO_PATH;
			pred[v] = -1;
		}//if
		else {
			shortest[v] = 0;
			pred[v] = -1;
		}

	}//for v

	cout << "Промежуточные результаты:" << endl;
	//это мы короче смотрим ищем с мин шортест эл-т
	//а потом добавляем его Q с 0 на 1
	for (int h = 0; h < size; h++) {
		int min = -1;
		for (int u = 0; u < size; u++) {
			if (Q[u] == 0 and ((min == -1) or (shortest[u] < shortest[min])))
			{
				min = u;
			}//if
		}//for u
		Q[min] = 1;

		//relax
		for (int v = 0; v < size; v++)
		{
			relax(Matr, shortest, pred, min, v);
		}//for v

		print(shortest, pred, Vershina, size);
	}//for h

	for (int i = 0; i < size; i++)
	{
		int x = i;

		while (x != -1)
		{
			cout << x << " <- "; //вывод верши
			x = pred[x];
		}//while

		cout << endl;
	}

	delete[] Q;//очищение выделенной памяти
	return;
}//end Дейкстра

//Белмана-Форда
void bellman_ford_algorithm(int** Matr, int size, int shortest[], int pred[], int Vershina)
{
	//заполняем shortest и pred
	for (int v = 0; v < size; v++)
	{
		//отделить ноль от остальных вершин
		if (v != Vershina)
		{
			shortest[v] = NO_PATH;
			pred[v] = -1;
		}//if
		else
		{
			shortest[v] = 0;
			pred[v] = -1;
		}//else

	}//for v
	cout << "Промежуточные результаты:" << endl;

	for (int k = 0; k < size - 1; k++)
	{//вызываем релакс для каждого ребра size-1 раз
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (Matr[i][j] != NO_PATH)
				{
					relax(Matr, shortest, pred, i, j);

				}//if

			}//for j

		}//for i
		//печать shortest и pred
		print(shortest, pred, Vershina, size);

	}//for k

	//Процедура поиска отрицательного цикла
	NegativeCycle(Matr, size, shortest, pred);

	for (int i = 0; i < size; i++)
	{
		int x = i;

		while (x != -1)
		{
			cout << x << " <- "; //вывод верши
			x = pred[x];
		}//while

		cout << endl;
	}

	return;
}//end BF

//Relax
void relax(int** Matr, int shortest[], int pred[], int a, int b)
{
	if (Matr[a][b] != NO_PATH && shortest[a] != NO_PATH) {

		if (shortest[a] + Matr[a][b] < shortest[b]) //выбираем минимальный путь
		{
			shortest[b] = shortest[a] + Matr[a][b]; //переприсваиваем этот путь
			pred[b] = a; //и устанавливаем для него предыдущую вершину
		}//if 2
	}//if 1

}//end relax

//Функция поиска отрицательного цикла
void NegativeCycle(int** Matr, int size, int shortest[], int pred[])
{
	//Инициализация переменных
	int CycleStart = -1;//Флаг нахождения отрицательного цикла и индекс его начала

	for (int u = 0; u < size; u++)
	{
		for (int v = 0; v < size; v++)
		{
			//Если суммарный путь < 0
			if (Matr[u][v] != NO_PATH && (Matr[u][v] + shortest[u] < shortest[v]) && shortest[v] != NO_PATH && shortest[u] != NO_PATH)
			{
				CycleStart = u; //запоминаем начало отрицательного цикла
				break;
			}

		}//for v

		if (CycleStart != -1) break; //если нашли отрицательный цикл
	}//for u

	//Не нашли отрицательный цикл
	if (CycleStart == -1) cout << "\nОтрицательного цикла нет" << endl;
	//Иначе выводим вершины самого сильного отрицательного цикла
	else
	{
		cout << "Найден отрицательный цикл:" << endl;
		int x = CycleStart;
		do {
			cout << x << " -> "; //вывод вершин цикла
			x = pred[x];
		} while (x != CycleStart); //пока не вернулись в вершину начала цикла

	}
	cout << endl << endl;

}//end NegativeCycle

//Флойд-Уоршелл (Надо повторить что в нем происходит)
void floyd_warshall_algorithm(int** Matr, int size, int** shortestFU, int** predFU)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			//копируем матрицу смежности в shortestFU
			shortestFU[i][j] = Matr[i][j];
			//заполняем матрицу predFU
			if (Matr[i][j] != NO_PATH && i != j)
				predFU[i][j] = i;
			else
				predFU[i][j] = -1;
		}//for j
	}//for i

	cout << "Промежуточные результаты:" << endl;

	//поиск кратчайшего пути из i в j через k
	for (int k = 0; k < size; k++)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (shortestFU[i][k] != NO_PATH && shortestFU[k][j] != NO_PATH && i != j)
				{
					if (shortestFU[i][k] + shortestFU[k][j] < shortestFU[i][j])
					{
						shortestFU[i][j] = shortestFU[i][k] + shortestFU[k][j];
						predFU[i][j] = predFU[k][j];
					}//if 2
				}//if 1

			}//for j

		}//for i
		//Печать матриц predFU и shortestFU
		cout << "\nk = " << k << endl;
		cout << "Shortest:" << endl;
		printMatr(size, shortestFU);
		cout << endl;
		cout << "Pred:" << endl;
		printMatr(size, predFU);
		cout << endl;
	}//for k

	//Печать путей до вершин для каждой начальной вершины
	for (int j = 0; j < size; j++)
	{
		cout << "Вершина: " << j << endl;
		for (int i = 0; i < size; i++)
		{
			int x = i;

			while (x != -1)
			{
				cout << x << " <- "; //вывод верши
				x = predFU[j][x];
			}//while

			cout << endl;
		}
		cout << endl;
	}


}//end FW

//Печать матрицы
void printMatr(int size, int** matrix)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] == NO_PATH)
				cout << "-- ";
			else
				cout << matrix[i][j] << " ";

		}//for j
		cout << endl;
	}//for i

}//end printMatr

//Алгоритм Прима
void prim_algorithm(int size, int** Matr)
{
	//Инициализация переменных
	bool* Flag = new bool[size] {false}; //выделение памяти под массив флагов для вершин
	int min, u, v; //минимум, откуда, куда
	Flag[0] = true; //разрешаем просмотр рёбер первой вершины
	int weight = 0; //минимальный вес остовного дерева


	for (int z = 0; z < size - 1; z++)
	{
		min = NO_PATH;
		u = 0;//откуда
		v = 0;//куда

		for (int i = 0; i < size; i++) //откуда
		{
			if (Flag[i])//если разрешён просмотр рёбер вершины
			{
				for (int j = 0; j < size; j++) //куда
				{
					if (!Flag[j] && Matr[i][j] != NO_PATH && min > Matr[i][j]) //если не смотрели путь И он существует
					{
						min = Matr[i][j]; //ищем минимум
						u = i; //запоминаем откуда
						v = j; //и куда  
					}//if 2
				}//for j
			}//if 1
		}//for i

		cout << u << " -> " << v << " : " << Matr[u][v] << endl;
		Flag[v] = true;
		weight += Matr[u][v]; //увеличиваем вес остовного дерева

	}//for z

	cout << "Минимальный вес дерева = " << weight << endl;
	delete[] Flag;//очищение выделенной памяти

}//end Prim 

//Алгоритм Крускалла
void kruskal_algorithm(int size, int** Matr)
{
	//Инициализация переменных
	//выделение памяти под Массив рёбер графа размера size^2
	Edge* Rebra_Massiv = new Edge[size * size]{ NULL };
	int k = 0;//количество ребер
	int* flag = new int[size] {-1}; //выделение памяти под Массив множеств

	//Заполняем массив рёбрами из матрицы смежности
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (Matr[i][j] != NO_PATH)
			{
				Rebra_Massiv[k].weight = Matr[i][j];
				Rebra_Massiv[k].from = i;
				Rebra_Massiv[k].to = j;
				k++;
			}
		}
	}

	//Сортируем массив рёбер по возрастанию
	Insertion_sort(Rebra_Massiv, k);

	int weight = 0; //вес минимального остовного дерева

	for (int i = 0; i < size; i++)
	{   //Каждая вершина изначально принадлежит своему множеству
		flag[i] = i;
	}//for i

	//цикл по всем рёбрам
	for (int i = 0; i < k; i++)
	{
		if (flag[Rebra_Massiv[i].from] != flag[Rebra_Massiv[i].to])
		{   // Проверка принадлежности вершин разным множествам
			int oldflag = flag[Rebra_Massiv[i].to];

			for (int j = 0; j < size; j++)
			{ // Цикл для слияния множеств

				if (flag[j] == oldflag)
				{
					flag[j] = flag[Rebra_Massiv[i].from];
				}//if

			}//for j

			weight += Rebra_Massiv[i].weight; //увеличиваем вес остовного дерева
			cout << Rebra_Massiv[i].from << " -> " << Rebra_Massiv[i].to << " : " << Rebra_Massiv[i].weight << endl;

		}//if
	}//for i


	cout << "Минимальный вес связующего дерева:";
	cout << weight << endl;

	//Очищение выделенной памяти
	delete[] flag;
	delete[] Rebra_Massiv;

}//end Kruskala

//Сортировка вставкой
void Insertion_sort(Edge* array, int size)
{
	//Инициализация переменных
	Edge Key;
	int i, j;

	//цикл сортировок от ключа до array[0]
	for (i = 1; i < size; i++)
	{
		Key = array[i]; //запоминаем ключ
		j = i - 1; //начинаем с i-1 эл-та

		//цикл перестановок
		while (j >= 0 and array[j].weight > Key.weight)
		{
			array[j + 1] = array[j];
			j--;

		}//while

		array[j + 1] = Key;
	}//for i

}// end Insertion_sort

