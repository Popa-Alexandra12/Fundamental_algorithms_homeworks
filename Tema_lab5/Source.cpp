/*Nume:Popa Alexandra
Grupa:30224
Tema_lab5:Tabele de dispersie
Observatii:
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Profiler.h"
#define MAX 10007

Profiler p5("lab5");

typedef struct {
	int id;
	char *nume;
} HASH_ELEMENT;

HASH_ELEMENT HT[MAX];

#define FNV_offset_basis 2166136261;
#define FNV_prime 16777619;
#define c1 2
#define c2 1
int gasite, negasite, sum_gasite, sum_negasite;
int max_gasite = INT_MIN; 
int max_negasite = INT_MIN;

unsigned h_function_FNV_1A(char *nume)
{
	unsigned hash = FNV_offset_basis;
	for (int i = 0;i < strlen(nume);i++)
	{
		hash = hash ^ nume[i];
		hash = hash * FNV_prime;
	}
	hash = hash >> 1;
	return hash;
}

int h_function(int id, int i)
{
	return(id + c1 * i + c2 * i* i) % MAX;
}

void insert(int id, char *nume)
{
	
	int i = 0;
	int j;
	
	
	do {
		if (nume != NULL)
		{
		
			j = h_function(h_function_FNV_1A(nume), i);
		}
		else j = h_function(id, i);

		if (HT[j].id == 0)
		{
			HT[j].id = id;
			HT[j].nume = nume;
			break;
		}
		else i++;

		} while (i <MAX);
	
}

HASH_ELEMENT * search(int id,char *nume)
{
	int i = 0;
	int j;
	do {
		j = h_function(h_function_FNV_1A(nume), i);
		if (HT[j].id == id)
		{
	
			return &HT[j];
		}
		i++;
	} while (HT[j].id != 0 && i < MAX);
	return NULL;
}
HASH_ELEMENT * search1(int id, char *nume)
{
	int i = 0;
	int j;
	do {
		j = h_function(id ,i);
		if (HT[j].id == id)
		{
			gasite = i + 1;
			sum_gasite += gasite;
			max_gasite = max(max_gasite, gasite);
			return &HT[j];
		}
		i++;
	} while (HT[j].id != 0 && i < MAX);
	negasite = i + 1;
	sum_negasite += negasite;
	max_negasite = max(max_negasite, negasite);
	return NULL;
}
void initializare_H_table()
{
	for (int i = 0;i < MAX ;i++)
	{
		HT[i].id = 0;
		HT[i].nume = NULL;
	}
}
void print_H_Table()
{
	for (int i = 0;i < MAX ;i++)
	{
		if (HT[i].id == 0)
		{
			printf("HT[%d]:0 NULL\n",i);
		}
		else printf("HT[%d]:ID:%d NUME:%s\n",i, HT[i].id,HT[i].nume);
	}
}
void demo()
{

	int v[] = {12,43,5,9,2,64,70,4,102,58,420};
	char s[][7] = { "ana","mara","dan","maria","stefan","adi","anca","ema","radu","gabi","diana" };
	initializare_H_table();
	for (int i = 0; i <sizeof(v)/sizeof(v[0]); i++) {
		insert(v[i],s[i]);
	}
	
	print_H_Table();

	HASH_ELEMENT *p = search(1,s[1]);
	if (p!=NULL) 
				printf("\nElementul %d a fost gasit",p->id);
				 else printf("\nElementul nu este gasit.");

	HASH_ELEMENT *q = search(102, s[8]);
	if (q != NULL)
		printf("\nElementul %d a fost gasit.", q->id);
	else printf("\nElementul nu este gasit.");
	
}
void perform()
{
	float alfa[5] = { 0.8,0.85,0.9,0.95,0.99 };
	int v[MAX + 2000];
	int k;
	int r,r1;
	srand(time(NULL));

	for (int i = 0; i < 5; i++) {
		initializare_H_table();
		max_gasite = INT_MIN;
		max_negasite = INT_MIN;
		sum_gasite = 0;
		sum_negasite = 0;
		FillRandomArray(v, MAX *alfa[i] + 1500, 10, 200000, true, 0);

		for (int j = 0; j < MAX *alfa[i]; j++) {
			insert(v[j], NULL);
		}
		for (int k = 0; k < 1500; k++) {
			//srand(time(NULL));
			r = v[ rand() % (int)(alfa[i] * MAX)];
			search1(r, NULL);
		}
		for (int s = alfa[i] * MAX; s < alfa[i] * MAX + 1500; s++) {
			search1(v[s], NULL);

		}

		printf("Factor de umplere %.2f \n", alfa[i]);
		printf("Efort mediu chei gasite %f \n", sum_gasite / 1500.0f);
		printf("Efort mediu chei negasite %f \n", sum_negasite / 1500.0f);
		printf("Efort maxim chei gasite %d\n", max_gasite);
		printf("Efort maxim chei negasite %d\n", max_negasite);
		printf("\n");

		
	}
}
int main()
{
	//demo();
	perform();
	return 0;
}