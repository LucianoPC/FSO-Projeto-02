#include <stdio.h>
#include <stdlib.h>

int main()
{
	int indice;
	int numeroArquivos;
	char *nomeArquivo;
	FILE *novoArquivo;
	
	
	nomeArquivo = malloc(sizeof(255));
	numeroArquivos = 100000;
	
	for(indice = 0; indice < numeroArquivos; indice++)
	{
		sprintf(nomeArquivo, "ArquivosVirus/Virus_%d", indice);
		novoArquivo = fopen(nomeArquivo, "a");
		fclose(novoArquivo);
	}	
	
	printf("\nOk!\n\n");
	
	return 0;
}
