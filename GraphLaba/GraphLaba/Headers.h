#include <iostream>
#include <list>

#define SIZE 10
#define NO_WAY INT_MAX

//�����
struct Edge
{
	int weight; //��� �����
	int	from; //������
	int to; //����
};

using namespace std;

//�������� ��������
void dijkstra_algorithm(int matrix[][SIZE], //������� ���������
	int* shortest, //������ � ����������� ������������
	int* previous, //������ � ����������� ���������
	int peak //�������
);

//�������� ��������-�����
void bellman_ford_algorithm(int matrix[][SIZE], //������� ���������
	int* shortest, //������ � ����������� ������������
	int* previous, //������ � ����������� ���������
	int peak //�������
);

//�������� ������-��������
void floyd_warshall_algorithm(int matrix[][SIZE], //������� ���������
	int shortest_floyd_warshall[][SIZE], //������� � ����������� ������������
	int previous_floyd_warshall[][SIZE] //������� � ����������� ���������
);

//�������� �����
void prim_algorithm(int matrix[][SIZE] //������� ���������
);

//�������� ��������
void kruskal_algorithm(int matrix[][SIZE] //������� ���������
);

//������ �������
void print_matrix(int matrix[][SIZE] //������� ���������
);

//������ 
void print_shortest(int peak, //�������
	int* shortest, //������ � ����������� ������������
	int* previous  //������ � ����������� ���������
);

//������� relax
void relax(int matrix[][SIZE], //������� ���������
	int* shortest, //������ � ����������� ������������
	int* previous, //������ � ����������� ���������
	int a, //������ ������ �������
	int b //������ ������ �������
);

//������� ������ �������������� �����
bool negative_cycle(int matrix[][SIZE], //������� ���������
	int* shortest, //������ � ����������� ������������
	int* previous  //������ � ����������� ���������
);

//����������
void sort(Edge* array, //������ �����
	int size 
);


