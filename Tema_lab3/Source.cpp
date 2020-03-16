/*Nume:Popa Alexandra
Grupa:30224
Tema_lab3:HeapSort si QuickSort/QuickSelect
Observatii:
			HeapSort:O(nlogn) pt. caz mediu,favorabil si defavorabil
					-foloseste functia Buttom-Up pt. construirea heap-ului deoarece este mai eficienta decat metoda Top-Down
					-nu este static
			QuickSort:O(nlogn) pt. caz mediu si favorabil
					  O(n^2) pt. caz defavorabil
			In cazul favorabil si mediu static cei doi algoritmi de sortare au acesasi timp de O(nlogn).
			In cazul defavorabil,graficele arata faptul ca algoritmul  HeapSort( O(nlogn) ) este mai eficient decat QuickSort( O (n^2) )
		 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include "Profiler.h"

Profiler p3("lab3");

void MAX_HEAPIFY(int v[], int m, int i,Operation *op1)
{
	int largest;
	int aux;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	(*op1).count();
	if (l<m && v[l]>v[i])
		largest = l;
	else largest = i;
	(*op1).count();
	if (r<m && v[r]>v[largest])
		largest = r;
	if (largest != i)
	{
		(*op1).count(3);
		aux = v[i];
		v[i] = v[largest];
		v[largest] = aux;
		MAX_HEAPIFY(v, m, largest,op1);
	}

}
void BUILD_MAX_HEAP_BU(int v[], int n,Operation *op1)
{

	for (int i = n / 2 - 1;i >= 0;i--)
		MAX_HEAPIFY(v, n, i,op1);
}
void HEAP_SORT(int v[], int n)
{
	Operation op1 = p3.createOperation("op_heap_sort", n);
	int aux;
	BUILD_MAX_HEAP_BU(v, n,&op1);
	for (int i = n - 1;i >= 0;i--)
	{
		op1.count(3);
		aux = v[0];
		v[0] = v[i];
		v[i] = aux;
		MAX_HEAPIFY(v, i, 0,&op1);
	}
}


int Partition(int v[], int n, int p, int r)
{
	Operation op2 = p3.createOperation("op_quick_sort", n);

	int x,i,aux;
	op2.count();
	x = v[r];
	i = p - 1;
	for (int j = p;j <= r - 1;j++)
	{
		op2.count();
		if (v[j] <= x)
		{
			i++;
			op2.count(3);
			aux = v[i];
			v[i] = v[j];
			v[j] = aux;
		}
	}
	op2.count(3);
	aux = v[i + 1];
	v[i + 1] = v[r];
	v[r] = aux;
	return i + 1;
}

int Partition_random(int v[], int n, int p, int r,Operation *op3)
{


	int x, i, aux;
	(*op3).count();
	x = v[r];
	i = p - 1;
	for (int j = p;j <= r - 1;j++)
	{
		(*op3).count();
		if (v[j] <= x)
		{
			i++;
			(*op3).count(3);
			aux = v[i];
			v[i] = v[j];
			v[j] = aux;
		}
	}
	(*op3).count(3);
	aux = v[i + 1];
	v[i + 1] = v[r];
	v[r] = aux;
	return i + 1;
}


void QuickSort(int v[], int n, int p, int r)
{
	int q;
	if (p < r)
	{
		q = Partition(v, n, p, r);
		QuickSort(v, n, p, q - 1);
		QuickSort(v, n, q + 1, r);
	}
}


int random(int p, int r)
{
	srand(time(NULL));
	return rand() % (r + 1)+p;

}
int  randomized_partition(int v[], int n, int p, int r)
{
	Operation op3= p3.createOperation("op_quick_sort_randomized", n);

	int i,aux;
	i = random(p, r);
	op3.count(3);
	aux = v[r];
	v[r] = v[i];
	v[i] = aux;
	return Partition_random(v, n, p, r,&op3);
}
void randomized_quicksort(int v[], int n, int p, int r)
{
	int q;
	if (p < r)
	{
		q = randomized_partition(v,n,p,r);
		randomized_quicksort(v,n,p,q-1);
		randomized_quicksort(v,n,q+1,r);
	}
}
int randomized_select(int v[], int n, int p, int r,int i)
{
	int q, k;
	if (p == r)
	{
		return v[p];
	}
	q = randomized_partition(v, n, p, r);
	k = q - p + 1;
	if (i == k)
	{
		return v[q];
	}
	else if (i < k)
		return randomized_select(v, n, p, q - 1, i);
		else return randomized_select(v, n, q+1,r, i-k);
}


void afisare(int v[],int n)
{
	for (int i = 0;i < n;i++)
	{
		printf("%d ", v[i]);
	}
}
void demo()
{
	int v[] = { 40,30,10,20 };
	int n = sizeof(v) / sizeof(v[0]);
	int u[100];
	int z=3;
	memcpy(u, v, sizeof(v));
	printf("Sirul initial:");
	afisare(u, n);
	QuickSort(u,n, 0, n-1);
	printf("\nSirul sortat cu QuickSort:");
	afisare(u, n);
	memcpy(u, v, sizeof(v));
	printf("\nSirul initial:");
	afisare(u, n);
	HEAP_SORT(u, n);
	printf("\nSirul sortat cu HeapSort:");
	afisare(u, n);
	memcpy(u, v, sizeof(v));
	printf("\nSirul initial:");
	afisare(u, n);
	printf("\n%d" ,randomized_select(v, n, 0, n - 1, z));
	

}
void average_case()
{
	int v[10000];
	int u[10000];
	for (int i = 1;i <= 5;i++)
	
		for (int i= 100;i <= 10000;i += 100)
		{
			FillRandomArray(v, i);
			memcpy(u, v, i * sizeof(v[0]));
			HEAP_SORT(u, i);
			QuickSort(v,i,0,i-1);
			
		}
	
	p3.createGroup("operatii_totale_averageCase","op_heap_sort","op_quick_sort");
	
	
	p3.showReport();
}
void worst_case()
{
	int v[10000];
	int u[10000];
	for (int i = 100;i <= 10000;i += 100)
	{
		FillRandomArray(v, i, 10, 50000, false, 2);
	    memcpy(u, v, i * sizeof(v[0]));
    	HEAP_SORT(u, i);
		QuickSort(v, i, 0, i - 1);

	}

	p3.createGroup("operatii_totale_worstCase", "op_heap_sort", "op_quick_sort");


	p3.showReport();
}
void best_case()
{
	int v[10000];
	int u[10000];
	for (int n = 100;n <= 10000;n += 100)
	{
		FillRandomArray(v, n, 10, 50000, false, 1);
		memcpy(u, v, n * sizeof(v[0]));
		HEAP_SORT(u, n);
		randomized_quicksort(v, n , 0, n - 1);

	}

	
	p3.createGroup("operatii_totale_bestCase", "op_heap_sort", "op_quick_sort_randomized");


	p3.showReport();
}
int main()
{
	//demo();
	//average_case();
	//worst_case();
	//best_case();
	return 0;
}
