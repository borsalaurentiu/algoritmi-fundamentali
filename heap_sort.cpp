/*Pentru verificarea corectitudinii algoritmului de sortare HeapSort si a constituirii 
structurii de date Heap Bottom-Up am folosit in functia verificareAlgoritm un sir de 
10 elemente, preluat din "Introduction to Algorithms".

Sursele de inspiratie pentru pseudocod sau chiar si pentru codul algoritmilor au fost:
"Introduction to Algorithms"
http://www.worldit.info/files/Studiu%20asupra%20algoritmilor%20de%20sortare.pdf
https://www.geeksforgeeks.org/heap-sort/

Am reusit sa scriu algoritmul pentru constituirea structurii de date Heap Bottom-Up.
Am comentat codul pentru afisarea graficelor si generarea sirurilor pentru comparare.*/


#include <stdio.h>
#include "profiler.h"
#define MAX_SIZE 10000

Profiler profiler("Tema 2");

void swap(int *a, int *b)
{
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

int left(int i)
{
	return (2 * i + 1);
}

int right(int i)
{
	return (2 * (i + 1));
}

void reconstituieHeap(int a[], int n, int i)
{
	int maxim;
	int stanga, dreapta;
	stanga = left(i);
	dreapta = right(i);

	maxim = i;
	profiler.countOperation("ReconstituieHeap: Numar de comparatii", n);
	profiler.countOperation("ReconstituieHeap: Numar de comparatii si asignari", n);
	if (stanga < n && a[stanga] > a[maxim])
		maxim = stanga;

	profiler.countOperation("ReconstituieHeap: Numar de comparatii", n);
	profiler.countOperation("ReconstituieHeap: Numar de comparatii si asignari", n);
	if (dreapta < n && a[dreapta] > a[maxim])
		maxim = dreapta;

	profiler.countOperation("ReconstituieHeap: Numar de comparatii", n);
	profiler.countOperation("ReconstituieHeap: Numar de comparatii si asignari", n);
	if (i != maxim)
	{
		profiler.countOperation("ReconstituieHeap: Numar de comparatii si asignari", n, 3);
		profiler.countOperation("ReconstituieHeap: Numar de asignari", n, 3);
		swap(&a[i], &a[maxim]);
		reconstituieHeap(a, n, maxim);
	}
}

void heapSort(int *a, int n)
{
	int i;
	for (i = n / 2 - 1; i >= 0; i--)
		reconstituieHeap(a, n, i);
	for (i = n - 1; i >= 0; i--)
	{
		profiler.countOperation("HeapSort: Numar de comparatii si asignari", n, 3);
		profiler.countOperation("HeapSort: Numar de asignari", n, 3);
		swap(&a[0], &a[i]);
		reconstituieHeap(a, i, 0);
	}
}


void bottomUp(int *a, int n) {
	int i;
	for (i = (n - 1) / 2; i >= 0; i--) {
		reconstituieHeap(a, n, i);
	}
}



void afiseaza(int *a, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

void verificareAlgoritm(int n) {
	/*int i;
	int a[MAX_SIZE], b[MAX_SIZE];
	for (i = 0; i < n; i++) {
	a[i] = rand() % 100 + 1;
	b[i] = a[i];
	}*/
	int c[10] = { 4,1, 3, 2, 16, 9, 10, 14, 8, 7 };
	bottomUp(c, n);
	afiseaza(c, n);
	heapSort(c, n);
	afiseaza(c, n);
}

int main() {
	verificareAlgoritm(10);
	int i,j;
	int v[MAX_SIZE], v1[MAX_SIZE], v2[MAX_SIZE];
	
	for (i = 100; i < 5000; i += 100) {
		FillRandomArray(v, i, 1, 100000, false, 0);
		for (j = 0; j < i; j++) 
		{
			v2[j] = v[j];		
			v1[j] = v[j];
		}
		heapSort(v, i);
		bottomUp(v1, i);
		//topDown(v2, i);

	}
	
	profiler.showReport();
	return 0;


}