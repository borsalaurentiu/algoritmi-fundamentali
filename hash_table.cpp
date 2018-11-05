#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

#define N 9973

int count = 0, c1 = 1, c2 = 1;

int Hash_Function(int k, int i) {
	int h;
	h = k + c1*i*i + c2*i;
	h = h % N;
	return h;
}

int Hash_Insert(int *T, int k) {
	int i = 0, j;
	do {
		j = Hash_Function(k, i);
		if (T[j] == -1) {
			T[j] = k;
			return j;
		}
		else {
			i++;
		}
	} while (i < N);
	return -1;
}

int Hash_Search(int *T, int k) {
	int i = 0, j;
	do {
		count++;
		j = Hash_Function(k, i);
		if (T[j] == k) {
			return 1;
		}
		else {
			i++;
		}
	} while ((T[j] != -1) && (i != N));
	return -1;
}

void Hash(int *T, int *gasite, int a) {
	int i;
	int v[N];// = (int*)malloc(N * sizeof(int));
	int random[1500];
	FillRandomArray(v, a, 1, 10000, false, 0);
	for (i = 0; i < a; i++) {
		Hash_Insert(T, v[i]);
	}
	
	FillRandomArray(random, 1500, 0, N-1, false, 0);
	for (i = 0; i < 1500; i++) {
		gasite[i] = T[random[i]];
	}
}

void initializare(int *T) {
	int i;
	for (i = 0; i < N; i++)
		T[i] = -1;
}

void afisare(int a) {
	int i, j;
	int gasite[1500], negasite[1500];
	int T[N];
	int gasitMediu = 0, gasitMaxim = 0, negasitMediu = 0, negasitMaxim = 0;
	FillRandomArray(negasite, 1500, 10001, 20000, false, 0);
	for (i = 0; i < 5; i++) {
		gasitMaxim = 0;
		negasitMaxim = 0;
		initializare(T);
		Hash(T, gasite, a);
		
		for (j = 0; j < 1500; j++) {
			count = 0;
			if ((Hash_Search(T, gasite[j])) == 1) {
				if ( count > gasitMaxim) {
					gasitMaxim = count;
				}
				gasitMediu += count;
			}
		}
		for (j = 0; j < 1500; j++) {
			count = 0;
			if ((Hash_Search(T, negasite[j])) == -1) {
				if (count > negasitMaxim) {
					negasitMaxim = count;
				}
				negasitMediu += count;
			}
		}
	}
	printf("%.2f\t\t %.2f\t\t %d\t\t %.2f\t\t %d\n", (double)a / N, (double) gasitMediu / (7500), gasitMaxim, (double) negasitMediu / (7500), negasitMaxim);
}

void verificare() {
	printf("VERIFICARE ALGORITM\n"); 
	int Verif[N] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int i, j;
	int m[8] = { 5, 15, 12, 8, 9, 14, 3, 7};
	for (i = 0; i < 8; i++) {	
		Hash_Insert(Verif, m[i]);
		for (j = 0; j < N; j++) {
			printf("H[%d] = %d; ", j, Verif[j]);
		}
		printf("\n");
	}

	for (i = 0; i < N; i++) {
		printf("H[%d] = %d; ", i, Verif[i]);
	}
	printf("\n");
	int y = 0;
	for (i = 0; i < N; i++) {
		count = 0;
		y = 0;
		if ((Hash_Search(Verif, m[i])) == 1) {
			if (count > y) {
				y = count;
			}
		}
		printf("Cauta %d: gasit dupa %d cautari.\n", m[i], y);
	}
}

void rezultate() {
	printf("Factor de\t Efort mediu\t Efort maxim\t Efort mediu\t Efort maxim\n");
	printf("umplere\t\t gasite\t\t gasite\t\t negasite\t negasite\n\n");

	int i;
	int a;
	double factor[5] = { 0.80, 0.85, 0.9, 0.95, 0.99 };
	
	for (i = 0; i < 5; i++) {
		a = (int) (factor[i] * N);
		afisare(a);
	}
}
int main()
{
	rezultate();
	//verificare();
	
	system("pause");
	return 0;
}