// EdgesSorting.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

//ребро
struct Edge
{
	int weight; //вес ребра
	int	from; //откуда
	int to; //куда
};

void quick_sort(Edge* sequestion, int start, int end)
{
	if (start >= end)
		return;

	int i = start;//начало массива
	int j = end;//конец массива
	int pivot = sequestion[(start + end) / 2].weight;//конечный элемент массива

	//Делим массив
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

	quick_sort(sequestion, start, j);
	quick_sort(sequestion, i, end);
}

int main()
{
	Edge* edges = new Edge[100];
    int k = 0;

    for (int i = 0; i < INT_MAX; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if (matrix[i][j] != INT_MAX)
            {
                edges[k].weight = matrix[i][j];
                edges[k].from = i;
                edges[k].to = j;
                k++;
            }
        }
    }
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
