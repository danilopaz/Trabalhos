#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct _Endereco{

	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};
typedef struct _Endereco Endereco;

int compara(const void *e1, const void *e2){
  	return strncmp(((Endereco*)e1)->cep, ((Endereco*)e2)->cep, 8);
}

int main(){

	FILE *f;
	FILE *new_file;
	Endereco e;
	char dir[15] = "cep_arq";
	char ext[5] = ".dat";
	char diretorio[15];
	f = fopen("cep.dat", "r");


	int i;
	for(i = 0; i < 8; i++){

		snprintf(diretorio, 15, "%s%d%s", dir, i, ext);
		new_file = fopen(diretorio, "w");
		int k;
		for(k = 0; k < 10; k++){
			fread(&e, sizeof(Endereco), 1, f);
			fwrite(&e, sizeof(Endereco), 1, new_file);
		}
		fclose(new_file);
	}

	printf("\nArquivos criados com sucesso!!!\n");
	fclose(f);


	Endereco *e2;
	FILE *arq;
	long posicao, qtde;

	int j;
	for(j = 0; j < 8; j++){
		snprintf(diretorio, 15, "%s%d%s", dir, i, ext);
		arq = fopen(diretorio, "r");
		fseek(arq, 0, SEEK_END);
		posicao = ftell(arq);
		qtde = posicao / sizeof(Endereco);

		e2 = (Endereco*) malloc(posicao);
		rewind(arq);
		fread(e2, sizeof(Endereco), qtde, arq);
		fclose(arq);
		qsort(e2, qtde, sizeof(Endereco), compara);
		snprintf(diretorio, 15, "%s%d%s", dir, i, ext);
		arq = fopen(diretorio, "w");
		fwrite(e2, sizeof(Endereco), qtde, arq);
	}
	fclose(arq);
	free(e2);


	FILE *a, *b, *saida;
    Endereco ea, eb;
    int prox = 0, n = 8;

	while(prox + 1 < n){
		snprintf(diretorio, 15, "%s%d%s", dir, prox, ext);
		a = fopen(diretorio, "rb");
	
		snprintf(diretorio, 15, "%s%d%s", dir, prox + 1, ext);
		b = fopen(diretorio, "rb");
	
		snprintf(diretorio, 15, "%s%d%s", dir, n, ext);
		saida = fopen(diretorio, "wb");
	
		prox = prox + 2;
		n++;
	
		fread(&ea, sizeof(Endereco), 1, a);
		fread(&eb, sizeof(Endereco), 1, b);
	
		while(!feof(a) && !feof(b)){
		    if(compara(&ea, &eb) < 0){
		        fwrite(&ea, sizeof(Endereco), 1, saida);
		        fread(&ea, sizeof(Endereco), 1, a);
		    }
		    else{
		   		fwrite(&eb, sizeof(Endereco), 1, saida);
		        fread(&eb, sizeof(Endereco), 1, b);
		    }
		}
	
		while(!feof(a)){
		    fwrite(&ea, sizeof(Endereco), 1, saida);
		    fread(&ea, sizeof(Endereco), 1, a);
		}
		while(!feof(b)){
		    fwrite(&eb, sizeof(Endereco), 1, saida);
		    fread(&eb, sizeof(Endereco), 1, b);
		}
	
		fclose(a);
		fclose(b);
		fclose(saida);
	}

	return 0;
}
