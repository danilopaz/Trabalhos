#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
	
	char linha[2048];
	char nis[15];
	int n = 0;
	int coluna = 0;
	long posicao;
	char* campo;
	
	FILE *f = fopen("bolsa.csv", "r");
	FILE *indice = fopen("indice_arq.txt", "w");
	
	fgets(linha, 2048, f);
	posicao = ftell(f);
	fgets(linha, 2048, f);
	
	while(!feof(f)){
		coluna = 0;
		campo = strtok(linha,"\t");
		while(campo){
			if(coluna == 7){
				strcpy(nis, campo);
				fprintf(indice, "%.14s %010ld\n", nis, posicao);
			}
			coluna++;
			campo = strtok(NULL,"\t");
		}
		posicao = ftell(f);
		fgets(linha, 2048, f);
		n++;
	}
	
	fclose(f);
	fclose(indice);
	return 0;
}
