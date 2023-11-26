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
    //������������� ����������
    int* passed_peaks = new int[SIZE]; //��-�� � ����������� ���������
    int min;
    
    //��������� passed_peaks ������
    for (int i = 0; i < SIZE; i++)
        *(passed_peaks + i) = 0;

    //��������� shortest � previous
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

    cout << "������������� ����������: " << endl;
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

    delete[] passed_peaks;//�������� ���������� ������
}

void print_shortest(int peak, int* shortest, int* previous)
{
    for (int j = 0; j < SIZE; j++)
    {
        if (j == peak)
            continue;
        if (*(shortest + j) == NO_WAY)
        {
            cout << "��� ���� � ������� " << j + 1 << endl;
        }
        else
        {
            cout << "���������� ���������� � ������� " << j + 1 << " - " << *(shortest + j) << endl;
            cout << "���������� ������� " << *(previous + j) + 1 << endl;
        }
    }
    cout << endl;
}

void relax(int matrix[][SIZE], int* shortest, int* previous, int a, int b)
{
	if (*(*(matrix + a) + b) != NO_WAY && *(shortest + a) != NO_WAY) 
    {
		if (*(shortest + a) + *(*(matrix + a) + b) < *(shortest + b)) //�������� ����������� ����
		{
            *(shortest + b) = *(shortest + a) + *(*(matrix + a) + b); 
            *(previous + b) = a; 
		}
	}
}

void bellman_ford_algorithm(int matrix[][SIZE], int* shortest, int* previous, int peak)
{
    //��������� shortest � pred
    for (int i = 0; i < SIZE; i++)
    {
        //�������� ���� �� ��������� ������
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

    cout << "������������� ����������:" << endl;
    for (int i = 0; i < SIZE - 1; i++)
    {
        //�������� ������ ��� ������� ����� size-1 ���
        for (int j = 0; j < SIZE; j++)
            for (int k = 0; k < SIZE; k++)
                if (*(*(matrix + j) + k) != NO_WAY)
                    relax(matrix, shortest, previous, j, k);
        //������ shortest � pred
        print_shortest(peak, shortest, previous);
    }

    //��������� ������ �������������� �����
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
            //�������� ������� ��������� � shortestFU
            shortest_floyd_warshall[i][j] = matrix[i][j];
            //��������� ������� predFU
            if (matrix[i][j] != NO_WAY && i != j)
                previous_floyd_warshall[i][j] = i;
            else
                previous_floyd_warshall[i][j] = -1;
        }
    }

    cout << "������������� ����������:" << endl;

    //����� ����������� ���� �� i � j ����� k
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
        cout << "���������� ���������� � �������: " << endl;
        print_matrix(shortest_floyd_warshall);
        cout << endl;
        cout << "���������� �������: " << endl;
        print_matrix(previous_floyd_warshall);
        cout << endl;
    }

    //������ ����� �� ������ ��� ������ ��������� �������
    for (int j = 0; j < SIZE; j++)
    {
        cout << "�������: " << j << endl;
        for (int i = 0; i < SIZE; i++)
        {
            int x = i;

            while (x != -1)
            {
                cout << x << " <- "; //����� �����
                x = previous_floyd_warshall[j][x];
            }//while

            cout << endl;
        }
        cout << endl;
    }
}

//������� ������ �������������� �����
bool negative_cycle(int matrix[][SIZE], int* shortest, int* previous)
{
    //������������� ����������
    int cycle_start = -1;//���� ���������� �������������� ����� � ������ ��� ������

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            //���� ��������� ���� < 0
            if (matrix[i][j] != NO_WAY && (matrix[i][j] + shortest[i] < shortest[j]) && shortest[j] != NO_WAY && shortest[i] != NO_WAY)
            {
                cycle_start = i; //���������� ������ �������������� �����
                break;
            }
        }

        if (cycle_start != -1) 
            break; //���� ����� ������������� ����
    }

    //�� ����� ������������� ����
    if (cycle_start == -1)
    {
        cout << "\n�������������� ����� ���" << endl;
    }
    else//����� ������� ������� ������ �������� �������������� �����
    {
        cout << "\n������ ������������� ����: " << endl << "<= ";
        int x = cycle_start;
        do 
        {
            cout << x+1 << " <= "; //����� ������ �����
            x = *(previous + x);
        } while (x != cycle_start); //���� �� ��������� � ������� ������ �����
        cout << endl;

        return true;
    }
    cout << endl << endl;

    return false;
}

void prim_algorithm(int matrix[][SIZE])
{
    //������������� ����������
    bool* flags = new bool[SIZE]; //��������� ������ ��� ������ ������ ��� ������
    int min, from, to; //�������, ������, ����
    flags[0] = true; //��������� �������� ���� ������ �������
    int weight = 0; //����������� ��� ��������� ������

    for (int z = 0; z < SIZE - 1; z++)
    {
        min = NO_WAY;
        from = 0;//������
        to = 0;//����

        for (int i = 0; i < SIZE; i++) //������
        {
            if (flags[i])//���� �������� �������� ���� �������
            {
                for (int j = 0; j < SIZE; j++) //����
                {
                    if (!flags[j] && matrix[i][j] != NO_WAY && min > matrix[i][j]) //���� �� �������� ���� � �� ����������
                    {
                        min = matrix[i][j]; //���� �������
                        from = i; //���������� ������
                        to = j; //� ����  
                    }
                }
            }
        }

        cout << from << " => " << to << " : " << matrix[from][to] << endl;
        flags[to] = true;
        weight += matrix[from][to]; //����������� ��� ��������� ������
    }

    cout << "����������� ��� ������ = " << weight << endl;
    delete[] flags;//�������� ���������� ������
}

void kruskal_algorithm(int matrix[][SIZE])
{
    //������������� ����������
    //��������� ������ ��� ������ ���� ����� ������� size^2
    Edge* edges = new Edge[SIZE * SIZE]{ NULL };
    int k = 0;//���������� �����
    int* flags = new int[SIZE]; //��������� ������ ��� ������ ��������

    //��������� ������ ������ �� ������� ���������
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

    //��������� ������ ���� �� �����������
    sort(edges, k);

    int weight = 0; //��� ������������ ��������� ������

    //������ ������� ���������� ����������� ������ ���������
    for (int i = 0; i < SIZE; i++)
        *(flags + i) = i;

    //���� �� ���� �����
    for (int i = 0; i < k; i++)
    {
        if (flags[edges[i].from] != flags[edges[i].to])
        {   // �������� �������������� ������ ������ ����������
            int oldflag = flags[edges[i].to];

            for (int j = 0; j < SIZE; j++)
            { // ���� ��� ������� ��������
                if (flags[j] == oldflag)
                {
                    flags[j] = flags[edges[i].from];
                }
            }

            weight += edges[i].weight; //����������� ��� ��������� ������
            cout << edges[i].from << " -> " << edges[i].to << " : " << edges[i].weight << endl;
        }
    }

    cout << "����������� ��� ���������� ������:";
    cout << weight << endl;

    //�������� ���������� ������
    delete[] flags;
    delete[] edges;
}

void sort(Edge* array, int size)
{
    //������������� ����������
    Edge Key;
    int i, j;

    //���� ���������� �� ����� �� array[0]
    for (i = 1; i < size; i++)
    {
        Key = array[i]; //���������� ����
        j = i - 1; //�������� � i-1 ��-��

        //���� ������������
        while (j >= 0 and array[j].weight > Key.weight)
        {
            array[j + 1] = array[j];
            j--;

        }//while

        array[j + 1] = Key;
    }
}


