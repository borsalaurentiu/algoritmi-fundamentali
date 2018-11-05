#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Profiler.h"

struct nodeT
{
	int key;
	int size;
	nodeT *stanga, *dreapta;
};

nodeT *Build_Tree(int st, int dr)
{
	if ((dr <= 0) || (st > dr))
	{
		return NULL;
	}
	else
	{
		nodeT *nod = (nodeT*)malloc(sizeof(nodeT));
		nod->key = (st + dr) / 2;
		nod->size = dr - st + 1;
		
		nod->stanga = Build_Tree(st, nod->key - 1);	
		nod->dreapta = Build_Tree(nod->key + 1, dr);
		return nod;
	}
}

nodeT *OS_SELECT(nodeT *root, int key)
{
	int i = root->stanga->size + 1;
	if (key == i)
		return root;
	if (key < i) 
		return OS_SELECT(root->stanga, key);
	else
		return OS_SELECT(root->dreapta, key - i);
}	

nodeT *succesor(nodeT *nod)
{
	nodeT *aux = (nodeT*)malloc(sizeof(nodeT));
	aux = nod;
	while (aux->stanga != NULL)
		aux = aux->stanga;
	return aux;
}

nodeT *OS_DELETE(nodeT *root, int key)
{
	if (root == NULL)
	{
		return root;
	}

	if(key < root->key)
	{
		root->size--;
		root->stanga = OS_DELETE(root->stanga, key);
	}
	else if (key > root->key)
	{
		root->size--;
		root->dreapta = OS_DELETE(root->dreapta, key);
	}
	else
	{
		root->size--;
		if (root->stanga == NULL)
		{
			nodeT *aux= (nodeT*)malloc(sizeof(nodeT));
			aux = root->dreapta;
			free(root);
			return aux;
		}
		else if (root->dreapta == NULL)
		{
			nodeT *aux = (nodeT*)malloc(sizeof(nodeT));
			aux = root->stanga;
			free(root);
			return aux;
		}
		nodeT *aux = (nodeT*)malloc(sizeof(nodeT));
		aux = succesor(root->dreapta);
		root->key = aux->key;
		root->dreapta = OS_DELETE(root->dreapta, aux->key);
	}
	return root;
}

void print(nodeT *nod, int n)
{
	int i;
	for (i = 1; i < n - nod->size; i++)
		printf("  ");
	printf("%d,%d\n", nod->key, nod->size);
}

void inorder(nodeT *nod, int n)
{
	if (nod != NULL)
	{
		inorder(nod->stanga, n);
		print(nod, n);
		inorder(nod->dreapta, n);
	}
}

void verificare()
{
	int n = 11, m = 1;
	nodeT *root = NULL;
	root = Build_Tree(1, n);
	printf("Nod %d, size %d\n\n\n", OS_SELECT(root, 9)->key, OS_SELECT(root, 9)->size);
	inorder(root, n);

	printf("\n\n\n\n");
	OS_DELETE(root, 9);
	n--;
	OS_DELETE(root, 11);
	n--;
	OS_DELETE(root, 8);
	n--;
	
	inorder(root, n);

}

int main()
{
	int n, i, random[3];
	bool continua;
	verificare();
	
	for (n = 100; n < 10000; n += 100) {
		for (i = 0; i < 5; i++) {
			nodeT *root = NULL;
			root = Build_Tree(1, n);
			
			continua = true;
			while (continua) {
				FillRandomArray(random, 3, 1, n, false, 0);
				if (random[0] != random[1] && random[0] != random[2] && random[1] != random[2])
					continua = false;
			}
			//printf("%d %d %d\n", random[0], random[1], random[2]);
			OS_SELECT(root, random[i]);
			OS_DELETE(root, random[i]);
		}
	}
	
	system("pause");

}
