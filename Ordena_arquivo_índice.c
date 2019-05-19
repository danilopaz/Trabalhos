#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Indice Indice;
struct _Indice{
	char nis[14];
	char pos[12];
};

//Criterio de comparacao para o ordenamento do arquivo
int compara(const void *i1, const void *i2){
  	return strncmp(((Indice*)i1)->nis, ((Indice*)i2)->nis, 14);
}

int main(){
	
	FILE *indice;
	Indice *i;
	long posicao, qtde;
	
	indice = fopen("indice_arq.txt", "r");
	fseek(indice, 0, SEEK_END);
	posicao = ftell(indice);
	qtde = posicao / sizeof(Indice);
	
	i = (Indice*) malloc(posicao);
	rewind(indice);
	if(fread(i, sizeof(Indice), qtde, indice) == qtde){
        printf("Lido = OK\n");
    }
	fclose(indice);
	
	//Ordenacao e escrita do arquivo ordenado em um novo arquivo.
	qsort(i, qtde, sizeof(Indice), compara);
	indice = fopen("indice_arq_ordenado.txt", "w");
	fwrite(i, sizeof(Indice), qtde, indice);
	
	fclose(indice);
	free(i);
	return 0;
}
