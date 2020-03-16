/*Nume:Popa Alexandra
Grupa:30224
Tema_lab4:Interclasare K liste ordonate
Observatii:
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10000
#include "Profiler.h"

Profiler p4("lab4");
typedef struct node {
	int key;
	struct node *next;
 }Node;

typedef struct list {
	Node *first;
	Node *last;
}List;

typedef struct heap_el {
	int key;
	int index_l;    //indexul listei din care provine nodul cu valoarea key
}Heap_el;

List final_list;
int heap_size=0;

void init_list(List *lista)
{
	lista->first = NULL;
	lista->last = NULL;
}

void print_list(int i, List liste[])
{
	printf("Lista numarul %d:", i);
	Node *p = liste[i].first;
	while (p != NULL)
	{
		printf("%d ", p->key);
		p = p->next;
	}
	printf("\n");
}

void print_final_list()
{
	printf("Lista interclasata:");
	Node *p = final_list.first;
	while (p != NULL)
	{
		printf("%d ", p->key);
		p = p->next;
	}
	printf("\n");
}

void insert_node_in_list(int x, List *liste)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->key = x;
	p->next = NULL;
	if (liste->first == NULL)
	{
		liste->first = p;
		liste->last = p;
		
	}
	else {
		liste->last->next = p;
		liste->last = p;
	}
}

void insert_node_in_final_list(int x)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->key = x;
	p->next = NULL;
	if (final_list.first == NULL)
	{
		final_list.first = p;
		final_list.last = p;
	}
	else {
		final_list.last->next = p;
		final_list.last = p;
	}
}

void MIN_HEAPIFY(Heap_el h[], int n, int i,int size,Operation op)
{
	

	int min;
	Heap_el aux;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	op.count();
	
	if (l<n && h[l].key<h[i].key)
		min = l;
	else min = i;
	op.count();
	
	if (r<n && h[r].key<h[min].key)
		min = r;
	if (min != i)
	{
		op.count(3);
		
		aux =h[i];
		h[i] = h[min];
		h[min] = aux;
	    MIN_HEAPIFY(h, n, min,size,op);
	}
    
}

void init_heap(Heap_el *h, int size_heap)
{
	for (int i = 0;i < size_heap;i++)
	{
		h[i].key = INT_MAX;
		h[i].index_l = -1;
	}
}
void HPush(heap_el h[], heap_el el,int size,Operation op)
{
	

	heap_el aux;
	int i;
	heap_size++;
	i = heap_size - 1;
	op.count();
	
	h[i] = el;
	while (i > 0 && h[(i - 1) / 2].key > h[i].key)
	{
		op.count();
		
		aux = h[i];
		h[i] = h[(i - 1) / 2];
		h[(i - 1) / 2] = aux;
		op.count(3);
		
		i = (i - 1) / 2;
	}
	if (i > 0) {
		op.count();
		
	}
}

Heap_el HPop(Heap_el h[],int n,int size,Operation op)
{


	if (heap_size == 0)
		printf("error:underflow heap");
	else {
		Heap_el min;
		op.count(2);
		
		min = h[0];
		h[0] = h[heap_size - 1];
		heap_size--;
		MIN_HEAPIFY(h, heap_size, 0,size,op);
		return min;
	}
}

void interclasare(List liste[], int k, int n,Heap_el h[],Operation op)
{
	

	Heap_el v;
	for (int i = 0;i < k;i++)
	{
		op.count();
		
		v.key = liste[i].first->key;
		v.index_l = i;     
		
		if (liste[i].first != NULL)
		{
			
			HPush(h, v,n,op);
		}
	}
	

	while (heap_size > 0)
	{
		
		v = HPop(h, k,n,op);
		op.count();
		
		insert_node_in_final_list(v.key);
		
		if (liste[v.index_l].first != NULL)     
		{
			op.count();
			
			liste[v.index_l].first = liste[v.index_l].first->next;
		}		
	
		if (liste[v.index_l].first != NULL)
		{
			op.count();
			
			v.key = liste[v.index_l].first->key;
			HPush(h, v,n,op);
		
		}
		
	}
	
	
}

void dealloc_final_list() {
	Node *p;
	while (final_list.first != NULL)
	{
		p = final_list.first;
		final_list.first = final_list.first->next;
		free(p);
	}
	final_list.last = NULL;
}

void demo()
{
	List liste[5];
	
	liste[0].first = NULL;
	liste[0].last = NULL;
	
	Heap_el*h = (Heap_el*)malloc(sizeof(Heap_el) * 5);
	init_heap(h, 5);
	int a[] = { 2,3,6,10,12 };
	int b[] = { 1,4,7,20,34 };
	int c[] = { 5,8,11,15,19 };
	int d[] = { 0,9,22,25,50 };
	init_list(&liste[0]);
	for (int i = 0;i < 5;i++)
	{
		insert_node_in_list(a[i],&liste[0]);
	}
	print_list(0, liste);
	init_list(&liste[1]);
	for (int i = 0;i < 5;i++)
	{
		insert_node_in_list(b[i], &liste[1]);
	}
	print_list(1, liste);
	init_list(&liste[2]);
	for (int i = 0;i < 5;i++)
	{
		insert_node_in_list(c[i], &liste[2]);
	}
	print_list(2, liste);
	init_list(&liste[3]);
	for (int i = 0;i < 5;i++)
	{
		insert_node_in_list(d[i],&liste[3]);
	}
	print_list(3, liste);
	
	Operation op= p4.createOperation("null", 5);

	interclasare(liste, 4, 5, h,op);
	print_final_list();
}
void average_case_k_constant1()
{
	//k constant
	//se aleg valorile 5, 10, 100
	
	const int k= 5;
	Heap_el*h = (Heap_el*)malloc(sizeof(Heap_el) * k);
	init_heap(h, k);
	List *liste=(List*)malloc(sizeof(List)*k);
	int v[MAX];
	int i, j, s;
	
		for (i = 100; i <= 10000; i += 100) {
			Operation op1 = p4.createOperation("op_k=5", i);
			int nr = i / k;
			for (j = 0; j < k; j++) {
				FillRandomArray(v, nr, 10, 50000, false, 1);
				init_list(&liste[j]);
				for (int s = 0; s < nr; s++)
				{
					
					insert_node_in_list( v[s],&liste[j]);
				}

			}
			interclasare(liste, k, i,h,op1);
			dealloc_final_list();

		}

}
void average_case_k_constant2()
{
	

	const int k = 10;
	Heap_el*h = (Heap_el*)malloc(sizeof(Heap_el) * k);
	init_heap(h, k);
	List *liste = (List*)malloc(sizeof(List)*k);
	int v[MAX];
	int i, j, s;
	
		for (i = 100; i <= 10000; i += 100) {
			Operation op2 = p4.createOperation("op_k=10", i);
			int nr = i / k;
			for (j = 0; j < k; j++) {
				FillRandomArray(v, nr, 10, 50000, false, 1);
				init_list(&liste[j]);
				for (int s = 0; s < nr; s++)
				{

					insert_node_in_list(v[s], &liste[j]);
				}

			}
			interclasare(liste, k, i, h,op2);
			dealloc_final_list();

		}

}
void average_case_k_constant3()
{
	
	const int k = 100;
	Heap_el*h = (Heap_el*)malloc(sizeof(Heap_el) * k);
	init_heap(h, k);
	List *liste = (List*)malloc(sizeof(List)*k);
	int v[MAX];
	int i, j, s;
	
		for (i = 100; i <= 10000; i += 100) {
			Operation op3 = p4.createOperation("op_k=100", i);
			int nr = i / k;
			for (j = 0; j < k; j++) {
				FillRandomArray(v, nr, 10, 50000, false, 1);
				init_list(&liste[j]);
				for (int s = 0; s < nr; s++)
				{

					insert_node_in_list(v[s], &liste[j]);
				}

			}
			interclasare(liste, k, i, h,op3);
			dealloc_final_list();

		}

}

void average_case_n_constant()
{
	

	List liste[520];
	int v[MAX];
	int k, i, s;
	
	const int n = 10000;
	

		for (k = 10; k <= 500; k += 10) {
			Operation op4 = p4.createOperation("op_n_constant", k);
			Heap_el*h = (Heap_el*)malloc(sizeof(Heap_el) * k);
			init_heap(h, k);
			int nr = n / k;
			for (i = 0; i < k; i++) {
				FillRandomArray(v, nr, 10, 50000, false, 1);
				init_list(&liste[i]);
				for (int s = 0; s < nr; s++)
				{
					insert_node_in_list(v[s], &liste[i]);
				}

			}
			interclasare(liste, k, i,h,op4);
			dealloc_final_list();


		}
	
	p4.createGroup("Caz mediu-n constant", "op_n_constant");
	p4.showReport();
}
int main()
{   
	demo();
	/*average_case_k_constant1();
	average_case_k_constant2();
	average_case_k_constant3();
	p4.createGroup("Caz mediu-k constant", "op_k=5", "op_k=10", "op_k=100");
	p4.showReport();*/
	average_case_n_constant();
	
}

