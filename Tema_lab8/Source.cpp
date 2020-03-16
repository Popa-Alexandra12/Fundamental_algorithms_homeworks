/*Nume:Popa Alexandra
Grupa:30224
Tema_lab8:Multimi disjuncte
Observatii:
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Profiler.h"
#define MAX 40001

Profiler p8("lab8");


typedef struct edge {
	int cost;
	int node1;
	int node2;
}Edge;

void MAKE_SET(int parent[],int rank[], int x,int n)
{
	parent[x] = x;
	rank[x] = 0;
}
int FIND_SET(int parent[], int rank[], int x,Operation op)
{
	op.count();
	if (parent[x] != x)
	{
		parent[x] = FIND_SET(parent, rank, parent[x],op);
	}
	return parent[x];
}
void LINK(int parent[], int rank[], int x, int y, Operation op)
{
	op.count();
	if (rank[x] > rank[y])
	{
		parent[y] = x;
	}
	else {
		parent[x] = y;
		op.count();
		if (rank[x] == rank[y])
		{
			rank[y]++;
		}
	}
}
void UNION(int parent[], int rank[], int x, int y, Operation op)
{
	LINK(parent, rank, FIND_SET(parent, rank, x,op), FIND_SET(parent, rank, y,op),op);
}
int Partition(Edge v[], int n, int p, int r, Operation op)
{
	
	Edge x, aux;
	int i;
	x = v[r];
	i = p - 1;
	for (int j = p;j <= r - 1;j++)
	{
		op.count();
		if (v[j].cost <= x.cost)
		{
			i++;
			aux = v[i];
			v[i] = v[j];
			v[j] = aux;
		}
	}
	
	aux = v[i + 1];
	v[i + 1] = v[r];
	v[r] = aux;
	return i + 1;
}

void QuickSort(Edge v[], int n, int p, int r, Operation op)
{
	int q;
	if (p < r)
	{
		q = Partition(v, n, p, r,op);
		QuickSort(v, n, p, q - 1,op);
		QuickSort(v, n, q + 1, r,op);
	}
}
void KRUSKAL(Edge G[], int nrEdges, int nrNodes,int parent[],int rank[], Operation op)
{
	
	for (int i = 1;i <= nrNodes;i++)
	{
		MAKE_SET(parent, rank, i, nrNodes);
	}
	QuickSort(G, nrEdges, 0, nrEdges,op);
	/*for (int i = 1; i <= nrEdges; i++) {
		printf("Muchia (%d,%d) cu costul %d\n", G[i].node1, G[i].node2, G[i].cost);
	
	}*/
	
	for (int i = 1;i <= nrEdges;i++)
	{
		
		op.count();
		if (FIND_SET(parent, rank, G[i].node1,op) != FIND_SET(parent, rank, G[i].node2,op))
		{
			UNION(parent, rank, G[i].node1, G[i].node2,op);
			printf("(%d,%d)=%d\n", G[i].node1, G[i].node2, G[i].cost);
		}
	}
}
void demo()
{

	Operation op= p8.createOperation("operatii_multimi_disjuncte", 20);
	int parent[10];
	int rank[10];
	for (int i = 1;i <= 10;i++)
	{
		MAKE_SET(parent, rank, i,10);
	}
	UNION(parent,rank,1,2,op);
	UNION(parent, rank, 3,4,op);
	UNION(parent, rank, 5,6,op);
	UNION(parent, rank, 7,8,op);
	UNION(parent, rank, 5,9,op);
	UNION(parent, rank, 3,8,op);



	printf("Nodul 1 se gaseste in setul %d\n", FIND_SET(parent, rank, 1, op));
	printf("Nodul 2 se gaseste in setul %d\n", FIND_SET(parent, rank, 2, op));
	printf("Nodul 3 se gaseste in setul %d\n", FIND_SET(parent, rank, 3, op));
	printf("Nodul 4 se gaseste in setul %d\n", FIND_SET(parent, rank, 4, op));
	printf("Nodul 5 se gaseste in setul %d\n", FIND_SET(parent, rank, 5, op));
	printf("Nodul 6 se gaseste in setul %d\n", FIND_SET(parent, rank, 6, op));
	printf("Nodul 7 se gaseste in setul %d\n", FIND_SET(parent, rank, 7, op));
	printf("Nodul 8 se gaseste in setul %d\n", FIND_SET(parent, rank, 8, op));
	printf("Nodul 9 se gaseste in setul %d\n", FIND_SET(parent, rank, 9, op));
	printf("Nodul 10 se gaseste in setul %d\n", FIND_SET(parent, rank, 10, op));

	
}
void demo1()
{
	int parent[20];
	int rank[20];

	
	Operation op = p8.createOperation("operatii_multimi_disjuncte", 20);
	Edge m[20];
	m[1].node1 = 1;
	m[1].node2 = 2;
	m[1].cost = 4;

	m[2].node1 = 2;
	m[2].node2 = 3;
	m[2].cost = 8;

	m[3].node1 = 3;
	m[3].node2 = 4;
	m[3].cost = 7;

	m[4].node1 = 4;
	m[4].node2 = 5;
	m[4].cost = 9;

	m[5].node1 = 5;
	m[5].node2 = 6;
	m[5].cost = 10;

	m[6].node1 = 6;
	m[6].node2 = 7;
	m[6].cost = 2;

	m[7].node1 = 7;
	m[7].node2 = 8;
	m[7].cost = 1;

	m[8].node1 = 8;
	m[8].node2 = 9;
	m[8].cost = 7;

	m[9].node1 = 1;
	m[9].node2 = 8;
	m[9].cost = 8;

	m[10].node1 = 2;
	m[10].node2 = 8;
	m[10].cost = 11;

	m[11].node1 = 3;
	m[11].node2 = 9;
	m[11].cost = 2;

	m[12].node1 = 7;
	m[12].node2 = 9;
	m[12].cost = 6;

	m[13].node1 = 3;
	m[13].node2 = 6;
	m[13].cost = 4;

	m[14].node1 = 4;
	m[14].node2 = 6;
	m[14].cost = 14;



	KRUSKAL(m, 14, 9, parent, rank, op);



}
void perform()
{
	Edge E[MAX];
	int parent[MAX];
	int rank[MAX];
	srand(NULL);
	for (int j = 1;j < 5;j++) 
	{
		for (int n = 100;n <= 10000;n += 100)
		{
			Operation op = p8.createOperation("operatii_multimi_disjuncte", n);

			for (int i = 1;i <= n-1 ;i++)
			{
				E[i].node1 = i;
				E[i].node2 = i + 1;
				E[i].cost = rand() % n + 1;

			}
			E[n].node1 = n- 1;
			E[n].node2 =  0;
			E[n].cost = rand() % n + 1;
			for (int i = n+1;i <= 4 * n;i++)
			{
				E[i].node1 = rand() % n;
				E[i].node2 = rand() % n;
				E[i].cost = rand() % n + 1;
			}
			KRUSKAL(E, 4 * n, n, parent, rank, op);


		}
	}
	p8.createGroup("Operatii_multimi_disjuncte", "op");
	p8.showReport();
}
int main()
{
	//demo();
	demo1();
	//perform();
	return 0;
}