#include <stdio.h>
#include <stdlib.h>

struct node {
	int key;
	int rank;
	node *p;
} *noduri[11];

node* MAKE_SET(int x)
{
	node *p = (node*)malloc(sizeof(node));
	p->key = x;
	p->rank = 0;
	p->p = p;
	return p;
}

node* FIND_SET(node *x)
{
	if (x != x->p)
		x->p = FIND_SET(x->p);
	return x->p;
}

void UNION(node *x, node*y)
{
	if (x->rank == y->rank)
	{
		y->p = x;
		x->rank++;
		while (x != x->p)
		{
			x = x->p;
			x->p->rank = x->rank + 1;
		}
	}
	else
	{
		if (x->rank > y->rank)
			y->p = x;
		else
			x->p = y;
	}
}

int main()
{
	int i;
	for (i = 1; i <= 10; i++)
		noduri[i] = MAKE_SET(i);

	printf("Noduri dupa MAKE_SET:\n");
	for (i = 1; i <= 10; i++) 
	{
		printf("P%d, N%d, R%d     ", noduri[i]->p->key, noduri[i]->key, noduri[i]->rank);
	}
	printf("\n\n");

	UNION(noduri[1], noduri[2]);                 //   1   4   5   8   10
	UNION(noduri[2], noduri[3]);                 //   2       6   9
	UNION(noduri[5], noduri[6]);                 //   3       7
	UNION(noduri[6], noduri[7]);
	UNION(noduri[8], noduri[9]);
	printf("Noduri dupa primele legaturi:\n");
	for (i = 1; i <= 10; i++)
	{
		printf("P%d, N%d, R%d     ", noduri[i]->p->key, noduri[i]->key, noduri[i]->rank);
	}
	printf("\n\n");

	UNION(noduri[1], noduri[8]);                 //     1          5                     1
	UNION(noduri[5], noduri[4]);                 //   2   8      6 4 10  ->         2   8     5
	UNION(noduri[5], noduri[10]);                //   3   9      7                  3   9   6 4 10
	UNION(noduri[1], noduri[5]);                 //                                         7
	printf("Noduri dupa ultimele legaturi:\n");
	for (i = 1; i <= 10; i++)
	{
		printf("P%d, N%d, R%d     ", noduri[i]->p->key, noduri[i]->key, noduri[i]->rank);
	}
	printf("\n\n");

	FIND_SET(noduri[3]);                         //          1
	FIND_SET(noduri[9]);                         //   2 3 8 9   5    6 7
	FIND_SET(noduri[7]);						 //            4 10  
	printf("Noduri dupa FIND_SET:\n");
	for (i = 1; i <= 10; i++)
	{
		printf("P%d, N%d     ", noduri[i]->p->key, noduri[i]->key);
	}
	printf("\n\n");

	system("pause");
	return 0;
}
