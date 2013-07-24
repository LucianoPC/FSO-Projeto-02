#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	
	FILE *arquivoMultiplica;
	FILE *arquivoSoma;
	size_t tamanho = 4096;
	char *linha = malloc(tamanho);
	
	arquivoMultiplica = fopen("multiplica.c", "r");
	arquivoSoma = fopen("soma.c", "w");
	
	while( getline(&linha, &tamanho, arquivoMultiplica) > 0 )
	{
		printf("%s", linha);
		fputs(linha, arquivoSoma);
	}
	
	fclose(arquivoSoma);
	fclose(arquivoMultiplica);
	
	
	arquivoSoma = fopen("soma.c", "r");
	
	
	while( getline(&linha, &tamanho, arquivoSoma) > 0 )
	{
		printf("%s", linha);
	}
	
	fclose(arquivoSoma);
	
	
	system("gcc -o soma.exe soma.c");
	
	
	printf("\nOk!\n\n");
	return 0;
}
