#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct dados_da_amostra{
	int num_trocas;
	double tempo_de_execucao; //n sei se precisa mudar o tipo pra clock_t, ent tem q ver isso dps
};

int* geraVetor(int tam);
void printaVetor(int *vet, int tam);
//============== Sorts ==============//
void insertionSort(int *vet, int tam);
void selectionSort(int *vet, int tam);
//Merge
//Heap
//Quick
//===================================//
double calculaMedia(int *valores, int tam)
{
	int i;
	double media = 0;
	for (i = 0; i < tam; i++)
		media += valores[i];
	media /= tam;
}


int main ()
{
	int tam;
	int *vet;
	
	srand(time(NULL));
	
	printf("Insira o tamanho do vetor: ");
		scanf("%d", &tam);
	
	
	vet = geraVetor(tam);
	printf("\nVetor gerado: ");
	printaVetor(vet, tam);
	
	printf("\nVetor organizado: ");
//	insertionSort(vet, tam);
//	selectionSort(vet, tam);
	mergeSort(vet, tam);
	printaVetor(vet, tam);
	
	return 0;
}

int* geraVetor(int tam)
{
	int i;
	int *vet = (int *) malloc(sizeof(int)*tam);
		
	for (i = 0; i < tam; i++)
		vet[i] = rand() % 100;
	
	return vet;
}

void printaVetor(int *vet, int tam)
{
	int i;
	for (i = 0; i < tam; i++)
		printf("%d ", vet[i]);
}

//============== Sorts ==============//
void insertionSort(int *vet, int tam)
{
	int i, j, chave;
	
	for (i = 1; i < tam; i++){
		chave = vet[i];
		j = i - 1;
		while (j >= 0 && vet[j] > chave){
			vet[j+1] = vet[j];
			j = j-1;
		}
		
		vet[j + 1] = chave;
	}
}
void selectionSort(int *vet, int tam)
{
	int i, j, min, aux;
	
	for (i = 0; i < tam-1; i++){
		min = i;
		for (j = i+1; j < tam; j++){
			if (vet[j] < vet[min]){
				min = j;
			}
		}
		aux = vet[i];	
		vet[i] = vet[min];
		vet[min] = aux;
	}
}

//Merge
//Heap
//Quick
//===================================//

