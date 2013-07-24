#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gravarCaractereNoArquivo(char caractere, char *nomeArquivo)
{
	FILE *arquivo;
	arquivo = fopen(nomeArquivo, "a");
	fputc(caractere, arquivo);
	fputc('\n', arquivo);
	fclose(arquivo);
}

char lerCaractereNoArquivo(char *nomeArquivo)
{
	FILE *arquivo;
	char caractere = ' ';
	arquivo = fopen(nomeArquivo, "r");
	caractere = fgetc(arquivo);
	fclose(arquivo);
	
	return caractere;
}

int main()
{
	FILE *arquivoDriver;
	FILE *arquivoVirus;
	char caractere;
	char caractereAnterior;
	
	char *nomeArquivoLog = "caracteres.txt";
	char *nomeArquivoModulo = "/dev/meuDriver";
	
	FILE *arquivoTeste;
	arquivoTeste = fopen("Arquivo_Teste.txt", "a");
	fclose(arquivoTeste);
	
	while(1)
	{
		caractere = lerCaractereNoArquivo(nomeArquivoModulo);
		
		if(caractere != caractereAnterior)
		{
			caractereAnterior = caractere;
			gravarCaractereNoArquivo(caractere, nomeArquivoLog);
		}
		
		usleep(100);
	}
	
	
	printf("\nOk!\n\n");
	
	return 0;
}