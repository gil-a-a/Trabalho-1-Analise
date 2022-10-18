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
//Insertion
void insertionSort(int *vet, int tam);

//Selection
void selectionSort(int *vet, int tam);

//Merge
void mergeSort(long long int *vetor, int comeco, int fim);
void intercala(long long int * , int , int , int );

//Heap
void maxHeapify(int *vet, int tam, int i);
void heapSort(int *vet, int tam);

//Quick
int partition(int *vet, int p, int r);
void quickSort(int *vet, int p, int r);
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
	long long int tam;
	long long int *vet;
	
	srand(time(NULL));
	
	printf("Insira o tamanho do vetor: ");
		scanf("%d", &tam);
	
	
	vet = geraVetor(tam);
	printf("\nVetor gerado: ");
	printaVetor(vet, tam);
	
	printf("\nVetor organizado: ");
//	insertionSort(vet, tam);
//	selectionSort(vet, tam);
    int p = vet[0];
    mergeSort(vet, 0, tam - 1);
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
//Insertion
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

//Selection
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
void intercala(long long int *vetor, int comeco, int meio, int fim) {
	int temp[fim - comeco + 1];
	int pos = 0, pos_comeco = comeco, pos_final = meio + 1;
   
	while (pos_comeco <= meio && pos_final <= fim){
    	if (vetor[pos_comeco] < vetor[pos_final]){
        	temp[pos++] = vetor[pos_comeco++];
    	}
    	else{
        	temp[pos++] = vetor[pos_final++];
    	}
	}

	while (pos_comeco <= meio){
		temp[pos++] = vetor[pos_comeco++];
	}

	while (pos_final <= fim){
		temp[pos++] = vetor[pos_final++];
	}

   int i;
   for (i = 0; i < pos; i++){
      vetor[i + comeco] = temp[i];
   }
   return;
}

void mergeSort(long long int *vetor, int comeco, int fim){
    int meio = (fim+comeco)/2;
	if (comeco < fim) {
        mergeSort(vetor, comeco, meio);
        mergeSort(vetor, meio+1, fim);
        intercala(vetor, comeco, meio, fim);
    }
}

//Heap
void maxHeapify(int *vet, int tam, int i)
{
	int aux;
    int maior = i;
    int e = 2*i + 1;
    int d = 2*i + 2;
 
    if (e < tam && vet[e] > vet[maior]){
    	maior = e;
	}
 
    if (d < tam && vet[d] > vet[maior]){
    	maior = d;
	}
 
    if (maior != i) {
    	aux = vet[i];
    	vet[i] = vet[maior];
    	vet[maior] = aux;
    	
        maxHeapify(vet, tam, maior);
    }
}

void heapSort(int *vet, int tam)
{
	int i, aux;
	
    for (i = tam/2 - 1; i >= 0; i--) {
    	maxHeapify(vet, tam, i);
	}
	
	for (i = tam - 1; i >= 0; i--) {
    	aux = vet[0];
    	vet[0] = vet[i];
    	vet[i] = aux;
 
        maxHeapify(vet, i, 0);
	}
}

//Quick
int partition(int *vet, int p, int r)
{
	int aux;
	int x = vet[r]; // pivô
	int i = p-1, j;

	for (j = p; j <= r-1; j++){
		if (vet[j] < x) {
			i++;
			aux = vet[i];
			vet[i] = vet[j];
			vet[j] = aux;
		}
	}
	
	aux = vet[i + 1];
	vet[i + 1] = vet[r];
	vet[r] = aux;
	
	return i + 1;
}

void quickSort(int *vet, int p, int r)
{
	int q;
	
	if (p < r) {
		q = partition(vet, p, r);	
		quickSort(vet, p, q-1);
		quickSort(vet, q+1, r);
	}
}
//===================================//
