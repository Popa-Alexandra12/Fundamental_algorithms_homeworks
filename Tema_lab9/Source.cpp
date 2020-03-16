/*Nume:Popa Alexandra
Grupa:30224
Tema_lab9:BFS
Observatii:
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Profiler.h"


Profiler p9("lab9");

typedef struct node {
	int key;
	struct node* next;
}Node;

typedef struct graf {
	int n;
	Node **noduri;
	int *parinte;
	int *culoare;
	int *dist;
}Graf;

enum culoare { WHITE, GRAY, BLACK };

Node *first = NULL;
Node *last = NULL;

typedef struct node2 {
	int key;
	int nrChildren;
	struct node2 **children;
}Node2;

void enqueue(int key)
{
	Node*p = (Node*)malloc(sizeof(Node));
	p->next = NULL;
	p->key = key;
	if (first == NULL)
	{
		first = last = p;
	}
	else
	{
		last->next = p;
		last = p;
	}
}
int dequeue()
{
	int el = first->key;
	Node *p = first;
	first = first->next;
	free(p);
	return el;
}
void BFS(Graf*g, int s,Operation op)
{
	first = last = NULL;
	g->culoare[s] = GRAY;
	g->parinte[s] = -1;
	op.count(2);
	enqueue(s);
	while (first != NULL)
	{
		int u = dequeue();
		printf("%d ", u);
		Node *p = g->noduri[u];
		while (p != NULL)
		{
			op.count(1);
			if (g->culoare[p->key] == WHITE)
			{
				g->culoare[p->key] = GRAY;
				g->parinte[p->key] = u;
				g->dist[p->key] = g->dist[u] + 1;
				op.count(3);
				enqueue(p->key);
			}
			p = p->next;
		}
		g->culoare[u] = BLACK;
		op.count(1);

		
	}

}
void traverse_BFS(Graf*g,Operation op)
{
	for (int i = 1;i <= g->n;i++)
	{   op.count(1);
		if (g->culoare[i] == WHITE)
		{
			
			BFS(g, i,op);
			printf("\n");
		}
	}
}
void create_list(Graf*g,int key1, int key2)
{
	Node*p = (Node*)malloc(sizeof(Node));
	p->key = key2;
	p->next = g->noduri[key1];
	g->noduri[key1] = p;
	
	Node*q = (Node*)malloc(sizeof(Node));
	q->key = key1;
	q->next = g->noduri[key2];
	g->noduri[key2] = q;
}
void initializare(Graf *g,Operation op)
{
	for (int i = 1;i <= g->n;i++)
	{
		g->noduri[i] = NULL;
		g->parinte[i] = -1;
		g->culoare[i] = WHITE;
		g->dist[i] = 0;
		op.count(4);
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
	Node2 *tree = (Node2*)malloc(sizeof(Node2)*(n+1));
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
			printf("\nArbore %d:\n",k-c+1);
			c--;
			pprint(root, 0);
		}
			
		
	}
	


}
void demo()
{
	int n = 10;
	Graf *g=(Graf*)malloc(sizeof(Graf));
	Operation op = p9.createOperation("operatii", n);
	g->n = n;
	g->noduri = (Node**)malloc(sizeof(Node*)*n);
	g->parinte = (int*)malloc(sizeof(int)*n);
	g->culoare = (int*)malloc(sizeof(int)*n);
	g->dist = (int*)malloc(sizeof(int)*n);

	initializare(g,op);

	create_list(g, 1, 2);
	create_list(g, 1, 5);
	create_list(g, 2, 6);
	create_list(g, 3, 4);
	create_list(g, 3, 6);
	create_list(g, 3, 7);
	create_list(g, 4, 7);
	create_list(g, 4, 8);
	create_list(g, 6, 7);
	create_list(g, 7, 8);
	create_list(g, 9, 10);

	traverse_BFS(g,op);
	
	T1(n, g->parinte);


}
void perform1()
{
	Graf *g = (Graf*)malloc(sizeof(Graf));
	
	int n = 100;
	g->n = n;
	g->noduri = (Node**)malloc(sizeof(Node*)*n);
	g->parinte = (int*)malloc(sizeof(int)*n);
	g->culoare = (int*)malloc(sizeof(int)*n);
	g->dist = (int*)malloc(sizeof(int)*n);
	
	
	srand(NULL);
	for (int e = 1000;e <= 4500;e += 100)
	{
		Operation op = p9.createOperation("operatii_n_ct", e);
		initializare(g,op);
	
		for (int i = 1; i <= e; i++) {
			int u = rand() % n + 1;
			int v = rand() % n + 1;
			create_list(g, u, v);
		}
		traverse_BFS(g,op);
	}

	p9.showReport();
}
void perform2()
{
	srand(NULL);
	Graf *g = (Graf*)malloc(sizeof(Graf));
	int e = 4500;
	for (int n = 100;n <= 200;n += 10)
	{
		Operation op = p9.createOperation("operatii_e_ct", n);

		g->n = n;
		g->noduri = (Node**)malloc(sizeof(Node*)*n);
		g->parinte = (int*)malloc(sizeof(int)*n);
		g->culoare = (int*)malloc(sizeof(int)*n);
		g->dist = (int*)malloc(sizeof(int)*n);
		initializare(g, op);
		for (int i = 1; i <= e; i++) {
			int u = rand() % n + 1;
			int v = rand() % n + 1;
			create_list(g, u, v);
		}
		traverse_BFS(g, op);
	}
	p9.showReport();
}
int main()
{
	//demo();
	//perform1();
	perform2();
	return 0;
}
