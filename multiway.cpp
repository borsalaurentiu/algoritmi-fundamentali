#include <stdio.h>
#include <stdlib.h>

struct nodeT
{
	int key, size;
	nodeT **children;
} *root, *array[10];

struct nodeK
{
	int key;
	nodeK *child,*brother;
} *vector[10];

int pi[10] = { 0, 2, 7, 5, 2, 7, 7, -1, 5, 2 };

void nodNull()
{
	int i;
	for (i = 1; i < 10; i++)
	{
		vector[i] = (nodeK*)malloc(sizeof(nodeK));
		vector[i]->brother = NULL;
		vector[i]->child = NULL;
		vector[i]->key = i;
	}
}

void T1()
{
	int i;
	int piSize[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (i = 1; i < 10; i++)
		if (pi[i] != -1)
			piSize[pi[i]]++;
			
	for (i = 1; i < 10; i++)
	{
		array[i] = (nodeT*)malloc(sizeof(nodeT));
		array[i]->key = i;
		array[i]->size = 0;
		array[i]->children = (nodeT**)malloc(sizeof(nodeT*) * piSize[i]);
	}

	for (i = 1; i < 10; i++)
	{
		if (pi[i] == -1)
			root = array[i];
		else
		{
			array[pi[i]]->size++;
			array[pi[i]]->children[array[pi[i]]->size] = array[i];
		}
	}
}

void T2(nodeT *array) {
	int i;
	if (array != NULL)
	{
		for (i = 1; i <= array->size; i++)
		{
			if (i == 1)
				vector[array->key]->child = vector[array->children[i]->key];
			else
				vector[array->children[i - 1]->key]->brother = vector[array->children[i]->key];
			T2(array->children[i]);
		}
	}
}

void R1()
{
	int i, j;
	for (i = 1; i < 10; i++)
	{
		printf("Nod %d, copii: ", i);
		for (j = 1; j < 10; j++)
			if (pi[j] == array[i]->key)
				printf("%d ", j);
		printf("\n");
	}

	printf("\n\n\n");
}

void R2()
{
	int i;
	char brother[10] = { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' };
	char child[10] = { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' };

	for (i = 1; i < 10; i++)
	{
		if (vector[i]->brother != 0)
			brother[i] = vector[i]->brother->key + 48;
		if (vector[i]->child != 0)
			child[i] = vector[i]->child->key + 48;
		printf("Nod %d, frate %c, copil %c\n", vector[i]->key, brother[i], child[i]);
	}

	printf("\n\n\n");
}

void PrettyPrint(nodeT *nod, int n)
{
	int i;

	if (nod != NULL)
	{
		printf("\n");

		for (i = 1; i < n; i++)
			printf("   ");

		printf("%d", nod->key);
		n++;

		if (nod->size != 0)
			for (i = 1; i <= nod->size; i++)
				PrettyPrint(nod->children[i], n);
	}
}


void preorder(nodeK *nod, int n)
{
	int i;
	if (nod != NULL)
	{
		
		for (i = 1; i < n; i++)
			printf("   ");
		printf("%d\n", nod->key, n);
		n++;
		preorder(nod->child, n);
		
		preorder(nod->brother, n);

	}
}




int main()
{
	T1();
	R1();
	nodNull();
	T2(root);
	R2();
	PrettyPrint(root, 1);
	printf("\n\n\n");
	preorder(vector[7], 1);
	system("pause");
	return 0;
}




