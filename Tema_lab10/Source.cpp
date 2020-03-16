/*Nume:Popa Alexandra
Grupa:30224
Tema_lab10:DFS
Observatii:
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Profiler.h"


Profiler p10("lab10");

typedef struct node {
	int key;
	struct node* next;
}Node;

typedef struct graf {
	int n;
	Node **noduri;
	int *parinte;
	int *culoare;
	int *d;
	int *f;
	int *lowlink;
	int *index;
	bool *onStack;
}Graf;

enum culoare { WHITE, GRAY, BLACK };
Node*first = NULL;
Node*stack= NULL;
bool contine_cicluri = false;


typedef struct node2 {
	int key;
	int nrChildren;
	struct node2 **children;
}Node2;

void create_list(Graf *g, int key1, int key2)
{
	Node*p = (Node*)malloc(sizeof(Node));
	p->key = key2;
	p->next =g->noduri[key1];
	g->noduri[key1]=p;
	
}
void insert_list(int key)
{
	Node*p = (Node*)malloc(sizeof(Node));
	p->key = key;
	p->next = NULL;
	if (first == NULL)
	{
		first = p;
	}
	else {
		p->next = first;
		first = p;
	}
}
void push(int key)
{
	Node*p = (Node*)malloc(sizeof(Node));
	p->key = key;
	p->next = NULL;
	if (stack == NULL)
	{
		stack = p;
	}
	else {
		p->next = stack;
		stack = p;
	}
}
int pop()
{
	int el;
	if (stack != NULL)
	{
		Node*p = stack;
		el = stack->key;
		stack = stack->next;
		free(p);
	}
	return el;

}
void show_list()
{
	printf("\n");
	Node* p = first;
	while (p != NULL)
	{
		printf("%d ",p->key);
		p = p->next;
	}
}

void DFS(Graf*g, int s,int *time,Operation op)
{
	//printf("%d ", s);
	(*time)++;
	g->culoare[s] = GRAY;
	g->d[s] = *time;
	Node*p = g->noduri[s];
	op.count(2);
	while (p != NULL)
	{
		op.count(1);
		if (g->culoare[p->key] == WHITE)
		{
			op.count(1);
			g->parinte[p->key] = s;
			DFS(g, p->key, time,op);
		}
		else {
			op.count(1);
			if (g->culoare[p->key] == GRAY)
			{
				//printf("\nGraful contine cicluri intre (%d,%d).\n", s, p->key);
				contine_cicluri = true;
			}
		}
		p = p->next;
	}
	g->culoare[s] = BLACK;
	(*time)++;
	g->f[s] = *time;
	op.count(2);
	insert_list(s);

}

void traverse_DFS(Graf* g,Operation op)
{
	int time = 0;
	for (int i = 1;i <= g->n;i++)
	{
		if (g->culoare[i] == WHITE)
		{
			DFS(g, i, &time,op);
			printf("\n");
		}
	}
}
void Tarjan(Graf *g, int s,int *time, int *index)
{
	(*time)++;
	g->culoare[s] = GRAY;
	g->d[s] = *time;
	g->index[s] = *index;
	g->lowlink[s] = *index;
	(*index)++;
	push(s);
	g->onStack[s] = true;
	Node*p = g->noduri[s];
	while (p != NULL)
	{
		if (g->culoare[p->key] == WHITE)
		{
			g->parinte[p->key] = s;
			Tarjan(g, p->key, time,index);
			if ( g->lowlink[p->key]<g->lowlink[s])
			{
				g->lowlink[s] = g->lowlink[p->key];
			}
			else {
				g->lowlink[s] = g->lowlink[s];
			}
		}
		else if (g->onStack[p->key] == true)
		{
			if (g->lowlink[p->key] < g->lowlink[s])
			{
				g->lowlink[s] = g->lowlink[p->key];
			}
			else {
				g->lowlink[s] = g->lowlink[s];
			}
		}
		p=p->next;
	}
	if (g->lowlink[s] == g->index[s])
	{
		int w = 0;
		printf("Componenta tare conexa:");
		while (w != s)
		{
			w =pop();
			g->onStack[w] = false;
			printf("%d ", w);
		}
		printf("\n");
	}
	g->culoare[s] = BLACK;
	(*time)++;
	g->f[s] = *time;


}
void traverse_Tarjan(Graf *g)
{
	int index = 0;
	int time = 0;
	for (int i = 1;i <= g->n;i++)
	{
		if (g->culoare[i] == WHITE)
		{
			Tarjan(g, i,&time,&index);
		}

	}
	
}
void initializare(Graf *g,Operation op)
{
	for (int i = 1;i <= g->n;i++)
	{
		g->noduri[i] = NULL;
		g->parinte[i] = -1;
		g->culoare[i] = WHITE;
		g->d[i] = 0;
		g->f[i] = 0;
		op.count(5);
	}
}
void initializare1(Graf *g)
{
	for (int i = 1;i <= g->n;i++)
	{
		g->noduri[i] = NULL;
		g->parinte[i] = -1;
		g->culoare[i] = WHITE;
		g->d[i] = 0;
		g->f[i] = 0;
		g->lowlink[i] = 0;
		g->onStack[i] = false;
	}
}
void pprint(Node2* root, int level)
{
	printf("\n");
	for (int i = 0;i < level;i++)
	{
		printf("    ");
	}
	printf("%d", root->key);
	for (int i = 0;i < root->nrChildren;i++)
	{
		pprint(root->children[i], level + 1);

	}
	

}
void T1(int n, int parent[])
{
	Node2 *root = NULL;
	Node2 *tree = (Node2*)malloc(sizeof(Node2)*(n + 1));
	int*v = (int*)malloc(sizeof(int)*n);


	for (int i = 1;i <= n;i++)
	{
		v[i] = 0;
	}
	for (int i = 1;i <= n;i++)
	{
		if (parent[i] != -1)
			v[parent[i]]++;
	}

	for (int i = 1;i <= n;i++)
	{
		tree[i].key = i;
		tree[i].nrChildren = 0;
		tree[i].children = (Node2**)malloc(sizeof(Node2*)*v[i]);
	}


	int k = 0;
	for (int i = 1; i <= n; i++) {
		if (parent[i] == -1)
			k++;
	}
	for (int i = 1;i <= n;i++)
	{

		if (parent[i] != -1)
		{

			tree[parent[i]].children[tree[parent[i]].nrChildren] = &tree[i];
			tree[parent[i]].nrChildren++;
		}

	}
	int c = k;
	for (int i = 1;i <= n;i++)
	{
		if (parent[i] == -1)
		{
			root = &tree[i];
			printf("\nArbore %d:\n", k - c + 1);
			c--;
			pprint(root, 0);
		}


	}



}
void show_adjList(Graf *g)
{

	for (int i = 1;i <= g->n;i++)
	{
		printf("%d: ", i);
		Node* p = g->noduri[i];
		while (p != NULL)
		{
			printf("%d ", p->key);
			p = p->next;
		}

		printf("\n");
	}
}
void demo_sortareTopologica()
{
	int n = 8;
	Graf *g = (Graf*)malloc(sizeof(Graf));
	g->n = n;
	g->noduri = (Node**)malloc(sizeof(Node*)*n);
	g->parinte = (int*)malloc(sizeof(int)*n);
	g->culoare = (int*)malloc(sizeof(int)*n);
	g->d = (int*)malloc(sizeof(int)*n);
	g->f = (int*)malloc(sizeof(int)*n);

	Operation op = p10.createOperation("operatii", n);
	initializare(g, op);

	/*create_list(g, 1, 4);
	create_list(g, 1, 2);
	create_list(g, 2, 5);
	create_list(g, 3, 6);
	create_list(g, 3, 5);
	create_list(g, 4, 2);
	create_list(g, 5, 4);
	create_list(g, 6, 6);
	create_list(g, 8, 9);
	create_list(g, 8, 7);
	create_list(g, 9, 7);
	create_list(g, 10, 9);*/


	create_list(g, 1, 8);
	create_list(g, 1, 5);
	create_list(g, 2, 4);
	create_list(g, 2, 3);
	create_list(g, 3, 4);
	create_list(g, 4, 5);
	create_list(g, 4, 1);
	create_list(g, 5, 6);
	create_list(g, 7, 6);
	create_list(g, 8, 7);
	create_list(g, 8, 5);

	printf("Lista de adiacenta:\n");
	show_adjList(g);
	traverse_DFS(g,op);
	T1(n, g->parinte);
	printf("\nSortare topologica:");
	show_list();
}
void demo_algoritmTarjan()
{
	int n = 8;
	Graf *g = (Graf*)malloc(sizeof(Graf));
	g->n = n;
	g->noduri = (Node**)malloc(sizeof(Node*)*n);
	g->parinte = (int*)malloc(sizeof(int)*n);
	g->culoare = (int*)malloc(sizeof(int)*n);
	g->d = (int*)malloc(sizeof(int)*n);
	g->f = (int*)malloc(sizeof(int)*n);
	g->lowlink = (int*)malloc(sizeof(int)*n);
	g->index = (int*)malloc(sizeof(int)*n);
	g->onStack = (bool*)malloc(sizeof(bool)*n);


	initializare1(g);

	/*create_list(g, 1, 4);
	create_list(g, 1, 2);
	create_list(g, 2, 5);
	create_list(g, 3, 6);
	create_list(g, 3, 5);
	create_list(g, 4, 2);
	create_list(g, 5, 4);
	create_list(g, 6, 6);
	create_list(g, 8, 9);
	create_list(g, 8, 7);
	create_list(g, 9, 7);
	create_list(g, 10, 9);*/

	create_list(g, 1, 2);
	create_list(g, 2, 3);
	create_list(g, 3, 1);
	create_list(g, 4, 5);
	create_list(g, 4, 3);
	create_list(g, 4, 2);
	create_list(g, 5, 6);
	create_list(g, 5, 4);
	create_list(g, 6, 7);
	create_list(g, 6, 3);
	create_list(g, 7, 6);
	create_list(g, 8, 8);
	create_list(g, 8, 7);
	create_list(g, 8, 5);

	printf("Lista de adiacenta:\n");
	show_adjList(g);
	traverse_Tarjan(g);
	T1(n, g->parinte);
}
void perform_v_ct()
{
	int n = 100;
	Graf *g = (Graf*)malloc(sizeof(Graf));
	g->n = n;
	g->noduri = (Node**)malloc(sizeof(Node*)*n);
	g->parinte = (int*)malloc(sizeof(int)*n);
	g->culoare = (int*)malloc(sizeof(int)*n);
	g->d = (int*)malloc(sizeof(int)*n);
	g->f = (int*)malloc(sizeof(int)*n);
	srand(NULL);
	for (int e = 1000;e <= 4500;e += 100)
	{
		Operation op = p10.createOperation("operatii_v_ct", e);
		initializare(g, op);
		for (int i = 1;i <= e;i++)
		{
			int u = rand() % n + 1;
			int v = rand() % n + 1;
			create_list(g, u, v);
		}
		traverse_DFS(g,op);
	}
	p10.showReport();

}
void perform_e_ct()
{
	
	Graf *g = (Graf*)malloc(sizeof(Graf));
	int e = 4500;
	srand(NULL);
	for (int n = 100;n <= 200;n += 10)
	{
		Operation op = p10.createOperation("operatii_e_ct", n);

		g->n = n;
		g->noduri = (Node**)malloc(sizeof(Node*)*n);
		g->parinte = (int*)malloc(sizeof(int)*n);
		g->culoare = (int*)malloc(sizeof(int)*n);
		g->d = (int*)malloc(sizeof(int)*n);
		g->f = (int*)malloc(sizeof(int)*n);
		initializare(g, op);
		for (int i = 1; i <= e; i++) {
			int u = rand() % n + 1;
			int v = rand() % n + 1;
			create_list(g, u, v);
		}
		traverse_DFS(g, op);
	}
	p10.showReport();
}
int main()
{
	//demo_sortareTopologica();
	//demo_algoritmTarjan();
	//perform_v_ct();
	perform_e_ct();
	return 0;
}