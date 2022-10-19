#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct dados_da_amostra{
	double tempo_de_execucao;
	long long int num_trocas;
	long long int num_comparacoes;
}Dados;

typedef struct estatisticas{
	double media;
	double variancia;
	double desvio_padrao;
}Estats;

struct dados_sort{
	Estats tempo_de_execucao;
	Estats num_trocas;
	Estats num_comparacoes;
};

int* geraVetor(long int tam);
void printaVetor(int *vet, long int tam);
//============== Sorts ==============//
//Insertion
void insertionSort(int *vet, long int tam, struct dados_da_amostra *dado);

//Selection
void selectionSort(int *vet, int long tam, struct dados_da_amostra *dado);

//Merge
void mergeSort(int *vet, int comeco, int fim, struct dados_da_amostra *dados);
void intercala(int *vet, int comeco, int meio, int fim, struct dados_da_amostra *dados);

//Heap
void maxHeapify(int *vet, long int tam, int i, struct dados_da_amostra *dados);
void heapSort(int *vet, long int tam, struct dados_da_amostra *dados);

//Quick
int partition(int *vet, int p, long int r, struct dados_da_amostra *dados);
void quickSort(int *vet, int p, long int r, struct dados_da_amostra *dados);
//===================================//

struct dados_sort calculaEstatisticas(struct dados_da_amostra* dados, int tamAmostra)
{
	struct dados_sort estats;
    int i;
    for(i = 0; i < tamAmostra; i++) {
        printf("n_comp[%d]: %d\n\n", i, dados[i].num_comparacoes);
    }
	
    estats.tempo_de_execucao.media = 0;
    estats.tempo_de_execucao.desvio_padrao = 0;
    estats.tempo_de_execucao.variancia = 0;
    estats.num_trocas.media = 0;
    estats.num_trocas.desvio_padrao = 0;
    estats.num_trocas.variancia = 0;
    estats.num_comparacoes.media = 0;
    estats.num_comparacoes.desvio_padrao = 0;
    estats.num_comparacoes.variancia = 0;
    
    for(i = 0; i < tamAmostra; i++) {
        /* ************ MEDIA ************* */
        //printf("dados[%d].")
        estats.tempo_de_execucao.media += dados[i].tempo_de_execucao;

        estats.num_trocas.media += dados[i].num_trocas;

        estats.num_comparacoes.media += dados[i].num_comparacoes;
    }

    estats.tempo_de_execucao.media /= tamAmostra;
    estats.num_trocas.media /= tamAmostra;
    estats.num_comparacoes.media /= tamAmostra;

    for(i = 0; i < tamAmostra; i++) {
        /* ************ VARIANCIA E DESVIO ************* */
        estats.tempo_de_execucao.variancia += pow((dados[i].tempo_de_execucao - estats.tempo_de_execucao.media), 2);

        estats.num_trocas.variancia += pow((dados[i].num_trocas - estats.num_trocas.media), 2);
        
        estats.num_comparacoes.variancia += pow((dados[i].num_comparacoes - estats.num_comparacoes.media), 2);
        }
    estats.tempo_de_execucao.variancia /= (tamAmostra - 1);
    estats.tempo_de_execucao.desvio_padrao = sqrt(estats.tempo_de_execucao.variancia);

    estats.num_trocas.variancia /= (tamAmostra - 1);
    estats.num_trocas.desvio_padrao = sqrt(estats.num_trocas.variancia);

    estats.num_comparacoes.variancia /= (tamAmostra - 1);
    estats.num_comparacoes.desvio_padrao = sqrt(estats.num_comparacoes.variancia);
    

	return estats;
}

void printaEstats(struct dados_sort dados)
{
	printf("[Tempo de exec]\n");
	printf("Media: %f\n", dados.tempo_de_execucao.media);
	printf("Variancia: %f\n", dados.tempo_de_execucao.variancia);
	printf("DP: %f\n", dados.tempo_de_execucao.desvio_padrao);
	
	printf("[N trocas]\n");
	printf("Media: %f\n", dados.num_trocas.media);
	printf("Variancia: %f\n", dados.num_trocas.variancia);
	printf("DP: %f\n", dados.num_trocas.desvio_padrao);
	
	printf("[N comparas]\n");
	printf("Media: %f\n", dados.num_comparacoes.media);
	printf("Variancia: %f\n", dados.num_comparacoes.variancia);
	printf("DP: %f\n", dados.num_comparacoes.desvio_padrao);
	
}

int main ()
{
	int *vet;
	long int tam;

    clock_t tempo1_merge, tempo2_merge;
    clock_t tempo1_heap, tempo2_heap;
    clock_t tempo1_quick, tempo2_quick;

    srand(time(NULL));

    FILE* fp_insertion = fopen("insertion.txt", "w+");
    FILE* fp_selection = fopen("selection.txt", "w+");
    FILE* fp_merge = fopen("merge.txt", "w+");
    FILE* fp_heap = fopen("heap.txt", "w+");
    FILE* fp_quick = fopen("quick.txt", "w+");
	
	printf("Insira o tamanho do vetor: ");
		scanf("%d", &tam);

    int nAmostras;

    printf("Entre com o nÃºmero de amostras: ");
        scanf("%d", &nAmostras);

    int i;
    struct dados_da_amostra* dados_insertion = (struct dados_da_amostra*) malloc(sizeof(struct dados_da_amostra)*nAmostras);
    for(i = 0; i < nAmostras; i++) {
        dados_insertion[i].num_comparacoes = 0;
        dados_insertion[i].num_trocas = 0;
        dados_insertion[i].tempo_de_execucao = 0;
    }

    struct dados_da_amostra* dados_selection = (struct dados_da_amostra*) malloc(sizeof(struct dados_da_amostra)*nAmostras);
    for(i = 0; i < nAmostras; i++) {
        dados_selection[i].num_comparacoes = 0;
        dados_selection[i].num_trocas = 0;
        dados_selection[i].tempo_de_execucao = 0;
    }

    struct dados_da_amostra* dados_merge = (struct dados_da_amostra*) malloc(sizeof(struct dados_da_amostra)*nAmostras);
    for(i = 0; i < nAmostras; i++) {
        dados_merge[i].num_comparacoes = 0;
        dados_merge[i].num_trocas = 0;
        dados_merge[i].tempo_de_execucao = 0;
    }
    struct dados_da_amostra* dados_heap = (struct dados_da_amostra*) malloc(sizeof(struct dados_da_amostra)*nAmostras);
    for(i = 0; i < nAmostras; i++) {
        dados_heap[i].num_comparacoes = 0;
        dados_heap[i].num_trocas = 0;
        dados_heap[i].tempo_de_execucao = 0;
    }
    struct dados_da_amostra* dados_quick = (struct dados_da_amostra*) malloc(sizeof(struct dados_da_amostra)*nAmostras);
    for(i = 0; i < nAmostras; i++) {
        dados_quick[i].num_comparacoes = 0;
        dados_quick[i].num_trocas = 0;
        dados_quick[i].tempo_de_execucao = 0;
    }

    for (i = 0; i < nAmostras; i++) {
		printf("Amostra %d\n", i+1);        
        //printf("\n **************** INSERTION **************** \n");
        vet = geraVetor(tam);
	    printf("\n\nVetor gerado: ");
	    //printaVetor(vet, tam);

		printf("Insertion comecou\n");
        
		insertionSort(vet, tam, &dados_insertion[i]);

        printf("\n\nVetor organizado: ");
        //printaVetor(vet, tam);
        printf("\n\ntempo: %f\nnum comp: %d\ntrocas: %d\n", dados_insertion[i].tempo_de_execucao, dados_insertion[i].num_comparacoes, dados_insertion[i].num_trocas);
        
        //printf("\n **************** SELECTION **************** \n");
        vet = geraVetor(tam);
	    printf("\n\nVetor gerado: ");
	    //printaVetor(vet, tam);

        printf("Selection comecou\n");
        
		selectionSort(vet, tam, &dados_selection[i]);

        printf("\n\nVetor organizado: ");
        //printaVetor(vet, tam);
        printf("\n\ntempo: %f\nnum comp: %d\ntrocas: %d\n", dados_selection[i].tempo_de_execucao, dados_selection[i].num_comparacoes, dados_selection[i].num_trocas);
        
        //printf("\n **************** MERGE **************** \n");
        vet = geraVetor(tam);
	    printf("\n\nVetor gerado: ");
	    //printaVetor(vet, tam);
	    
		printf("Merge comecou\n");
        
		tempo1_merge = clock();
        mergeSort(vet, 0, tam - 1, &dados_merge[i]);
        tempo2_merge = clock();
        dados_merge[i].tempo_de_execucao = (double)(tempo2_merge - tempo1_merge)/CLOCKS_PER_SEC;

        printf("\n\nVetor organizado: ");
        //printaVetor(vet, tam);
        printf("\n\ntempo: %f\nnum comp: %d\ntrocas: %d\n", dados_merge[i].tempo_de_execucao, dados_merge[i].num_comparacoes, dados_merge[i].num_trocas);
        
        //printf("\n **************** HEAP **************** \n");
        vet = geraVetor(tam);
	    printf("\n\nVetor gerado: ");
	    //printaVetor(vet, tam);
	    
		printf("Heap comecou\n");
        
		tempo1_heap = clock();
        heapSort(vet, tam, &dados_heap[i]);
        tempo2_heap = clock();
        dados_heap[i].tempo_de_execucao = (double)(tempo2_heap - tempo1_heap)/CLOCKS_PER_SEC;

        printf("\n\nVetor organizado: ");
        //printaVetor(vet, tam);
        printf("\n\ntempo: %f\nnum comp: %d\ntrocas: %d\n", dados_heap[i].tempo_de_execucao, dados_heap[i].num_comparacoes, dados_heap[i].num_trocas);
        
        //printf("\n **************** QUICK **************** \n");
        
        vet = geraVetor(tam);
	    printf("\n\nVetor gerado: ");
	    //printaVetor(vet, tam);
		
		printf("Quick comecou\n");
        tempo1_quick = clock();
        quickSort(vet, 0, tam-1, &dados_quick[i]);
        tempo2_quick = clock();
        dados_quick[i].tempo_de_execucao = (double)(tempo2_quick - tempo1_quick)/CLOCKS_PER_SEC;

        printf("\n\nVetor organizado: ");
        //printaVetor(vet, tam);
        printf("\n\ntempo: %f\nnum comp: %d\ntrocas: %d\n", dados_quick[i].tempo_de_execucao, dados_quick[i].num_comparacoes, dados_quick[i].num_trocas);
        
    }

    for(i = 0; i < nAmostras; i++) {
        fprintf(fp_insertion, "[Amostra %d]\n", i+1);
        fprintf(fp_insertion, "tempo: %f\nnum comp: %ld\ntrocas: %ld\n\n", dados_insertion[i].tempo_de_execucao, dados_insertion[i].num_comparacoes, dados_insertion[i].num_trocas);

        fprintf(fp_selection, "[Amostra %d]\n", i+1);
        fprintf(fp_selection, "tempo: %f\nnum comp: %d\ntrocas: %d\n\n", dados_selection[i].tempo_de_execucao, dados_selection[i].num_comparacoes, dados_selection[i].num_trocas);

        fprintf(fp_merge, "[Amostra %d]\n", i+1);
        fprintf(fp_merge, "tempo: %f\nnum comp: %d\ntrocas: %d\n\n", dados_merge[i].tempo_de_execucao, dados_merge[i].num_comparacoes, dados_merge[i].num_trocas);
    
        fprintf(fp_heap, "[Amostra %d]\n", i+1);
        fprintf(fp_heap, "tempo: %f\nnum comp: %d\ntrocas: %d\n\n", dados_heap[i].tempo_de_execucao, dados_heap[i].num_comparacoes, dados_heap[i].num_trocas);
    
        fprintf(fp_quick, "[Amostra %d]\n", i+1);
        fprintf(fp_quick, "tempo: %f\nnum comp: %d\ntrocas: %d\n\n", dados_quick[i].tempo_de_execucao, dados_quick[i].num_comparacoes, dados_quick[i].num_trocas);
    }
	
    //calcula estatisticas
    struct dados_sort estatisticas_insertion = calculaEstatisticas(dados_insertion, nAmostras);
    struct dados_sort estatisticas_selection = calculaEstatisticas(dados_selection, nAmostras);
    struct dados_sort estatisticas_merge = calculaEstatisticas(dados_merge, nAmostras);
    struct dados_sort estatisticas_heap = calculaEstatisticas(dados_heap, nAmostras);
    struct dados_sort estatisticas_quick = calculaEstatisticas(dados_quick, nAmostras);

    
    fprintf(fp_insertion, "[Tempo de exec]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_insertion.tempo_de_execucao.media, estatisticas_insertion.tempo_de_execucao.variancia, estatisticas_insertion.tempo_de_execucao.desvio_padrao);
    fprintf(fp_insertion, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", 
    estatisticas_insertion.num_comparacoes.media, estatisticas_insertion.num_comparacoes.variancia, estatisticas_insertion.num_comparacoes.desvio_padrao);
    fprintf(fp_insertion, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", 
    estatisticas_insertion.num_trocas.media, estatisticas_insertion.num_trocas.variancia, estatisticas_insertion.num_trocas.desvio_padrao);
    
    fprintf(fp_selection, "[Tempo de exec]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_selection.tempo_de_execucao.media, estatisticas_selection.tempo_de_execucao.variancia, estatisticas_selection.tempo_de_execucao.desvio_padrao);
    fprintf(fp_selection, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", 
    estatisticas_selection.num_comparacoes.media, estatisticas_selection.num_comparacoes.variancia, estatisticas_selection.num_comparacoes.desvio_padrao);
    fprintf(fp_selection, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", 
    estatisticas_selection.num_trocas.media, estatisticas_selection.num_trocas.variancia, estatisticas_selection.num_trocas.desvio_padrao);
    
    fprintf(fp_merge, "[Tempo de exec]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_merge.tempo_de_execucao.media, estatisticas_merge.tempo_de_execucao.variancia, estatisticas_merge.tempo_de_execucao.desvio_padrao);
    fprintf(fp_merge, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", 
    estatisticas_merge.num_comparacoes.media, estatisticas_merge.num_comparacoes.variancia, estatisticas_merge.num_comparacoes.desvio_padrao);
    fprintf(fp_merge, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", 
    estatisticas_merge.num_trocas.media, estatisticas_merge.num_trocas.variancia, estatisticas_merge.num_trocas.desvio_padrao);
    
	fprintf(fp_heap, "[Tempo de exec]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_heap.tempo_de_execucao.media, estatisticas_heap.tempo_de_execucao.variancia, estatisticas_heap.tempo_de_execucao.desvio_padrao);
    fprintf(fp_heap, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", 
    estatisticas_heap.num_comparacoes.media, estatisticas_heap.num_comparacoes.variancia, estatisticas_heap.num_comparacoes.desvio_padrao);
    fprintf(fp_heap, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", 
    estatisticas_heap.num_trocas.media, estatisticas_heap.num_trocas.variancia, estatisticas_heap.num_trocas.desvio_padrao);
    
    fprintf(fp_quick, "[Tempo de exec]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_quick.tempo_de_execucao.media, estatisticas_quick.tempo_de_execucao.variancia, estatisticas_quick.tempo_de_execucao.desvio_padrao);
    fprintf(fp_quick, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", 
    estatisticas_quick.num_comparacoes.media, estatisticas_quick.num_comparacoes.variancia, estatisticas_quick.num_comparacoes.desvio_padrao);
    fprintf(fp_quick, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", 
    estatisticas_quick.num_trocas.media, estatisticas_quick.num_trocas.variancia, estatisticas_quick.num_trocas.desvio_padrao);
    

    
    printf("\n\nInsertion:\n");
    printaEstats(estatisticas_insertion);
    
    printf("\nSelection:\n");
    printaEstats(estatisticas_selection);
    
    printf("\nMerge:\n");
    printaEstats(estatisticas_merge);
    
    printf("\nHeap:\n");
    printaEstats(estatisticas_heap);
    
    printf("\nQuick:\n");
    printaEstats(estatisticas_quick);
	
	fclose(fp_selection);
	fclose(fp_heap);
	fclose(fp_insertion);
	fclose(fp_quick);
	fclose(fp_merge);

	return 0;
}

int* geraVetor(long int tam)
{
	int i;
	int *vet = (int *) malloc(sizeof(int)*tam);
	
	for (i = 0; i < tam; i++)
		vet[i] = rand() % 100;
	
	return vet;
}

void printaVetor(int *vet, long int tam)
{
	int i;
	for (i = 0; i < tam; i++)
		printf("%d ", vet[i]);
}

//============== Sorts ==============//
//Insertion
void insertionSort(int *vet, long int tam, struct dados_da_amostra *dado)
{
	int i, j, chave;
	clock_t tempo1, tempo2;

    printf("comps no insertion: %d\n", dado->num_comparacoes);
    printf("trocas no insertion: %d\n", dado->num_trocas);

	tempo1 = clock();

	for (i = 1; i < tam; i++){
		chave = vet[i];
		j = i - 1;
		while (j >= 0 && vet[j] > chave){
			vet[j+1] = vet[j];
			j = j-1;
            dado->num_trocas++;
            dado->num_comparacoes++;
		}

		dado->num_comparacoes++;
		vet[j + 1] = chave;
	}

	tempo2 = clock();

	dado->tempo_de_execucao = (double) (tempo2 - tempo1)/CLOCKS_PER_SEC;

    printf("comps no insertion: %d\n", dado->num_comparacoes);
    printf("trocas no insertion: %d\n", dado->num_trocas);
}

//Selection
void selectionSort(int *vet, int long tam, struct dados_da_amostra *dado)
{
	int i, j, min, aux;
	clock_t tempo1, tempo2;

	tempo1 = clock();
	
	for (i = 0; i < tam-1; i++){
		min = i;
		for (j = i+1; j < tam; j++){
			dado->num_comparacoes++;
			if (vet[j] < vet[min]){
				min = j;
			}
		}
		aux = vet[i];	
		vet[i] = vet[min];
		vet[min] = aux;
		
		dado->num_trocas++;
	}
	
	tempo2 = clock();
	
	dado->tempo_de_execucao = (double) (tempo2 - tempo1)/CLOCKS_PER_SEC;
}

//Merge
void intercala(int *vet, int comeco, int meio, int fim, struct dados_da_amostra *dados) {
	int temp[fim - comeco + 1];
	int pos = 0, pos_comeco = comeco, pos_final = meio + 1;

	while (pos_comeco <= meio && pos_final <= fim){
    	if (vet[pos_comeco] < vet[pos_final]){
        	temp[pos++] = vet[pos_comeco++];
            dados->num_trocas++;
    	}
    	else{
        	temp[pos++] = vet[pos_final++];
            dados->num_trocas++;
    	}

        dados->num_comparacoes++;
	}

	while (pos_comeco <= meio){
		temp[pos++] = vet[pos_comeco++];
        dados->num_trocas++;
	}

	while (pos_final <= fim){
		temp[pos++] = vet[pos_final++];
        dados->num_trocas++;
	}

    int i;
    for (i = 0; i < pos; i++){
        vet[i + comeco] = temp[i];
    }

    return;
}

void mergeSort(int *vet, int comeco, int fim, struct dados_da_amostra *dados){
    int meio = (fim+comeco)/2;
	if (comeco < fim) {
        mergeSort(vet, comeco, meio, dados);
        mergeSort(vet, meio+1, fim, dados);
        intercala(vet, comeco, meio, fim, dados);
    }

    dados->num_comparacoes++;
}

//Heap
void maxHeapify(int *vet, long int tam, int i, struct dados_da_amostra *dados)
{
	int aux;
    int maior = i;
    int e = 2*i + 1;
    int d = 2*i + 2;
    
    dados->num_comparacoes++;
    if (e < tam && vet[e] > vet[maior]){
    	maior = e;
	}
    
    dados->num_comparacoes++;
    if (d < tam && vet[d] > vet[maior]){
    	maior = d;
	}
    
    dados->num_comparacoes++;
    if (maior != i) {
    	aux = vet[i];
    	vet[i] = vet[maior];
    	vet[maior] = aux;
    	
        dados->num_trocas++;
        maxHeapify(vet, tam, maior, dados);
    }
}

void heapSort(int *vet, long int tam, struct dados_da_amostra *dados)
{
	int i, aux;
	
    for (i = tam/2 - 1; i >= 0; i--) {
    	maxHeapify(vet, tam, i, dados);
	}
	
	for (i = tam - 1; i >= 0; i--) {
    	aux = vet[0];
    	vet[0] = vet[i];
    	vet[i] = aux;

        dados->num_trocas++;
        maxHeapify(vet, i, 0, dados);
	}
}

//Quick
int partition(int *vet, int p, long int r, struct dados_da_amostra *dados)
{
	int aux;
	int x = vet[r]; // pivÃ´
	int i = p-1, j;

	for (j = p; j <= r-1; j++){
        
        dados->num_comparacoes++;
		if (vet[j] < x) {
			i++;
			aux = vet[i];
			vet[i] = vet[j];
			vet[j] = aux;
            dados->num_trocas++;
		}
	}
	
	aux = vet[i + 1];
	vet[i + 1] = vet[r];
	vet[r] = aux;
	dados->num_trocas++;

	return i + 1;
}

void quickSort(int *vet, int p, long int r, struct dados_da_amostra *dados)
{
	int q;
	

	if (p < r) {
		q = partition(vet, p, r, dados);	
		quickSort(vet, p, q-1, dados);
		quickSort(vet, q+1, r, dados);
	}
}
