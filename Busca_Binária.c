#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(){
	
	FILE *f;
	Endereco e;
	long posicao, primeiro, meio, ultimo;
	
	f = fopen("cep_ordenado.dat", "r");				//Abre o arquivo.
	char meu_cep[8];
	printf("Digite seu CEP: ");
	scanf("%s", &meu_cep);
	
	int cont = 0;
	fseek(f, 0, SEEK_END);
	posicao = ftell(f);
	rewind(f);
	primeiro = 0;
	ultimo = (posicao / sizeof(Endereco)) - 1;
	
	while(primeiro <= ultimo){ 
		meio = (primeiro + ultimo) / 2;	
		fseek(f, meio * sizeof(Endereco), SEEK_SET);
		cont++;
		fread(&e, sizeof(Endereco), 1, f);
		if(strncmp(meu_cep, e.cep,8) == 0){
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;
		}
		else if(strncmp(meu_cep, e.cep,8) > 0){
			primeiro = meio + 1;
		}
		else if(strncmp(meu_cep, e.cep,8) < 0){
			ultimo = meio - 1;
		}
	}
	printf("\n Numero de enderecos lidos: %d\n", cont);				//Imprime a quantidade de registros lidos até encontrar o procurado.
	fclose(f);
	return 0;
}
