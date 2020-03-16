/*Nume:Popa Alexandra
Grupa:30224
Tema_lab2:Construire Heap si HeapSort
Observatii:
			Construire Heap buttom-up:O(n)
									 -Algoritmul utilizeaza doua functii BUILD_MAX_HEAP_BU si MAX_HEAPIFY;
									-MAX_HEAPIFY:- mentine proprietatea de Heap (sau o creaza) a unui arbore;
												-functia compara nodurile copil cu nodul parinte si gaseste maximul dintre cele 3 noduri;
												-daca maximul este chiar nodul parinte functia se termina,
												in caz contrar se interschimba nodul parinte cu nodul maxim si se verifica proprietatea de Heap 
												in continuare pt urmatorii subarbori;
									-BUILD_MAX_HEAP_BU:-apeleaza functia MAX_HEAPIFY pt. jumatate din nodurile din vector,adica pt. nodurile care nu sunt frunze;
									-Pt. cele mai multe noduri se fac deplasarile cele mai scurte.
			Construire Heap top-down:O(nlogn)
									-Utilizeaza functiile BUILD_MAX_HEAP_TD si MAX_HEAP_INSERT;
									- MAX_HEAP_INSERT:-insereaza un nod ca frunza si verifica conditia de Heap;
													   -in cazul in care conditia nu este indeplinita, deplaseaza nodul de jos in sus pana la gasirea pozitiei potrivite;
									- BUILD_MAX_HEAP_TD:-insereaza elementele unui vector in Heap prin apelarea functiei MAX_HEAP_INSERT;
								    -Pt. cele mai putine noduri de fac cele mai lungi deplasari.
			Heap-Sort:O(nlogn);
					Stabilitate:NU;
					-foloseste buttom-up pt. contruirea Heap-lui deoarece este o metoda mai eficienta decat top-down;
			Cele doua metode de constructie a heap-ului creaza heap-uri diferite dar care respecta proprietatea acestor arbori.
			Meoda mai eficienta este buttom-up(complexitate de O(n))in comparatie cu top-down(complexitate O(nlogn));
			In worst_case, se observa din graficul generat ca algoritmii sunt liniari si ca metoda buttom_up este mult mai eficienta decat metoda top_down.
			In average_caze, numarul operatiilor efectuate este redus,iar metoda buttom_up ramane mai eficienta ca top_down.
			
		
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Profiler.h"
Profiler p("lab2");
int heap_size;

void MAX_HEAPIFY(int v[], int n,int i)
{
	Operation op1 = p.createOperation("build_BU", n);


	int largest;
	int aux;
	int l = 2*i+1; 
	int r = 2*i + 2;
	op1.count();
	if (l<n && v[l]>v[i])
		largest = l;
	else largest = i;
	op1.count();
	if (r<n && v[r]>v[largest])
		largest = r;
	if (largest != i)
	{
		op1.count(3);
		aux = v[i];
		v[i] = v[largest];
		v[largest] = aux;
		MAX_HEAPIFY(v, n, largest);
	}

}
void BUILD_MAX_HEAP_BU(int v[], int n)     
{

	for (int i = n / 2 - 1;i >= 0;i--)
		MAX_HEAPIFY(v,n, i);
}
void HEAP_SORT(int v[], int n)
{
	int aux;
	BUILD_MAX_HEAP_BU(v, n);
	for (int i = n - 1;i >=0;i--)
	{
		aux = v[0];
		v[0] = v[i];
		v[i] = aux;
		MAX_HEAPIFY(v, i, 0);
	}
}
void MAX_HEAP_INSERT(int v[],int n, int x)
{
	Operation op1 = p.createOperation("build_TD", n);

	int aux,i;
	heap_size++;
	i = heap_size-1;
	op1.count();
	v[i] = x;
	while (i > 0 && v[(i - 1) / 2]<v[i])
	{
		op1.count();
		aux = v[i];
		v[i] = v[(i - 1) / 2];
		v[(i - 1) / 2] = aux;
		op1.count(3);
		i = (i - 1) / 2;
	}
	if (i > 0) op1.count();
}
void BUILD_MAX_HEAP_TD(int v[], int n)
{

	heap_size = 1;
	for (int i = 1;i < n;i++)
		MAX_HEAP_INSERT(v,n, v[i]);
}
void afisare(int v[], int n)
{
	for (int i = 0;i < n;i++)
		printf("%d ", v[i]);
}
void demo()
{

	int v[] = { 7, 5, 1, 2, 6, 4, 9 };
	//int v[] = { 7, 6,5,4,3,2,1};
	//int v[] = {1,2,3,4,5,6,7,8,9};
	int n = sizeof(v) / sizeof(v[0]);
	int u[100];
	memcpy(u, v, sizeof(v));
	printf("Sirul initial:");
	afisare(v, n);
	printf("\nSirul construit buttom-up:");
	BUILD_MAX_HEAP_BU(u, n);
	afisare(u,n);
	memcpy(u, v, sizeof(v));
	printf("\nSirul initial:");
	afisare(v, n);
	printf("\nSirul sortat cu heap sort:");
	HEAP_SORT(u, n);
	afisare(u, n);
	memcpy(u, v, sizeof(v));
	printf("\nSirul initial:");
	afisare(v, n);
	printf("\nSirul construit top-down:");
	BUILD_MAX_HEAP_TD(u, n);
	afisare(u, n);

}
void average_case()
{
	int v[10000];
	int u[10000];
	for(int i=1;i<=5;i++)
		for (int n = 100;n <= 10000;n+=100)
		{
			FillRandomArray(v, n);
			memcpy(u, v, n * sizeof(v[0]));
			BUILD_MAX_HEAP_BU(u, n);
			BUILD_MAX_HEAP_TD(v, n);
		}
	

	p.createGroup("operatii_totale_averageCase", "build_BU", "build_TD");
	
	
	p.showReport();
}
void worst_case()
{
	int v[10000];
	int u[10000];
	for (int n = 100;n <= 10000;n += 100)
	{
		FillRandomArray(v, n, 10, 50000, false, 1);
		memcpy(u, v, n * sizeof(v[0]));
		BUILD_MAX_HEAP_BU(u, n);
		BUILD_MAX_HEAP_TD(v, n);
	}


	p.createGroup("operatii_totale_worstCase", "build_BU", "build_TD");


	p.showReport();
}
int main()
{
	//demo();
	//average_case();
	//worst_case();
	return 0;
}
