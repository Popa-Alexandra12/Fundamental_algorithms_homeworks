/*Nume:Popa Alexandra
Grupa:30224
Tema_lab6:Statistici dinamice de ordine
Observatii:
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Profiler.h"


Profiler p6("lab6");

typedef struct node {
	int key;
	struct node*right;
	struct node*left;
	struct node*parent;
	int size;
}Node;

Node *root;

Node* build_tree(int v[], int n, int st, int dr,Operation op1)
{

	if (st > dr) return NULL;
	else {
		int m = (st + dr) / 2;
		Node *root = (Node*)malloc(sizeof(Node));
		root->size = dr-st + 1;
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		root->key = v[m];
		op1.count();
		root->left = build_tree(v, n, st, m - 1,op1);
		if (root->left!=NULL)
		{
			root->left->parent = root;
		}
		op1.count();
		root->right = build_tree(v, n, m + 1, dr,op1);
		if (root->right!=NULL)
		{
			root->right->parent = root;
		}
		return root;
	}
	
}
Node* os_select(Node *x, int i)
{
	int r = 0;
	if (root == NULL) r = 0;
	if (x->left != NULL)
	{
		 r = ((x->left)->size) + 1;
	}
	else r = 1;
	x->size--;
	if (i == r) return x;
	else {
		if (i < r) return os_select(x->left, i);
		else return os_select(x->right, i-r);
	}
}
Node* findMinim(Node* x, int n, Operation op1)
{
	Node* p = x;
	while (p->left != NULL) {
		op1.count(2);
		p->size--;
		p = p->left;
	}
	return p;
}

Node *os_delete(Node* del, int n,Operation op1)
{


	Node*p;
	if (del == NULL) return NULL;
	if (del->left == NULL && del->right == NULL)
	{
	
		if (del->parent->right != NULL) {
			if (del->parent->right == del)
			{
				del->parent->right = NULL;
				p = del->parent;
				op1.count();
				free(del);
				return p;
			}
		}
		if (del->parent->left != NULL) {
			if (del->parent->left == del)
			{
				del->parent->left = NULL;
				p = del->parent;
				op1.count();
				free(del);
				return p;
			}
		}
	}
	if (del->left == NULL)
	{
		p = del->right;
		p->parent = del->parent;
		op1.count();
		if (del->parent != NULL)
		{
			op1.count();
			if (del->parent->left == del)
			{
				del->parent->left = p;
				op1.count();
			}
			op1.count();
			if (del->parent->right == del)
			{
				del->parent->right = p;
				op1.count();
			}
		}
		else {
			root = p;
			op1.count();
		}
		free(del);
		return p;

	}
	 
	else if (del->right == NULL)
		{
			p = del->left;
			p->parent = del->parent;
			op1.count(2);
			if (del->parent != NULL)
			{
				op1.count();
				if (del->parent->left == del)
				{
					del->parent->left = p;
					op1.count();
				}
				op1.count();
				if (del->parent->right == del)
				{
					del->parent->right = p;
					op1.count();
				}
			}
			else {
				root = p;
				op1.count();
			}
			free(del);
			return p;

		}
	else {
		p = findMinim(del->right, n,op1);
		op1.count();
		del->key = p->key;
		del = os_delete(p, n,op1);
		return  del;
	}
	return del;

	
}

void pprint(Node *nod, int level)
{
	
		if (nod->left != NULL)
		{
			pprint(nod->left, level + 1);
		}
		for (int i = 0;i < level;i++)
		{
			printf("    ");
		}
		printf("(%d %d)\n", nod->key, nod->size);
		if (nod->right != NULL)
		{
			pprint(nod->right, level + 1);

		}
	
}

void demo()
{
	Operation op1 = p6.createOperation("op_tree", 11);

	root = NULL;
	int v[11] = { 2,4,6,8,10,12,14,16,18,20,22 };
	root = build_tree(v, 10, 0, 10,op1);
	pprint(root, 0);
	Node *n;

	n = os_select(root, 2);
	if (n == NULL) printf("Elementul nu a fost gasit.");
	else {
		printf("Elementul cu a %d-a cea mai mica cheie este:%d.\n", 2, n->key);
		os_delete(n, 11,op1);
		pprint(root, 0);
	}

	n = os_select(root, 3);
	if (n == NULL) printf("Elementul nu a fost gasit.");
	else {
		printf("Elementul cu a %d-a cea mai mica cheie este:%d.\n", 3, n->key);
		os_delete(n, 11,op1);
		pprint(root, 0);
	}

	n = os_select(root, 7);
	if (n == NULL) printf("Elementul nu a fost gasit.");
	else {
		printf("Elementul cu a %d-a cea mai mica cheie este:%d.\n", 7, n->key);
		os_delete(n, 11,op1);
		pprint(root, 0);
	}

	n = os_select(root, 4);
	if (n == NULL) printf("Elementul nu a fost gasit.");
	else {
		printf("Elementul cu a %d-a cea mai mica cheie este:%d.\n", 4, n->key);
		os_delete(n, 11,op1);
		pprint(root, 0);
	}
	
	

}
void perform()
{

	root = NULL;
	int v[10000];
	for (int n = 100;n <= 10000;n+= 100) 
	{
		Operation op1 = p6.createOperation("op_tree", n);
		FillRandomArray(v, n, 1, 50000, true, 1);
		root = build_tree(v, n, 0, n - 1,op1);
		int s = n;
		while (s > 1)
		{
			int random = rand() % (s) + 1;
			Node*p = os_select(root, random);
			os_delete(p, n,op1);
			s--;
		}
		free(root);
		

	}

	p6.createGroup("perform", "op_tree");
	p6.showReport();
}
int main()
{
	demo();
	perform();
}