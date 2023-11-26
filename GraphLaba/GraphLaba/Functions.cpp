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
        if (i != peak)
        {
            *(shortest + i) = NO_WAY;
            *(previous + i) = -1;
        }
        else 
        {
            *(shortest + i) = 0;
            *(previous + i) = -1;
        }
    }

    cout << "Промежуточные результаты: " << endl;
    for (int i = 0; i < SIZE; i++) {
        min = -1;
        for (int j = 0; j < SIZE; j++)
            if (*(passed_peaks + j) == 0 && ((min == -1) || (*(shortest + j) < *(shortest + min))))
                min = j;
        *(passed_peaks + min) = 1;

        for (int i = 0; i < SIZE; i++)
            relax(matrix, shortest, previous, min, i);

        print_shortest(peak, shortest, previous);
    }

    for (int i = 0; i < SIZE; i++)
    {
        int x = i;

        while (x != -1)
        {
            cout << x+1 << " <= "; 
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
        //отделить ноль от остальных вершин
        if (i != peak)
        {
            *(shortest + i) = NO_WAY;
            *(previous + i) = -1;
        }
        else
        {
            *(shortest + i) = 0;
            *(previous + i) = -1;
        }
    }

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
            cout << x+1 << " <= "; 
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
            //копируем матрицу смежности в shortestFU
            shortest_floyd_warshall[i][j] = matrix[i][j];
            //заполняем матрицу predFU
            if (matrix[i][j] != NO_WAY && i != j)
                previous_floyd_warshall[i][j] = i;
            else
                previous_floyd_warshall[i][j] = -1;
        }
    }

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

    //Печать путей до вершин для каждой начальной вершины
    for (int j = 0; j < SIZE; j++)
    {
        cout << "Вершина: " << j << endl;
        for (int i = 0; i < SIZE; i++)
        {
            int x = i;

            while (x != -1)
            {
                cout << x << " <- "; //вывод верши
                x = previous_floyd_warshall[j][x];
            }//while

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
            cout << x+1 << " <= "; //вывод вершин цикла
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
    bool* flags = new bool[SIZE]; //выделение памяти под массив флагов для вершин
    int min, from, to; //минимум, откуда, куда
    flags[0] = true; //разрешаем просмотр рёбер первой вершины
    int weight = 0; //минимальный вес остовного дерева

    for (int z = 0; z < SIZE - 1; z++)
    {
        min = NO_WAY;
        from = 0;//откуда
        to = 0;//куда

        for (int i = 0; i < SIZE; i++) //откуда
        {
            if (flags[i])//если разрешён просмотр рёбер вершины
            {
                for (int j = 0; j < SIZE; j++) //куда
                {
                    if (!flags[j] && matrix[i][j] != NO_WAY && min > matrix[i][j]) //если не смотрели путь И он существует
                    {
                        min = matrix[i][j]; //ищем минимум
                        from = i; //запоминаем откуда
                        to = j; //и куда  
                    }
                }
            }
        }

        cout << from << " => " << to << " : " << matrix[from][to] << endl;
        flags[to] = true;
        weight += matrix[from][to]; //увеличиваем вес остовного дерева
    }

    cout << "Минимальный вес дерева = " << weight << endl;
    delete[] flags;//очищение выделенной памяти
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
    sort(edges, k);

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
            { // Цикл для слияния множеств
                if (flags[j] == oldflag)
                {
                    flags[j] = flags[edges[i].from];
                }
            }

            weight += edges[i].weight; //увеличиваем вес остовного дерева
            cout << edges[i].from << " -> " << edges[i].to << " : " << edges[i].weight << endl;
        }
    }

    cout << "Минимальный вес связующего дерева:";
    cout << weight << endl;

    //Очищение выделенной памяти
    delete[] flags;
    delete[] edges;
}

void sort(Edge* array, int size)
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
    }
}


