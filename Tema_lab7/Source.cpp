/*Nume:Popa Alexandra
Grupa:30224
Tema_lab7:Arbori multicai
Observatii:
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Profiler.h"


Profiler p7("lab7");

typedef struct node2 {
	int key;
	int nrChildren;
	struct node2 **children;
}Node2;


typedef struct node3 {
	int key;
	struct node3 *child;
	struct node3 *brother;
}Node3;

void pprint_node3(Node3 *nod, int level)
{
	
		if (nod != NULL) {
			for (int i = 0;i < level;i++) 
				printf("    ");
			printf("(%d)\n", nod->key);
			pprint_node3(nod->child, level + 1);
			printf("\n");
			pprint_node3(nod->brother, level);
		}



}
Node2* T1(int n,int parent[])
{
	Node2 *root = NULL;
	Node2 *tree = (Node2*)malloc(sizeof(Node2)*(n));  

	for (int i = 1;i <= n;i++)
	{
		tree[i].key = i;
		tree[i].nrChildren = 0;
		tree[parent[i]].children = (Node2**)malloc(sizeof(Node2*));
	}
	for (int i = 1;i <= n;i++)
	{
		
		if (parent[i] == -1)
		{
			root = &tree[i];
		}
		else {
			
			tree[parent[i]].children[tree[parent[i]].nrChildren]= (Node2*)malloc(sizeof(Node2));
			tree[parent[i]].children[tree[parent[i]].nrChildren] = &tree[i];
			tree[parent[i]].nrChildren++;
			//tree[parent[i]].key = parent[i];
		}
	}
	return root;


}
Node3* T3(Node2* root_n2)
{
	Node3* root_n3 = (Node3*)malloc(sizeof(Node3));
	root_n3->key = root_n2->key;
	root_n3->child =root_n3->brother = NULL;
	
	for (int i = 0;i < root_n2->nrChildren;i++)
	{
		Node3* p2;
		p2= T3(root_n2->children[i]);
		if (root_n3->child==NULL) {
			root_n3->child = p2;
		}
		else if (root_n3 != NULL)
		{
			Node3* p3 = root_n3->child;
			
			while (p3->brother != NULL)
			{
				p3 = p3->brother;
			}
			if (p3->brother == NULL) p3->brother = p2;
		}
		
	}
	return root_n3;

}
int main()
{
	int parent[10] = {0, 2, 7, 5, 2, 7, 7,-1,5,2 };
	Node2* p=T1(9, parent);
	Node3* q = T3(p);
	printf("Arbore binar:\n");
	pprint_node3(q, 0);
	return 0;
}