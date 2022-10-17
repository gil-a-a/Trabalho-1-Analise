void intercala(int *vet, int tam, int p, int q, int r)
{
	int i, j, k;
	int aux[tam];
	
	for (i = p; i < q; i++)
		aux[i] = vet[i];
	for (j = q + 1; j < r; j++)
		aux[r + q + 1 - j] = vet[j];
	
	i = p;
	j = r;
	
	for (k = p; k < r; k++){
		if (aux[i] <= aux[j]){
			vet[k] = aux[i];
			i++;
		} else {
			vet[k] = aux[j];
			j--;
		}
	}
}

void mergeSortCont(int *vet, int tam, int p, int r)
{
	int q;
	
	if (p < r){
		q = (int) floor((p + r)/2);	//floor() arredonda pra baixo
		mergeSortCont(vet, tam, p, q);
		mergeSortCont(vet, tam, q + 1, r);
		intercala(vet, tam, p, q, r);
	}
}

void mergeSort(int *vet, int tam)
{
	mergeSortCont(vet, tam, 0, tam-1);
}
