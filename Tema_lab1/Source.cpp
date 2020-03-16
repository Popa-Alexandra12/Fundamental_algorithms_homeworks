/*Nume:Popa Alexandra
Grupa:30224
Tema_lab1:Metode directe de sortare
Observatii:
	BubbleSort:
				Average case:O(n^2)
				Best case:O(n)
				Worst case:O(n^2)
				Algoritm stabil
				In cazul cel mai bun(atunci cand vectorul este sortat crescator) acesta are o eficienta de O(n),mult mai 
				buna decat in worst case sau average case,cazuri in care este mai putin eficient decat ceilalti algoritmi.
	InsertionSort:
				Average case:O(nlogn)
				Best case:O(n)
				Worst case:O(nlogn)
				Algoritm stabil
				Am ales sa utilizez cautare binara deoarece timpul se reduce de la O(n),
				cum ar fi in cazul unei cautari obisnuite, la O(logn).
				Dintre toti algoritmii de sortare,Insertion Sort are cel mai mic numar de comparatii,
				ceea ce il face mai eficient.
	SelectionSort:
				Average case:O(n^2)
				Best case:O(n^2)
				Worst case:O(n^2)
				Algoritm instabil
				Selection sort trebuie sa parcurga toate elementele din partea nesortata pentru a gasi minimul,
				ceea ce necesita un timp de O(n^2),spre deosebire de insertion sort care necesita un timp de O(nlogn)
				(in cazul utilizarii cautarii binare) pentru a gasi locul primului element din partea nesortata.
				Este un algoritm eficient pentru sortarea unui vector cu numar mic de elemente.
				Numarul de comparatii este acelasi ca in cazul utilizarii sortarii Bubble.
				Dintre toti algoritmii de sortare acesta este algoritmul cu cele mai putine asignari .
	Prin urmare,pentru cazurile average,worst si best,graficele arata faptul ca Insertion Sort este algoritmul de sortare
	cel mai eficient,urmat de Selection Sort si apoi de Bubble Sort.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Profiler.h"
Profiler p("lab1");
void bubble_sort(int v[], int n)
{
	Operation op1 = p.createOperation("bubble_comp", n);
	Operation op2 = p.createOperation("bubble_assign", n);
	int aux;

	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < n-i-1; j++)
		{
			op1.count();
			if (v[j] > v[j+1])
			{
				op2.count(3);
				aux = v[j];
				v[j] = v[j+1];
				v[j+1] = aux;

			}
		}
	}
}
int binary_search(int v[],int n, int st, int dr, int x)
{
	Operation op1 = p.createOperation("insertion_comp", n);
	Operation op2 = p.createOperation("insertion_assign", n);
	int mid;
	if (st >= dr) return st;
	else {
		mid = (dr + st) / 2;
		op1.count();
	    if(v[mid]>x)
			return binary_search(v, n, st, mid, x);
		else return binary_search(v, n, mid+1, dr, x);
	}
}
void insertion_sort(int v[], int n)
{
	Operation op1 = p.createOperation("insertion_comp", n);
	Operation op2 = p.createOperation("insertion_assign", n);
	int k;
	for (int i = 1; i < n;i++)
	{
		op2.count();
		int x = v[i];
		/*int j = i - 1;
		while (v[j] > x && j>=0)
		{
			v[j + 1] = v[j];
			j--;
		}*/
		//Am ales sa fac o cautare binara deoarece timpul se reduce de la O(n) la O(logn)
		int j= binary_search(v, n, 0, i, x);
		for (k = i;k >= j+1;k--)     
		{
			op2.count();
			v[k] = v[k-1];
		}
		op2.count();
		v[j] = x;

	}
}
void selection_sort(int v[], int n)
{
	Operation op1 = p.createOperation("selection_comp", n);
	Operation op2 = p.createOperation("selection_assign", n);
	int i_min, aux;
	for (int i = 0;i < n;i++)
	{
		i_min = i;
		for (int j = i + 1;j < n;j++)
		{
			op1.count();
			if (v[j] < v[i_min])
			{
				i_min = j;
			}
		}
		if (i_min != i)
		{
			op2.count(3);
			aux = v[i];
			v[i] = v[i_min];
			v[i_min] = aux;
		}
	}
}
void afisare(int v[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", v[i]);
	printf("\n");
}
void demo()
{
	int v[] = { 7, 5, 1, 2, 6, 4, 9 };
	int n = sizeof(v) / sizeof(v[0]);
	int u[100];
	memcpy(u, v, sizeof(v));
	printf("Sirul initial:");
	afisare(u, n);
	bubble_sort(u, n);
	printf("\nBubble sort:");
	afisare(u, n);
	memcpy(u, v, sizeof(v));
	printf("\nSirul initial:");
	afisare(u, n);
	insertion_sort(u, n);
	printf("\nInsertion sort:");
	afisare(u, n);
	printf("\nSirul initial:");
	afisare(v, n);
	selection_sort(v, n);
	printf("\nSelection sort:");
	afisare(v, n);

}
void perform_avg()
{
	int v[10000];
	int u[10000];
	for (int n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(v, n);//2-descresc 1-cresc
		memcpy(u, v, n * sizeof(v[0]));
		bubble_sort(u, n);
		memcpy(u, v, n*sizeof(v[0]));
		insertion_sort(u, n);
	    selection_sort(v, n);
	}
	p.addSeries("bubble_average", "bubble_comp", "bubble_assign");//pt toate sortarile
	p.addSeries("insertion_average", "insertion_comp", "insertion_assign");
	p.addSeries("selection_average", "selection_comp", "selection_assign");

	p.createGroup("comparatii_average", "bubble_comp", "insertion_comp", "selection_comp");
	p.createGroup("asignari_average", "bubble_assign", "insertion_assign", "selection_assign");
	p.createGroup("algoritmi_sortare_average", "bubble_average", "insertion_average", "selection_average");


	p.showReport();
}
void perform_best()
{
	int v[10000];
	int u[10000];
	for (int n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(v, n,10,50000,false,1);
		memcpy(u, v, n * sizeof(v[0]));
		bubble_sort(u, n);
		memcpy(u, v, n * sizeof(v[0]));
		insertion_sort(u, n);
		selection_sort(v, n);
	}
	p.addSeries("bubble_best", "bubble_comp", "bubble_assign");
	p.addSeries("insertion_best", "insertion_comp", "insertion_assign");
	p.addSeries("selection_best", "selection_comp", "selection_assign");

	p.createGroup("comparatii_best", "bubble_comp", "insertion_comp", "selection_comp");
	p.createGroup("asignari_best", "bubble_assign", "insertion_assign", "selection_assign");
	p.createGroup("algoritmi_sortare_best", "bubble_best", "insertion_best", "selection_best");

	p.showReport();
}
void perform_worst()
{
	int v[10000];
	int u[10000];
	for (int n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(v, n, 10, 50000, false, 2);
		memcpy(u, v, n * sizeof(v[0]));
		bubble_sort(u, n);
		memcpy(u, v, n * sizeof(v[0]));
		insertion_sort(u, n);
		selection_sort(v, n);
	}
	p.addSeries("bubble_worst", "bubble_comp", "bubble_assign");
	p.addSeries("insertion_worst", "insertion_comp", "insertion_assign");
	p.addSeries("selection_worst", "selection_comp", "selection_assign");

	p.createGroup("comparatii_worst", "bubble_comp", "insertion_comp", "selection_comp");
	p.createGroup("asignari_worst", "bubble_assign", "insertion_assign", "selection_assign");
	p.createGroup("algoritmi_sortare_worst", "bubble_worst", "insertion_worst", "selection_worst");

	p.showReport();

}
int main()
{
	demo();
	printf("\nAverage case:");
	perform_avg();
	printf("\nBest case:");
	perform_best();
	printf("\nWorst case:");
	perform_worst();

	return 0;
}

